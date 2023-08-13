/////////////////////////////////////////////////
//
// ������ ���������� ����������� ����������� 
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
    // ����� ���������� ����������� �����������
    class TLog
    {
    private:
        // ������� �����
        const char * S_LOG_DIR = "Logs";
        // ���������� ����� ����
        const char * S_LOG_EXT = ".log";
        // ������ ����� ����
        const char * S_LOG_NAME = "%Y%m%d";
        // ������ ����� ����
        const char * S_LOG_ROW = "%H:%M:%S";
        // ������� ������� �����������
        const char * S_LOG_INIT = "Log init";
        // ������� ���������� �����������
        const char * S_LOG_DONE = "Log done";
    private:
        // ����� ��� �������� 
        char m_FormatBuff[34] = {};
        // ������� ���������� ������������� ������
        std::mutex m_Mutex;
        // ���� ����
        FILE * m_File = nullptr;
    private:
        // ����������� ���� � ������� � ��������� �������������
        inline const char * DateTme(const char * aFormat);
        // ������ ������ 
        inline void InternalWrite(const char * aValue);
    public:
        // ������ �����������
        void Start();
        // ��������� �����������
        void Stop();
        // ������ ���������� ���������
        void Write(const char * aMethod, const char * aFile, long aLine, bool aCritical, const char * aMessage, ...);
    };
}