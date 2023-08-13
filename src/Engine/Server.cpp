#include "pch.h"
#include "Server.h"
#include "Globals//Player.h"

namespace engine
{
    void TServer::Start()
    {
        Log("Starting");
        m_Planetar.Start();
        m_Auth.Start();
#ifndef NDEBUG
        m_Socket.Start(25599, this);
#else
        m_Socket.Start(25600, this);
#endif
        Log("Started");
    }

    void TServer::Stop()
    {
        Log("Stopping");
        m_Queue.Awake();
        m_Socket.Stop();
        m_Auth.Stop();
        m_Planetar.Stop();
        Log("Stopped");
    }

    void TServer::OnConnect(transport::TSocketConnection * aConnection)
    {
        /**/
    }

    void TServer::OnDisconnect(transport::TSocketConnection * aConnection)
    {
        /**/
    }

    void TServer::OnRead(transport::TSocketConnection * aConnection, char * aBuffer, int aBufferSize)
    {
        // ������� ���������
        int tmpSize = aConnection->BufferRead.Size() - sizeof(int);
        // ���� ��� ����� ������� - ������� ������
        if (tmpSize >= 0)
        {
            tmpSize = aConnection->BufferRead.PeekCommand();
            tmpSize -= aConnection->BufferRead.Position();
        }
        // ������� ������� ������ ������
        int tmpCopyCount = std::min(aBufferSize, std::abs(tmpSize));
        aBufferSize -= tmpCopyCount;
        // ������� �����
        aConnection->BufferRead.WriteBuffer(aBuffer, tmpCopyCount);
        // ������� ����� �� ����������� ������
        aBuffer += tmpCopyCount;
        // ���� ������� ����������, ��������� ��� ��
        if (tmpSize < 0)
        {
            tmpSize += tmpCopyCount;
            // ��������� ������ ���� ������ ������
            if (tmpSize == 0)
                aConnection->BufferRead.Allocate();
            // ���� ��� ���� ������ - �������
            if (aBufferSize > 0)
                OnRead(aConnection, aBuffer, aBufferSize);
            return;
        }
        else
            aConnection->BufferRead.Reset(true);
        // ��������� ������� ������� � ������        
        tmpSize = aConnection->BufferRead.PeekCommand();
        // ����� ������� � ����������� 0x1F01 >> 0x1
        switch (tmpSize >> 12)
        {
        case 0:
            m_Auth.Command(aConnection);
            break;
        case 1:
            m_Planetar.Command(aConnection);
            break;
        default:
            Log("Unknow command");
        }
        // ���� ����� ���� � ������ - ������� �������
        aConnection->BufferRead.Reset(false);
    }

    void TServer::OnWrite(transport::TSocketConnection ** aConnection)
    {
        *aConnection = m_Queue.Pop();
    }

    globals::TPlayer * TServer::FindPlayer(int aID, bool aLoad)
    {
        return m_Auth.FindPlayer(aID, aLoad);
    }

    void TServer::Send(transport::TSocketConnection * aConnection)
    {
        /*m_Queue.Push(aConnection);*/
    }
}