/////////////////////////////////////////////////
//
// ������ ���������� �������� � �� ����� MySQL
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.08
//
/////////////////////////////////////////////////

#pragma once

#include "Dataset.h"

#ifdef UseMySQL

namespace database
{
    // ��������� � ��
    class TConnectionMySQL : public TConnection
    {
    private:
        // ��������� �������� ������ �������������
        MYSQL m_MySQL = {};
        // ������������ ����������
        MYSQL * m_Connection = nullptr;
    public:
        // ����������
        void Start();
        // ������������
        void Stop();
        // ����� �������� ��������� � �����������
        TDataset * Call(const char * aQuery, const char * aFormat, va_list aParams);
    };

    // �������, ����������� �������
    class TDatasetMySQL : public TDataset
    {
    private:
        // �������������� ������
        MYSQL_STMT * m_Stmt = nullptr;
        // ����������
        MYSQL_RES * m_Res = nullptr;
        // �������� ���������� �������
        MYSQL_BIND * m_Bind = nullptr;
    private:
        // ����������� �������� ���������� �������
        MYSQL_BIND * Seek(const char * aName);
        // ����������� ������
        void ReadBuffer(MYSQL_BIND * aBind, void * aValue);
    public:
        // ���������� �������
        TDatasetMySQL(MYSQL * aConnection, const char * aQuery, const char * aFormat, va_list aParams);
        // ����������
        ~TDatasetMySQL();
        // ������ ��������� ������
        bool ReadRow();
        // ������� �������� ��� Int
        int ReadInt(const char * aFieldName);
        // ������� �������� ��� String
        string & ReadString(const char * aFieldName);
    };
}

#endif