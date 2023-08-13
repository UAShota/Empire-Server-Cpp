/////////////////////////////////////////////////
//
// Флот: постройка и ремонт юнита              
// Copyright(c) 2016 UAshota                   
//
// Rev a  2017.12.18
// Rev D  2018.03.13
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"
#include "Modules/Planetar/Classes/PlanetarShip.h"
#include "Modules/Planetar/Classes/PlanetarPlanet.h"
#include "PlanetarShipControlCustom.h"

namespace planetar
{
    // Класс обработки постройки юнита
    class TShipControlConstruct : TShipControlCustom
    {
    private: 
        // Максимальное количество активных верфей
        static const int I_MAX_SHIPYARD_ACTIVE = 4;
    private:
        // Количество ХП добавляемого за тик
        int GetHPperTick(TShip * aShip);
        // Таймер события постройки
        bool OnTimer(TShip * aShip, int & ACounter, int & AValue);
    public:
        // Базовое выполнение
        TShip * Execute(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer);
        // Выполнение команды игрока
        void Player(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer);
    };
}