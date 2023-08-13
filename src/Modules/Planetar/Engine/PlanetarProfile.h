//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "PlanetarEngine.h"
#include "Modules/Planetar/Classes/PlanetarHangar.h"
#include "Modules/Planetar/Classes/PlanetarShip.h"

namespace globals
{
    class TPlayer;
}

/*        // Отправим данные технологий корабликов
        SocketWriter.PlayerTechWarShipLoad(tmpProfile.TechShipProfile, tmpProfile.TechShipValues, aPlayer);
        // Отправим данные технологий строений
        SocketWriter.PlayerTechBuildingLoad(tmpProfile.TechBuildingProfile, tmpProfile.TechBuildingValues, aPlayer);
                // Отправим размер хранилища
        SocketWriter.PlayerStorageChange(aPlayer.Storage.Size, aPlayer.Storage.Storages, aPlayer);
        // Отправим ангар
        for tmpI : = 0 to TPlanetar(aPlayer.Planetar).Hangar.Size do
            begin
            SocketWriter.PlayerHangarUpdate(tmpI,
                TPlanetar(aPlayer.Planetar).Hangar.Slots[tmpI].Count,
                TPlanetar(aPlayer.Planetar).Hangar.Slots[tmpI].ShipType, aPlayer);
        end;

*/

namespace planetar
{
    // Класс управления планетарным профилем
    class TProfile
    {
    private:
        // Игрок владеющий профилем
        class globals::TPlayer * m_Player = nullptr;
        // Ссылка на свое созвездие
        TPlanetarEngine * m_Engine = nullptr;
        // Ссылка на созвездие подписки
        TPlanetarEngine * m_Subscribe = nullptr;
        // Планетарный ангар профиля
        THangar m_Hangar;
        // Купленные техи игрока
        TShipTechValues * m_TechShipValues = nullptr;
        // Ссылка на техи расы игрока
        TShipTechProfile * m_TechShipProfile = nullptr;
        // Купленные техи строения
    /*TechBuildingValues: TPlBuildingTechValues;
        // Ссылка на техи расы игрока
    TechBuildingProfile: PPlBuildingTechProfile;*/
    private:
        // Загрузка технологий корабликов
        void LoadTechWarShips();
        // Загрузка технологий строений
        void LoadTechBuildings();
        // Загрузка ангара
        void LoadHangar();
    public:
        // Конструктор
        TProfile(globals::TPlayer * aPlayer);
        // Загрузка профиля
        void Start();
        // Выгрузка профиля
        void Stop();
        // Признак доступности созвездия
        bool Available();
        // Подписка указанного игрока к текущей планетарке
        bool Subscribe(globals::TPlayer * aPlayer);
        // Отписка текущего игрока
        void Unsubscribe();
        // Отправка команды в созвездие
        bool Command();

        // Покупка технологии кораблика
        void BuyTech(TShipType::E aShipType, TShipTech::E aTech, globals::TPlayer * aPlayer);
        // Покупка технологии строения
        /*procedure BuyTech(aBuildingType: TPlBuildingType; aPlayer: TGlPlayer); overload;*/
        // Купленная технология указанного кораблика
        TShipTechItem * Tech(TShipType::E aShipType, TShipTech::E aTech);
        // Купленная технология указанного строения
        /*function TechBuilding(aBuildingType: TPlBuildingType; aTech: TPlBuildingTechType) : Int; overload;*/
    };
}