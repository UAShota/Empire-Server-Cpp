/////////////////////////////////////////////////
//
// ����: ����� ��������� ���� ��� �����      
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
        // ����������, ����� �������� �� ���� ����� �����������
        bool GetShipPriority(TShip * aLeft, TShip * aRight);
        // �������� ���������� ����� ����� �����������
        int GetShipRange(TShip * aLeft, TShip * aRight);
        // ����������, ����� �������� �� ���� ����� � ����������
        bool GetShipNear(TShip * aCenter, TShip * aLeft, TShip * aRight);
        // ������ � ���
        bool GetTargetingToHead(TShip * aShip, TShip * aRightShip, TShip * aLeftShip, TShip * & AWeapone);
        // ������ � ��� � ��� ����
        bool GetTargetingToCorners(TShip * aShip, TShip * aRightShip, TShip * aLeftShip);
        // ������ � ��� � ���������� ����� ����
        bool GetTargetingToInner(TShip * aShip, TShip * aRightShip, TShip * aLeftShip,
            TShip * aRightShipInner, TShip * aLeftShipInner);
        // ������ � ��� ������� ����
        bool GetTargetingToDouble(TShip * aShi, TShip * aRightShip, TShip * aLeftShip,
            TShip * aRightShipInner, TShip * aLeftShipInner);
        // ����� ���������� ��� �����
        TShip * GetTargetShip(TShip * aShip, bool aIgnoreFriend, bool aLeft, bool aOneStep,
            globals::TPlayer * aOwner);
        // ������������ ������������ �������
        bool GetWeaponeOvershot(TShip * aShip);
        // ������������ �������� � ��������
        bool GetWeaponeOverFriends(TShip * aShi, TShip * *AWeapone);
        // ������������ �������� ��������
        bool GetWeaponeDoubleLaser(TShip * aShip);
        // ������������ �������� ������
        bool GetWeaponeDoubleBullet(TShip * aShip);
        // ������������ �����
        bool GetWeaponeBullet(TShip * aShip);
    public:
        // ������� ����������
        void Execute(TShip * aShip);
    };
}