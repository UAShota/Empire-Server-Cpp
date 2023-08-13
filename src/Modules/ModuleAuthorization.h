/////////////////////////////////////////////////
//
// ������ ���������� ����������� ��������
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"
#include "Components/Transport/Socket.h"
#include "Components/Transport/Buffer.h"

namespace server
{
    // ����� ���������� ������������
    class TAuthorization
    {
    private:
        // ������ ������
        enum Errors
        {
            // ������ - ������� ������ ����� ��� ������
            ERR_INVALID_CREDENTIALS = 1
        };
        // ������� �����������
        enum Commands
        {
            // �������� ��������� ����
            CMD_CHAT_MESSAGE = 0x0001,
            // �������� ������� �����������
            CMD_LOGIN_AUTH = 0x0002,
            // �������� ������������ �����������
            CMD_LOGIN_FAILED = 0x0003,
            // �������� �������� �����������
            CMD_LOGIN_ACCEPT = 0x0004,
            // �������� ���������� � ��������� �����������
            CMD_LOGIN_RELOG = 0x0005
        };
    private:
        // ��������� ����������� UID
        int m_LastPlayerUID = 0;
        // ��������� ����������� �������
        globals::TPlayer * m_LastPlayer = nullptr;
        // ������ �������
        globals::TPlayerMap m_Players = {};
        // ������� ������� ���������
        transport::TSocketBuffer * m_BufferRead;
        // ������� ������� ������
        transport::TSocketBuffer m_BufferWrite;
        // ����� ��������� �������
        TThread m_Thread;
        // ������� ������
        TAsyncQueueSignal<transport::TSocketBuffer*> m_Queue;
    private:
        // ���� ��������� ���� ���� ������ ������
        static void Execute(TAuthorization * aInstance);
        // ������������ ������
        void WorkRead();
        // ����������� ������ �������
        void ResponseLoginAccept(globals::TPlayer * aPlayer);
        // ����������� ������ ���������
        void ResponseLoginFailed();
        // ����������� ������
        bool CmdLogin();
        // �������� ������� ������
        globals::TPlayer *LoadPlayer(int aUID);
    public:
        // ������ ������
        void Start();
        // ��������� ������
        void Stop();
        // ������� �� ���������
        void Command(transport::TSocketConnection * aConnection);
        // ����� ������ �� ��������������
        globals::TPlayer * FindPlayer(int aUID, bool aLoad);
        // �������� ��������� � ��� ������
        /*void ChatMessage(const char * aText, Globals::TPlayer * aPlayer = nullptr);*/
    };
}