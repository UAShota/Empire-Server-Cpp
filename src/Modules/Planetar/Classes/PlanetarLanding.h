//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Resource.h"
#include "PlanetarShip.h"

namespace planetar
{
    // ����� ����������� ������� ����� �������
    struct TLandingObjects
    {
        // ��������
        TShip * Ship;
        // ������
        globals::TResource * Resource;
    };

    // ����� ����������� ���������� ����� ����������
    class TLandings
    {
    public:
        // ���������� ������ ������
        static const int I_FIGHT_COUNT = 15;
        // ���������� ��������� ������
        static const int I_TOTAL_COUNT = I_FIGHT_COUNT + 5;
    private:
        // ������ ���������� ����
        TLandingObjects	m_Landings[I_TOTAL_COUNT] = {};
    public:
        // ���������� ������� � ����
        void Add(TShip * aShip);
        // �������� ������� � �����
        void Remove(TShip * aShip);
        // �������� �� ������� �������
        bool HaveShip(int aPosition, TShip * aShip);
    };

    // ��� ������������ �����
    class TLanding
    {
    public:
        int Position;
        /*
        // ��������� ������� �� ��������� ����
       m_unction Inc() : TPlLanding;
        // ��������� ������� �� ���������� ����
       m_unction Dec() : TPlLanding;
        // ��������� �� ��������� ����
       m_unction Next() : TPlLanding;
        // ��������� �� ���������� ����
       m_unction Prev() : TPlLanding;
        // ������� ������ ������ �����
       m_unction IsLowOrbit() : Boolean;
        public
            // ���� ��� ���������� ��������
            class m_unction Offset(aValue : Int) : TPlLanding; static;
        // ���������� ������ �����
        class m_unction Valid(aValue : Int) : Boolean; static;*/
    };
}