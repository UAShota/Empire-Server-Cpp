/////////////////////////////////////////////////
//
// ������ ���������� �������� � �� ����� PostgreSQL
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.08
//
/////////////////////////////////////////////////

#pragma once

#include "Dataset.h"

namespace database
{
	// ��������� � ��
	class TConnectionPostgreSQL : public TConnection
	{
	private:
		// ��������� �������� ������ �������������
		// ������������ ����������
		PGconn* m_connection = nullptr;
	public:
		// ����������
		void Connect();
		// ������������
		void Disconnect();
		// ����� �������� ��������� � �����������
		TDataset* Call(const char* aQuery, const char* aFormat, va_list aParams);
	};

	// �������, ����������� �������
	class TDatasetPostgreSQL : public TDataset
	{
	private:
		// ����������
		PGresult* m_res = nullptr;
		int m_size = 0;
		int m_position = 0;
	public:
		// ���������� �������
		TDatasetPostgreSQL(PGconn* aConnection, const char* aQuery, const char* aFormat, va_list aParams);
		// ����������
		~TDatasetPostgreSQL();
		// ������ ��������� ������
		bool ReadRow();
		// ������� �������� ��� Int
		int ReadInt(const char* aFieldName);
		// ������� �������� ��� String
		string& ReadString(const char* aFieldName);
	};
}