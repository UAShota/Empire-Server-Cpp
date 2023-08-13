/////////////////////////////////////////////////
//
// ����: ��������� � ������ �����              
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
    // ����� ��������� ��������� �����
    class TShipControlConstruct : TShipControlCustom
    {
    private: 
        // ������������ ���������� �������� ������
        static const int I_MAX_SHIPYARD_ACTIVE = 4;
    private:
        // ���������� �� ������������ �� ���
        int GetHPperTick(TShip * aShip);
        // ������ ������� ���������
        bool OnTimer(TShip * aShip, int & ACounter, int & AValue);
    public:
        // ������� ����������
        TShip * Execute(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer);
        // ���������� ������� ������
        void Player(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer);
    };
}