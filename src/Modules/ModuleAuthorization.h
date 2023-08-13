/////////////////////////////////////////////////
//
// Модуль управления управляющим сервером
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
    // Класс управления подсистемами
    class TAuthorization
    {
    private:
        // Список ошибок
        enum Errors
        {
            // Ошибка - неверно указан логин или пароль
            ERR_INVALID_CREDENTIALS = 1
        };
        // Команды авторизации
        enum Commands
        {
            // Комманда сообщения чата
            CMD_CHAT_MESSAGE = 0x0001,
            // Комманда запроса авторизации
            CMD_LOGIN_AUTH = 0x0002,
            // Комманда некорректной авторизации
            CMD_LOGIN_FAILED = 0x0003,
            // Комманда успешной авторизации
            CMD_LOGIN_ACCEPT = 0x0004,
            // Комманда оповещения о повторном подключении
            CMD_LOGIN_RELOG = 0x0005
        };
    private:
        // Последний запрошенный UID
        int m_LastPlayerUID = 0;
        // Последний запрошенный профиль
        globals::TPlayer * m_LastPlayer = nullptr;
        // Список игроков
        globals::TPlayerMap m_Players = {};
        // Текущая команда обработки
        transport::TSocketBuffer * m_BufferRead;
        // Текущая команда записи
        transport::TSocketBuffer m_BufferWrite;
        // Поток обработки команды
        TThread m_Thread;
        // Очередь команд
        TAsyncQueueSignal<transport::TSocketBuffer*> m_Queue;
    private:
        // Весь жизненный цикл идет внутри потока
        static void Execute(TAuthorization * aInstance);
        // Внутренности потока
        void WorkRead();
        // Авторизация игрока успешна
        void ResponseLoginAccept(globals::TPlayer * aPlayer);
        // Авторизация игрока провалена
        void ResponseLoginFailed();
        // Авторизация игрока
        bool CmdLogin();
        // Загрузка профиля игрока
        globals::TPlayer *LoadPlayer(int aUID);
    public:
        // Запуск модуля
        void Start();
        // Остановка модуля
        void Stop();
        // Команда на обработку
        void Command(transport::TSocketConnection * aConnection);
        // Поиск игрока по идентификатору
        globals::TPlayer * FindPlayer(int aUID, bool aLoad);
        // Отправка сообщения в чат игрока
        /*void ChatMessage(const char * aText, Globals::TPlayer * aPlayer = nullptr);*/
    };
}