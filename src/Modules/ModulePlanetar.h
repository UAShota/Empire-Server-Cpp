/////////////////////////////////////////////////
//
// Модуль управления планетарной зоной
// Copyright(c) 2016 UAShota
//
// Rev F  2018.10.24
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"

namespace planetar
{
    // Класс планетарной зоны
    class TPlanetar
    {
    private:
        // Ошибки
        enum Errors
        {
            // Ошибок нет
            ERR_SUCCESS = 0,
            // Система не загружена
            ERR_SYSTEM_UNLOADED = 0x1F01,
            // Система не активна
            ERR_SYSTEM_UNAVAILABLE = 0x1F02
        };
        // Комманды
        enum Commands
        {
            // Запрос активности созвездия
            CMD_AVAILABLE = 0x1F01,
            // Подписка на созвездие
            CMD_SUBSCRIBE = 0x1F02
        };
    private:
        // Локальный буфер отправки команд
        transport::TSocketBuffer m_Buffer;
        // Текущий игрок обработки
        globals::TPlayer * m_Player = nullptr;
    private:
        // Считывание кода планетарки и поиск сопоставленного профиля
        globals::TPlayer * FindPlayer(int & aPlanetarID, int & aErrorCode);
        // Загрузка боток
        void LoadAutoPlanetars();
        // Отправка признака доступности
        void SendAvailable(int aPlanetarID, int aErrorCode);
        // Признак доступности планетарки игрока
        void CheckAvailable();
        // Подключение к планетарке
        void Subscribe();
        // Перенаправление команды планетарке
        void Retranslate();
    public:
        // Запуск модуля
        void Start();
        // Остановка модуля
        void Stop();
        // Команда на обработку
        void Command(transport::TSocketConnection * aConnection);
    };
}