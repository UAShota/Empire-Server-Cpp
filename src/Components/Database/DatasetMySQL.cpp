#include "pch.h"
#include "DatasetMySQL.h"

#ifdef UseMySQL

namespace database
{
    void TConnectionMySQL::Start()
    {
        setlocale(LC_ALL, "Russian");

        // ��������� ������� ���������
        if (!mysql_init(&m_MySQL))
        {
            LogError("MySQL init error");
            exit(0);
        }

        // �������� ���������
        if (mysql_options(&m_MySQL, MYSQL_SET_CHARSET_NAME, "utf8"))
        {
            LogError(mysql_error(&m_MySQL));
            exit(mysql_errno(&m_MySQL));
        }

        // ��������� �����������
        m_Connection = mysql_real_connect(&m_MySQL, S_HOST, S_USERNAME, S_PWD, S_DATABASE, I_PORT, 0, 0);
        if (!m_Connection)
        {
            LogError(mysql_error(&m_MySQL));
            exit(mysql_errno(&m_MySQL));
        }
    }

    void TConnectionMySQL::Stop()
    {
        mysql_close(m_Connection);
    }

    TDataset * TConnectionMySQL::Call(const char * aQuery, const char * aFormat, va_list aParams)
    {
        return new TDatasetMySQL(m_Connection, aQuery, aFormat, aParams);
    }

    TDatasetMySQL::TDatasetMySQL(MYSQL * aMySQL, const char * aQuery, const char * aFormat, va_list aParams)
    {
        uint tmpFormatLen = 0;
        char tmpBuffer[MAXBYTE] = {};

        // ������� ������
        strcat_s(tmpBuffer, "call ");
        strcat_s(tmpBuffer, aQuery);

        // ������� ��������� �������
        if (aFormat != nullptr)
        {
            tmpFormatLen = strlen(aFormat);
            strcat_s(tmpBuffer, "(");
            for (uint tmpI = 0; tmpI < tmpFormatLen; tmpI++)
            {
                strcat_s(tmpBuffer, "?");
                if (tmpI < tmpFormatLen - 1)
                    strcat_s(tmpBuffer, ",");
            }
            strcat_s(tmpBuffer, ")");
        }

        // �������������� ����� stmp
        m_Stmt = mysql_stmt_init(aMySQL);
        if (!m_Stmt)
        {
            Log(mysql_stmt_error(m_Stmt));
            return;
        }

        // �������������� ���������
        if (mysql_stmt_prepare(m_Stmt, tmpBuffer, strlen(tmpBuffer)))
        {
            Log(mysql_stmt_error(m_Stmt));
            return;
        }

        // ���� ��������� ���� - ������ ��
        if (tmpFormatLen > 0)
        {
            // ������� ���������        
            std::vector<MYSQL_BIND> tmpBinds(tmpFormatLen);
            MYSQL_BIND * tmpBind = &tmpBinds.front();
            const char * tmpchar = aFormat;
            string * tmpString = nullptr;
            // ������ ���������
            for (uint tmpI = 0; tmpI < tmpFormatLen; tmpI++, tmpchar++, tmpBind++)
            {
                // ��������� ��� ���������
                switch (*tmpchar)
                {
                case 'd':
                    tmpBind->buffer_type = MYSQL_TYPE_LONG;
                    tmpBind->buffer = &va_arg(aParams, int);
                    tmpBind->buffer_length = sizeof(int);
                    break;
                case 's':
                    tmpString = (string*)va_arg(aParams, string*);
                    tmpBind->buffer_type = MYSQL_TYPE_STRING;
                    tmpBind->buffer = tmpString->String();
                    tmpBind->buffer_length = tmpString->Length();
                    break;
                default:
                    Log("Invalid query format");
                    break;
                }
            }
            // �������� ��������
            if (mysql_stmt_bind_param(m_Stmt, &tmpBinds.front()))
            {
                Log(mysql_stmt_error(m_Stmt));
                return;
            }
        }

        // �������� ������
        if (mysql_stmt_execute(m_Stmt))
        {
            Log(mysql_stmt_error(m_Stmt));
            return;
        }

        // �������� ������ ����� ������
        if (mysql_stmt_store_result(m_Stmt))
        {
            Log(mysql_stmt_error(m_Stmt));
            return;
        }

        // �������� ���������� � ��������
        m_Res = mysql_stmt_result_metadata(m_Stmt);
        if (!m_Res)
        {
            Log(mysql_stmt_error(m_Stmt));
            return;
        }

        // ������� ���������� ������
        MYSQL_STMT tmpStmt = MYSQL_STMT(*m_Stmt);
        while (mysql_stmt_next_result(&tmpStmt) == 0)
        {
            mysql_stmt_store_result(&tmpStmt);
            mysql_stmt_free_result(&tmpStmt);
        }

        // ��������� ��������
        m_Bind = new MYSQL_BIND[m_Res->field_count];
        MYSQL_FIELD * tmpField = m_Res->fields;
        MYSQL_BIND * tmpBind = m_Bind;
        // ������� ���� ����� 
        for (uint tmpI = 0; tmpI < m_Res->field_count; tmpI++, tmpField++, tmpBind++)
        {
            memset(tmpBind, 0, sizeof(MYSQL_BIND));
            tmpBind->buffer_type = tmpField->type;
            tmpBind->buffer_length = tmpField->length;
            tmpBind->buffer = new wchar[tmpBind->buffer_length];
        }

        // �������� ����������
        if (mysql_stmt_bind_result(m_Stmt, m_Bind))
        {
            Log(mysql_stmt_error(m_Stmt));
            return;
        }
    }

