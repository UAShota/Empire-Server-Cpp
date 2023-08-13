/////////////////////////////////////////////////
//
// �������� ������ � ��� ���������������� �������
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
        // ����� ������ �� ���������
        const int iCapacity = 64;
        // ����� ������
        char * m_Memory;
        // ������ ������ ������
        int m_Size = 0;
        // ������������ ������ ������ ������
        int m_Capacity = 0;
        // ������� ������� ���������
        int m_Position = 0;
        // ������� ������ �������
        int m_CommandPos = 0;
        // ��������� �� ���������������� ������
        class TSocketConnection * m_SocketConnection = nullptr;
    private:
        // ��������� ��������� ������
        void AllocMemory(int aSize);
        // ���������� ������ ��������� ������
        void ReallocMemory(int aSize);
        // �������� ������� ���������� ������
        bool Readable(int aSize);
        // ������ ������
        void ReadBuffer(void * aValue, int aSize, bool aSkeepPointer = false);
        // ������ ������ � ������ ��������
        int ReadInt(bool aSkipPointer);
        // ������ ������ � ������ ��������
        void WriteInt(int aValue, int aPosition);
    public:
        // ��������� ��� �������
        TSocketBuffer();
        // ����������� ������
        TSocketBuffer(TSocketBuffer * aBuffer);
        // ��� ������ � ��������
        TSocketBuffer(class TSocketConnection * aSocketConnection);
        // ��� ������ � �������
        TSocketBuffer(int aCommand);
        // ��������� ����������
        ~TSocketBuffer();
        // ���������������� ���������
        class TSocketConnection * SocketConnection();
        // ����� ������
        char * Memory();
        // ������� ��������������� ������
        int Position();
        // ������ ������
        int Size();
        // ����������� ������� �������
        void Allocate();
        // ����������� ���� ������� ��� ������ ���������
        int PeekCommand();
        // ����������� ���� ������� �� ������� ���������
        int ReadCommand();
        // ������ �����
        int ReadInt();
        // ������ ������
        string & ReadString();
        // ������ ������ ������
        void WriteBuffer(void * aBuffer, int aSize, int aPosition = 0);
        // ������ ������ ������
        void WriteBuffer(TSocketBuffer * aBuffer);
        // ������ ��������
        void WriteCommand(int aValue);
        // ������ ������ �����
        void WriteInt(int aValue);
        // ������ ������
        void WriteBool(bool aValue);
        // ������ ������
        void WriteString(string & aValue);
        // ����������� ������� ������ �� ������ ������
        void Reset(bool aDropSize);
        // ����������� ������� ������ �� ������ ������ � ������� ������� ������
        void Commit();
    };
}