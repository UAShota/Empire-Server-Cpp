/////////////////////////////////////////////////
//
// ���� : ����� �������          
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
    // ����� ��������� ����� ������� �����
    class TShipControlCustom
    {
    protected:
        static const int I_MAX_SHIP_COUNT = 6;
        static const int I_MAX_SHIP_ACTIVE = I_MAX_SHIP_COUNT - 1;
        static const int I_MAX_SHIP_REFILL = I_MAX_SHIP_ACTIVE - 1;
        static const int I_MAX_FUEL_COUNT = 5;
        static const int I_FUEL_FOR_HANGAR = 2;
    protected:
        // ������ ����������� �������
        TPlanetarEngine * m_Engine;
    protected:
        // �������� ������� �������
        TShip * CreateShip(TPlanet * aPlanet, TShipType::E aShipType, int aSlot, int aCount, globals::TPlayer * aPlayer);
        // �����������, �������� �� �������� �����������
        TShip * CheckShipBlocker(TShip * aShip, int aSlot, bool aEnemy, TShipMode::E aWantMode);
        // ����� ��������� �������, ������� ����� �������� ������������
        TShip * CheckShipSide(TPlanet * aDestination, int aSlot, TShipMode::E aWantMode);
        // �������� ����������� ������� ������� �� ������
        bool CheckArrival(TPlanet * aDestination, bool aShipLowOrbit, int aSlotFrom, int aSlotTo,
            TPlanet * aShipPlanet, globals::TPlayer * aShipOwner, bool aCheckOnePlanet);
        // �������� �� ����������� ������� � ���
        bool CheckMoveTo(TShip * aShip, TPlanet * aDestination, int aSlotTo, bool aCheckOnePlanet);
        // �������� ����������� ������� ������� �� ����
        bool CheckBackZone(bool aIgnoreBackZone, TPlanet * aDestination, int aSlot, globals::TPlayer * aOwner);
        // �������� ��������� ����
        int GetFreeSlot(bool aIgnore, TPlanet * aDestination, bool aShipLowOrbit, globals::TPlayer * aOwner);
        // ��������� ����� �����
        int DealDamage(TShip * aShip, int aDamage, bool aDestruct = true);
        // ���������� �� ��� �������� ������� �����
        void WorkShipHP(TPlanet * aPlanet);
    public:
        TShipControlCustom(TPlanetarEngine * aThread) noexcept;
    };
}