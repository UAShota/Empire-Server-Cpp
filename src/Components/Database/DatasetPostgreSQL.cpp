#include "pch.h"
#include "DatasetPostgreSQL.h"

namespace database
{
	void TConnectionPostgreSQL::Connect()
	{
		const char conninfo[] = "postgresql://ovz1.j61191019.0n03n.vps.myjino.ru?port=49207&dbname=galaxyhopes_release&user=galaxyhopes_release&password=7553745";
		/*S_HOST, S_USERNAME, S_PWD, S_DATABASE, I_PORT*/
		// Попробуем создать экземпляр
		m_connection = PQconnectdb(conninfo);
		if (PQstatus(m_connection) != CONNECTION_OK)
		{
			LogError("PostgreSQL init error", PQerrorMessage(m_connection));
			PQfinish(m_connection);
			exit(0);
		}
	}

	void TConnectionPostgreSQL::Disconnect()
	{
		PQfinish(m_connection);
	}

	TDataset* TConnectionPostgreSQL::Call(const char* aQuery, const char* aFormat, va_list aParams)
	{
		return new TDatasetPostgreSQL(m_connection, aQuery, aFormat, aParams);
	}

	TDatasetPostgreSQL::TDatasetPostgreSQL(PGconn* aConnection, const char* aQuery, const char* aFormat, va_list aParams)
	{
		uint tmpFormatLen = 0;
		char tmpBuffer[MAXBYTE] = {};

		// Соберем запрос
		strcat_s(tmpBuffer, "call ");
		strcat_s(tmpBuffer, aQuery);

		// Добавим параметры запроса
		if (aFormat != nullptr)
		{
			tmpFormatLen = strlen(aFormat);
			strcat_s(tmpBuffer, "(");
			for (uint tmpI = 0; tmpI < tmpFormatLen; tmpI++)
			{
				strcat_s(tmpBuffer, "$1");
				if (tmpI < tmpFormatLen - 1)
					strcat_s(tmpBuffer, ",");
			}
			strcat_s(tmpBuffer, ")");
		}

		/* PQexec(conn, "*/
		/*if (PQresultStatus(res) != PGRES_COMMAND_OK) {*/

		m_size = PQntuples(m_res);
	}

	TDatasetPostgreSQL::~TDatasetPostgreSQL()
	{
		if (m_res)
			PQclear(m_res);
	}

	bool TDatasetPostgreSQL::ReadRow()
	{
		if (m_position < m_size) {
			m_position++;
			return true;
		}
		else
			return false;
	}

	int TDatasetPostgreSQL::ReadInt(const char* aFieldName)
	{
		const int tmpField = PQfnumber(m_res, aFieldName);
		const char* tmpBuff = PQgetvalue(m_res, m_position, tmpField);
		// Вернем
		return atol(tmpBuff);
	}

	string& TDatasetPostgreSQL::ReadString(const char* aFieldName)
	{
		const int tmpField = PQfnumber(m_res, aFieldName);
		const int tmpLength = PQgetlength(m_res, m_position, tmpField);
		char* tmpBuff = PQgetvalue(m_res, m_position, tmpField);
		// Вернем
		return *(new string(tmpBuff, tmpLength));
	}
}