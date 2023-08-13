/////////////////////////////////////////////////
//
// Упаковка буфера и его потокобезопасная очередь
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.04
//
/////////////////////////////////////////////////

#pragma once

#include "Components/Classes/String.h"

namespace transport
{
    class TSocketBuffer
    {
    private:
        // Объем памяти по умолчанию
        const int iCapacity = 64;
        // Буфер данных
        char * m_Memory;
        // Размер буфера данных
        int m_Size = 0;
        // Максимальный размер буфера данных
        int m_Capacity = 0;
        // Текущая позиция указателя
        int m_Position = 0;
        // Позиция старта команды
        int m_CommandPos = 0;
        // Указатель на пользовательский объект
        class TSocketConnection * m_SocketConnection = nullptr;
    private:
        // Первичная релокация данных
        void AllocMemory(int aSize);
        // Увеличение памяти релокация данных
        void ReallocMemory(int aSize);
        // Проверка наличия указанного буфера
        bool Readable(int aSize);
        // Чтение буфера
        void ReadBuffer(void * aValue, int aSize, bool aSkeepPointer = false);
        // Чтение буфера с учетом смещения
        int ReadInt(bool aSkipPointer);
        // Чтение буфера с учетом смещения
        void WriteInt(int aValue, int aPosition);
    public:
        // Дефолтный для классов
        TSocketBuffer();
        // Копирование буфера
        TSocketBuffer(TSocketBuffer * aBuffer);
        // Для чтения с серверва
        TSocketBuffer(class TSocketConnection * aSocketConnection);
        // Для записи с команды
        TSocketBuffer(int aCommand);
        // Дефолтный деструктор
        ~TSocketBuffer();
        // Пользовательский указатель
        class TSocketConnection * SocketConnection();
        // Буфер данных
        char * Memory();
        // Признак сформированного буфера
        int Position();
        // Размер буфера
        int Size();
        // Определение размера буффера
        void Allocate();
        // Возвращение кода команды без сдвига указателя
        int PeekCommand();
        // Возвращение кода команды со сдвигом указателя
        int ReadCommand();
        // Чтение числа
        int ReadInt();
        // Чтение строки
        string & ReadString();
        // Запись буфера данных
        void WriteBuffer(void * aBuffer, int aSize, int aPosition = 0);
        // Запись буфера данных
        void WriteBuffer(TSocketBuffer * aBuffer);
        // Запись комманды
        void WriteCommand(int aValue);
        // Запись целого числа
        void WriteInt(int aValue);
        // Запись булина
        void WriteBool(bool aValue);
        // Запись строки
        void WriteString(string & aValue);
        // Перемещение позиции буфера на начало буфера
        void Reset(bool aDropSize);
        // Перемещение позиции буфера на начало буфера с записью размера пакета
        void Commit();
    };
}