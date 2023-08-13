/////////////////////////////////////////////////
//
// ������ ���������� �������������� ������
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.08
//
/////////////////////////////////////////////////

#pragma once

#include "Components/Transport/Socket.h"
#include "Modules/ModulePlanetar.h"
#include "Modules/ModuleAuthorization.h"

namespace engine
{
    class TServer : transport::ISocketWrapper
    {
    private:
        // ������ ������������� �������
        server::TAuthorization m_Auth;
        // ������ ����������� ��������
        planetar::TPlanetar m_Planetar;
        // �������� ����������
        transport::TSocket m_Socket;
        // ������� �������� ���������
        TAsyncQueueSignal<transport::TSocketConnection*> m_Queue;
    public:
        // �����
        void Start();
        // ���������
        void Stop();
        // ������� ����������� �������
        void OnConnect(transport::TSocketConnection * aConnection);
        // ������� ������ �������
        void OnRead(transport::TSocketConnection * aConnection, char * aBuffer, int aBufferSize);
        // ������� ������ �������
        void OnWrite(transport::TSocketConnection ** aConnection);
        // ������� ���������� �������
        void OnDisconnect(transport::TSocketConnection * aConnection);
        // ����� ������ �� ��������������
        globals::TPlayer * FindPlayer(int aID, bool aLoad);
        // �������� ������
        void Send(transport::TSocketConnection * aConnection);
    };
}