    TDatasetMySQL::~TDatasetMySQL()
    {
        if (m_Res)
        {
            if (m_Bind)
            {
                MYSQL_BIND * tmpBind = m_Bind;
                for (uint tmpI = 0; tmpI < m_Res->field_count; tmpI++, tmpBind++)
                    delete[](tmpBind->buffer);
                delete[](m_Bind);
            }
            mysql_free_result(m_Res);
        }
        mysql_stmt_free_result(m_Stmt);
    }

    bool TDatasetMySQL::ReadRow()
    {
        // ��� ������
        if (!m_Bind)
            return false;
        int tmpResult = mysql_stmt_fetch(m_Stmt);
        // ������ ����
        if (tmpResult == 0)
            return true;
        // ������ ���������
        if (tmpResult == MYSQL_NO_DATA)
            return false;
        // ����� ������
        Log(mysql_stmt_error(m_Stmt));
        return false;
    }

    MYSQL_BIND * TDatasetMySQL::Seek(const char * aName)
    {
        MYSQL_FIELD * tmpField = m_Res->fields;
        for (uint tmpI = 0; tmpI < m_Res->field_count; tmpI++, tmpField++)
        {
            MYSQL_BIND * tmpBind = &m_Bind[tmpI];
            // ������ ����� �����
            if (_stricmp(tmpField->name, aName) != 0)
                continue;
            // ������� ��������
            if (mysql_stmt_fetch_column(m_Stmt, tmpBind, tmpI, 0))
            {
                Log(mysql_stmt_error(m_Stmt));
                return false;
            }
            else
                return tmpBind;
        }
        Log("Invalid field name", aName);
        return false;
    }

    void TDatasetMySQL::ReadBuffer(MYSQL_BIND * aBind, void * aValue)
    {
        if (!memcpy(aValue, aBind->buffer, *aBind->length))
            Log("Buffer copy for read failed");
    }

    int TDatasetMySQL::ReadInt(const char * aFieldName)
    {
        int tmpValue = 0;
        // ������ ����
        if (MYSQL_BIND * tmpBind = Seek(aFieldName))
        {
            if (tmpBind->length)
                ReadBuffer(tmpBind, &tmpValue);
        }
        return tmpValue;
    }

    string & TDatasetMySQL::ReadString(const char * aFieldName)
    {
        char * tmpBuf = nullptr;
        int tmpLen = 0;
        // ������ ����
        if (MYSQL_BIND * tmpBind = Seek(aFieldName))
        {
            if (tmpBind->length)
            {
                tmpLen = *tmpBind->length;
                tmpBuf = (char*)malloc(tmpLen);
                ReadBuffer(tmpBind, tmpBuf);
            }
        }
        // ������
        return *(new string(tmpBuf, tmpLen));
    }
}

#endif