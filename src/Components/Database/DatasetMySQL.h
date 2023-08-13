/////////////////////////////////////////////////
//
// Модуль управления доступом к БД через MySQL
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
    // Коннектор к БД
    class TConnectionMySQL : public TConnection
    {
    private:
        // Интерфейс держащий данные инициализации
        MYSQL m_MySQL = {};
        // Подключенное соединение
        MYSQL * m_Connection = nullptr;
    public:
        // Соединение
        void Start();
        // Отсоединение
        void Stop();
        // Вызов хранимой процедуры с параметрами
        TDataset * Call(const char * aQuery, const char * aFormat, va_list aParams);
    };

    // Датасет, выполняющий запросы
    class TDatasetMySQL : public TDataset
    {
    private:
        // Подготовленный объект
        MYSQL_STMT * m_Stmt = nullptr;
        // Метаданные
        MYSQL_RES * m_Res = nullptr;
        // Биндинги результата выборки
        MYSQL_BIND * m_Bind = nullptr;
    private:
        // Кэширование значение указанного столбца
        MYSQL_BIND * Seek(const char * aName);
        // Копирование буфера
        void ReadBuffer(MYSQL_BIND * aBind, void * aValue);
    public:
        // Выполнение запроса
        TDatasetMySQL(MYSQL * aConnection, const char * aQuery, const char * aFormat, va_list aParams);
        // Деструктор
        ~TDatasetMySQL();
        // Чтение очередной записи
        bool ReadRow();
        // Возврат значения как Int
        int ReadInt(const char * aFieldName);
        // Возврат значения как String
        string & ReadString(const char * aFieldName);
    };
}

#endif