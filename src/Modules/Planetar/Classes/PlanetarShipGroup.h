//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "PlanetarShip.h"
#include "PlanetarPlanet.h"

namespace planetar
{
    // �������� ������ ��������
    class TShipGroup
    {
    private:
        // �����, � ������� ������������ ��������� ���������
        TShip * m_Slots[5] = {};
        // ������� ���������� ������������ �������
        int * m_Position = nullptr;
        // ������ �������� � ������
        TShipList * m_Ships = nullptr;
        // ������ ������ � ���� �������� ������
        /*TPlanetList * m_Planets = nullptr;*/
    private:
        // ���������� �������� � ���������� �������
        void SortByPriority();
        // ���������� �������� � ������ ������
            // TODO - omdv : ��������� ����������� ��������� ����������
        void SortBySlot();
    public:
        /*TShipGroup(TPlanetList * aPlanetList, TShipList * aShipList);*/
        ~TShipGroup();
        // �������� ������� �� ������(��������, ������� � �����, ����� ����)
        void Remove(TShip * aShip);
    };
}