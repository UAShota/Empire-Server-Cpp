/////////////////////////////////////////////////
//
// Флот : общие функции          
// Copyright(c) 2016 UAshota                   
//
// Rev a  2017.12.18
// Rev D  2018.03.13
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"
#include "Modules/Planetar/Engine/PlanetarEngine.h"
#include "Modules/Planetar/Classes/PlanetarShip.h"
#include "Modules/Planetar/Classes/PlanetarPlanet.h"
#include "Modules/Planetar/Classes/PlanetarLanding.h"

namespace planetar
{
    // Класс обработки общих функций флота
    class TShipControlCustom
    {
    protected:
        static const int I_MAX_SHIP_COUNT = 6;
        static const int I_MAX_SHIP_ACTIVE = I_MAX_SHIP_COUNT - 1;
        static const int I_MAX_SHIP_REFILL = I_MAX_SHIP_ACTIVE - 1;
        static const int I_MAX_FUEL_COUNT = 5;
        static const int I_FUEL_FOR_HANGAR = 2;
    protected:
        // Объект планетарной системы
        TPlanetarEngine * m_Engine;
    protected:
        // Создание объекта корабля
        TShip * CreateShip(TPlanet * aPlanet, TShipType::E aShipType, int aSlot, int aCount, globals::TPlayer * aPlayer);
        // Определение, является ли кораблик блокирующим
        TShip * CheckShipBlocker(TShip * aShip, int aSlot, bool aEnemy, TShipMode::E aWantMode);
        // Поиск соседнего корабля, который имеет свойства блокирующего
        TShip * CheckShipSide(TPlanet * aDestination, int aSlot, TShipMode::E aWantMode);
        // Проверка возможности прилета корабля на орбиту
        bool CheckArrival(TPlanet * aDestination, bool aShipLowOrbit, int aSlotFrom, int aSlotTo,
            TPlanet * aShipPlanet, globals::TPlayer * aShipOwner, bool aCheckOnePlanet);
        // Проверка на возможность прилета и тыл
        bool CheckMoveTo(TShip * aShip, TPlanet * aDestination, int aSlotTo, bool aCheckOnePlanet);
        // Проверка возможности посадки корабля на слот
        bool CheckBackZone(bool aIgnoreBackZone, TPlanet * aDestination, int aSlot, globals::TPlayer * aOwner);
        // Получить свободный слот
        int GetFreeSlot(bool aIgnore, TPlanet * aDestination, bool aShipLowOrbit, globals::TPlayer * aOwner);
        // Нанесение урона юниту
        int DealDamage(TShip * aShip, int aDamage, bool aDestruct = true);
        // Обновление ХП или удаление убитого стека
        void WorkShipHP(TPlanet * aPlanet);
    public:
        TShipControlCustom(TPlanetarEngine * aThread) noexcept;
    };
}