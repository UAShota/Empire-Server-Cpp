/////////////////////////////////////////////////
//
// Модуль управления доступом к БД через PostgreSQL
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.08
//
/////////////////////////////////////////////////

#pragma once

#include "Dataset.h"

namespace database
{
	// Коннектор к БД
	class TConnectionPostgreSQL : public TConnection
	{
	private:
		// Интерфейс держащий данные инициализации
		// Подключенное соединение
		PGconn* m_connection = nullptr;
	public:
		// Соединение
		void Connect();
		// Отсоединение
		void Disconnect();
		// Вызов хранимой процедуры с параметрами
		TDataset* Call(const char* aQuery, const char* aFormat, va_list aParams);
	};

	// Датасет, выполняющий запросы
	class TDatasetPostgreSQL : public TDataset
	{
	private:
		// Метаданные
		PGresult* m_res = nullptr;
		int m_size = 0;
		int m_position = 0;
	public:
		// Выполнение запроса
		TDatasetPostgreSQL(PGconn* aConnection, const char* aQuery, const char* aFormat, va_list aParams);
		// Деструктор
		~TDatasetPostgreSQL();
		// Чтение очередной записи
		bool ReadRow();
		// Возврат значения как Int
		int ReadInt(const char* aFieldName);
		// Возврат значения как String
		string& ReadString(const char* aFieldName);
	};
}