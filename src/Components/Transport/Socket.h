/////////////////////////////////////////////////
//
// Êëèåíò äîñòóïà ê ñåòè
// Copyright(c) 2016 UAShota
//
// Rev F  2018.11.04
//
/////////////////////////////////////////////////

#pragma once

#include "pch.h"
#include "Buffer.h"
#include "Components/Classes/Queue.h"
#include "Components/Classes/Thread.h"

namespace transport
{
    // Êëàññ îïèñàíèÿ ïîäñîåäèíåííîãî êëèåíòà
    /**/
    class TSocketConnection
    {
    private:
        static const int I_IP_LENGTH = 16;
        string m_IP;
        SOCKET m_UID = 0;
        TAsyncQueueSignal<TSocketBuffer> m_QueueWrite;
    public:
        void * Owner = nullptr;
        TSocketBuffer BufferRead = this;
    public:
        TSocketConnection(SOCKET aUID, sockaddr_in & aAddr);
        // Èäåíòèôèêàòîð âëàäåëüöà
        SOCKET UID();
        // IP êëèåíòà
        string IP();
        // Äîáàâëåíèå ïàêåòà äëÿ îòïðàâêè
        void Send(TSocketBuffer * aBuffer);
    };

    // Èíòåðôåéñ êàëëáàêîâ
    class ISocketWrapper
    {
    public:
        // Íîâîå ñîåäèíåíèå
        virtual void OnConnect(TSocketConnection * aConnection);
        // Âûäà÷à ïðî÷èòàííîãî áóôåðà
        virtual void OnRead(TSocketConnection * aConnection, char * aBuffer, int aBufferSize);
		// Çàïðîñ áóôôåðà äëÿ îòïðàâêè
		virtual void OnWrite(TSocketConnection *& aConnection);
        // Ïîòåðÿ ñîåäèíåíèÿ
        virtual void OnDisconnect(TSocketConnection * aConnection);
    };

    // Êëàññ ñîêåòíîãî ñîåäèíåíèÿ
    class TSocket
    {
    private:
        // Ðàçìåð áóôåðà ÷òåíèÿ
        static const int I_BUFFER_LENGTH = 0xff;
        // Íàáîð êëèåíòîâ
        typedef std::map<SOCKET, TSocketConnection*> TSocketMap;
    private:
        // Áóôåð ÷òåíèÿ ïàêåòà
        char m_Buffer[I_BUFFER_LENGTH] = {};
        // Õåíäë ñëóøàþùåãî ïîòîêà
        TThread m_ThreadRead;
        // Õåíäë çàïèñûâàþùåãî ïîòîêà
        TThread m_ThreadWrite;
        // Ñîêåò ñëóøàþùåãî ñåðâåðà
        SOCKET m_ServerSocket = {};
        // Îáðàáîò÷èê ñîáûòèé
        ISocketWrapper * m_Wrapper;
        // Ñîïîñòàâëåííûå êëèåíòû
        TSocketMap m_Clients;
        // Ñîáèðàåìûé áóôåð ñîêåòîâ
        Sockets m_Sockets = {};
    private:
        // Âåñü æèçíåííûé öèêë èäåò âíóòðè ïîòîêà
        static void ExecuteRead(TSocket * aInstance);
        // Âåñü æèçíåííûé öèêë èäåò âíóòðè ïîòîêà
        static void ExecuteWrite(TSocket * aInstance);
        // Ëîãèðîâàíèå îøèáêè
        void Error();
        // Âûñòàâëåíèå íåáëîêèðóþùåãî ðåæèìà ñîêåòà
        bool SetNonBlock(SOCKET aSocket);
        // Ïîëó÷åíèå ñïèñêà êëèåíòîâ äëÿ m_d_set
        void SetClients();
        // Îáðàáîòêà ñîåäèíåíèé è ÷òåíèÿ
        void WorkRead();
        // Îáðàáîòêà ñîåäèíåíèé è çàïèñè
        void WorkWrite();
        // Ïîäêëþ÷åíèå íîâîãî êëèåíòà
        void Connect();
        // Ïîäêëþ÷åíèå íîâîãî êëèåíòà
        void Disconnect(SOCKET aSocket, TSocketConnection * aConnection);
    public:
        // Çàïóñê ñåðâåðà
        void Start(int aPort, ISocketWrapper * aWrapper);
        // Îñòàíîâêà ñåðâåðà
        void Stop();
    };
}