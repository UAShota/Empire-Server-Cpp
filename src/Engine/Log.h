/////////////////////////////////////////////////
//
// Модуль управления подсистемой логирования 
// Copyright(c) 2016 UAShota
//
// Rev D  2018.03.13
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "pch.h"

namespace engine
{
    // Класс управления подсистемой логирования
    class TLog
    {
    private:
        // Каталог логов
        const char * S_LOG_DIR = "Logs";
        // Расширение файла лога
        const char * S_LOG_EXT = ".log";
        // Формат имени лога
        const char * S_LOG_NAME = "%Y%m%d";
        // Формат имени лога
        const char * S_LOG_ROW = "%H:%M:%S";
        // Событие запуска логирования
        const char * S_LOG_INIT = "Log init";
        // Событие завершения логирования
        const char * S_LOG_DONE = "Log done";
    private:
        // Буфер для операций 
        char m_FormatBuff[34] = {};
        // Мьютекс блокировки одновременной записи
        std::mutex m_Mutex;
        // Файл лога
        FILE * m_File = nullptr;
    private:
        // Возвращение даты и времени в строковом представлении
        inline const char * DateTme(const char * aFormat);
        // Запись строки 
        inline void InternalWrite(const char * aValue);
    public:
        // Запуск логирования
        void Start();
        // Остановка логирования
        void Stop();
        // Запись кастомного сообщения
        void Write(const char * aMethod, const char * aFile, long aLine, bool aCritical, const char * aMessage, ...);
    };
}