//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"
#include "Modules/Planetar/Protocol/PlanetarProtocolReader.h"
#include "Modules/Planetar/Protocol/PlanetarProtocolWriter.h"

namespace planetar
{
    // Класс обработчика всех процессов планетарки
    class TPlanetarEngine
    {
    private:
        // Объект потока
        TThread m_Thread;
        // Признак доступности созвездия
        bool m_Available = false;
        // Список планет
        TPlanet::Map m_Planets;

        // Ссылка на глобальный объект игрока
        globals::TPlayer * m_Player = nullptr;
        // Подключенные к созвездию клиенты
           /*Clients: TPlClientsDict;
                // Контроллер строений
           ControlBuildings: TPlanetarBuildingsController;
                // Контоллер планет
           ControlPlanets: TPlanetarPlanetsController;
                // Контроллер кораблей
           ControlShips: TPlanetarShipsController;
                // Контроллер хранилищ
           ControlStorages: TPlanetarStorageController;
           */        
           // Количество захваченных планет
        int MannedCount = 0;
        // Время активности пульсара
        int TimePulsarActive = 0;
        // Время активности ЧТ
        int TimeWormholeActive = 0;
        // Время открытия ЧТ
        int TimeWormholeOpen = 0;
        // Обработка корабликов
           /*WorkerShips: TPlanetarWorkerShips;
                // Обработка планет
           WorkerPlanets: TPlanetarWorkerPlanets;
           */
           // Сокет чтения
        TPlanetarProtocolReader m_SocketReader;
        // Сокет записи
        TPlanetarProtocolWriter m_SocketWriter;
        // Размер созвездия по вертикали
        int m_SizeX = 0;
        // Размер созвездия по горизонтали
        int m_SizeY = 0;
    private:
        // Весь жизненный цикл идет внутри потока
        static void Execute(TPlanetarEngine * aInstance);
    private:
        // Загрузка параметров созвездия
        void LoadParams();
        // Внутри потока
        void Work();
    public:
        TPlanetarEngine(class globals::TPlayer * aPlayer);
        ~TPlanetarEngine();
        // Размер созвездия по X
        int SizeX();
        // Размер созвездия по Y
        int SizeY();
        // Планеты системы
        TPlanet::Map Planets();
        // Признак загруженного созвездия
        bool Available();
        // Команда в очередь созвездия
        bool Command(class globals::TPlayer * aPlayer);
        // Подключение к системе
        void Subscribe(globals::TPlayer * aPlayer);
        // Отключение от системы
        void Unsubscribe(globals::TPlayer * aPlayer);
    };
}