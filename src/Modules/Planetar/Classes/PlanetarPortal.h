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
#include "PlanetarPlanet.h"

namespace planetar
{
    // Объект планетарного портала
    class TPortal
    {
    public:
        // Создатель
        globals::TPlayer * Owner = nullptr;
        // Планета входа
        TPlanet * Enter = nullptr;
        // Планета выхода
        TPlanet * Exit = nullptr;
        // Лимит перемещений
        int Limit = 0;
        // Возможность перебить
        bool Breakable = false;
        // Быстрый переброс(чт)
        bool m_astTransfer = false;
    public:
        TPortal() noexcept;
        ~TPortal();
    };
}