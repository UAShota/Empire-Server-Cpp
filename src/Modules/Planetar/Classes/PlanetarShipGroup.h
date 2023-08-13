//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
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
    // Описание группы кораблей
    class TShipGroup
    {
    private:
        // Слоты, в которые составляются выбранные кораблики
        TShip * m_Slots[5] = {};
        // Позиция последнего добавленного корабля
        int * m_Position = nullptr;
        // Список кораблей в группе
        TShipList * m_Ships = nullptr;
        // Список планет в пути перелета группы
        /*TPlanetList * m_Planets = nullptr;*/
    private:
        // Построение кораблей в защищенную коробку
        void SortByPriority();
        // Построение кораблей в сжатую группу
            // TODO - omdv : Групповое перемещение упростить сортировку
        void SortBySlot();
    public:
        /*TShipGroup(TPlanetList * aPlanetList, TShipList * aShipList);*/
        ~TShipGroup();
        // Удаление корабля из группы(убийство, перенос в ангар, смена пути)
        void Remove(TShip * aShip);
    };
}