/////////////////////////////////////////////////
//
// Модуль управления распределением команд
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
        // Движок распределения пакетов
        server::TAuthorization m_Auth;
        // Движок планетарных действий
        planetar::TPlanetar m_Planetar;
        // Сокетное соединение
        transport::TSocket m_Socket;
        // Очередь сокетных сообщений
        TAsyncQueueSignal<transport::TSocketConnection*> m_Queue;
    public:
        // Старт
        void Start();
        // Остановка
        void Stop();
        // Каллбак подключения клиента
        void OnConnect(transport::TSocketConnection * aConnection);
        // Каллбак чтения клиента
        void OnRead(transport::TSocketConnection * aConnection, char * aBuffer, int aBufferSize);
        // Каллбак записи клиента
        void OnWrite(transport::TSocketConnection ** aConnection);
        // Каллбак отключения клиента
        void OnDisconnect(transport::TSocketConnection * aConnection);
        // Поиск игрока по идентификатору
        globals::TPlayer * FindPlayer(int aID, bool aLoad);
        // Отправка пакета
        void Send(transport::TSocketConnection * aConnection);
    };
}