/////////////////////////////////////////////////
//
// Флот: поиск локальной цели для атаки      
// Copyright(c) 2016 UAshota                   
//
// Rev a  2017.12.18
// Rev D  2018.03.13
//
/////////////////////////////////////////////////

#pragma once

#include "Modules/Planetar/Control/Ships/PlanetarShipControlCustom.h"

namespace planetar
{
    class TShipControlTargetLocal : TShipControlCustom
    {
    private:
        // Определить, какой кораблик из двух более приоритетен
        bool GetShipPriority(TShip * aLeft, TShip * aRight);
        // Получить расстояния между двумя корабликами
        int GetShipRange(TShip * aLeft, TShip * aRight);
        // Определить, какой кораблик из двух ближе к указанному
        bool GetShipNear(TShip * aCenter, TShip * aLeft, TShip * aRight);
        // Прицел в лоб
        bool GetTargetingToHead(TShip * aShip, TShip * aRightShip, TShip * aLeftShip, TShip * & AWeapone);
        // Прицел в лоб в два края
        bool GetTargetingToCorners(TShip * aShip, TShip * aRightShip, TShip * aLeftShip);
        // Прицел в лоб с прострелом через цель
        bool GetTargetingToInner(TShip * aShip, TShip * aRightShip, TShip * aLeftShip,
            TShip * aRightShipInner, TShip * aLeftShipInner);
        // Прицел в две ближние цели
        bool GetTargetingToDouble(TShip * aShi, TShip * aRightShip, TShip * aLeftShip,
            TShip * aRightShipInner, TShip * aLeftShipInner);
        // Поиск противника для атаки
        TShip * GetTargetShip(TShip * aShip, bool aIgnoreFriend, bool aLeft, bool aOneStep,
            globals::TPlayer * aOwner);
        // Прицеливание прострельным орудием
        bool GetWeaponeOvershot(TShip * aShip);
        // Прицеливание лазерами и ракетами
        bool GetWeaponeOverFriends(TShip * aShi, TShip * *AWeapone);
        // Прицеливание двойными лазерами
        bool GetWeaponeDoubleLaser(TShip * aShip);
        // Прицеливание двойными пулями
        bool GetWeaponeDoubleBullet(TShip * aShip);
        // Прицеливание пулей
        bool GetWeaponeBullet(TShip * aShip);
    public:
        // Базовое выполнение
        void Execute(TShip * aShip);
    };
}