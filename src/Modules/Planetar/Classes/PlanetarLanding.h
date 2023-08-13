//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
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
    // Класс описывающий объекты слота посадки
    struct TLandingObjects
    {
        // Кораблик
        TShip * Ship;
        // Ресурс
        globals::TResource * Resource;
    };

    // Класс описывающий посадочные места планетоида
    class TLandings
    {
    public:
        // Количество боевых слотов
        static const int I_FIGHT_COUNT = 15;
        // Количество доступных слотов
        static const int I_TOTAL_COUNT = I_FIGHT_COUNT + 5;
    private:
        // Массив посадочных мест
        TLandingObjects	m_Landings[I_TOTAL_COUNT] = {};
    public:
        // Добавление корабля в слот
        void Add(TShip * aShip);
        // Удаление корабля с слота
        void Remove(TShip * aShip);
        // Проверка на наличие корабля
        bool HaveShip(int aPosition, TShip * aShip);
    };

    // Тип планетарного слота
    class TLanding
    {
    public:
        int Position;
        /*
        // Сохранить переход на следующий слот
       m_unction Inc() : TPlLanding;
        // Сохранить переход на предыдущий слот
       m_unction Dec() : TPlLanding;
        // Указатель на следующий слот
       m_unction Next() : TPlLanding;
        // Указатель на предыдущий слот
       m_unction Prev() : TPlLanding;
        // Признак нижней орбиты слота
       m_unction IsLowOrbit() : Boolean;
        public
            // Слот для указанного значения
            class m_unction Offset(aValue : Int) : TPlLanding; static;
        // Валидность номера слота
        class m_unction Valid(aValue : Int) : Boolean; static;*/
    };
}