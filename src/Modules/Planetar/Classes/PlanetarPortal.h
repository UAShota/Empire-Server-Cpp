//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"
#include "PlanetarPlanet.h"

namespace planetar
{
    // ������ ������������ �������
    class TPortal
    {
    public:
        // ���������
        globals::TPlayer * Owner = nullptr;
        // ������� �����
        TPlanet * Enter = nullptr;
        // ������� ������
        TPlanet * Exit = nullptr;
        // ����� �����������
        int Limit = 0;
        // ����������� ��������
        bool Breakable = false;
        // ������� ��������(��)
        bool m_astTransfer = false;
    public:
        TPortal() noexcept;
        ~TPortal();
    };
}