#pragma once

#include "Globals/Player.h"
#include "Modules/Planetar/Classes/PlanetarShip.h"
#include "Modules/Planetar/Classes/PlanetarPlanet.h"

namespace planetar
{
    class TPlanetarProtocolWriter
    {
    private:
        enum Commands
        {
            // Команда оповещение о загрузке созвездия
            CmdPlanetarStarted = 0x1000, /*непонятно пока*/
            // Команда запуска загрузки созвездия клиенту
            CMD_SYSTEM_LOAD_BEGIN = 0x1001,
            // Команда перемещения корабля
            Ship_MOVE_TO = 0x1002,
            // Команда создания корабля
            Ship_CREATE = 0x1003,
            // Команда удаления корабля
            Ship_DELETE = 0x1005,
            // Команда обновления таймера планеты
            Planet_UPDATE_TIMER = 0x1006,
            // Команда обновления HP корабля
            Ship_UPDATE_HP = 0x1007,
            // Команда смены аттача корабля
            Ship_CHANGE_ATTACH = 0x1008,
            // Команда смены цели корабля
            Ship_CHANGE_TARGET = 0x1009,
            // Команда обновления состояния корабля
            Ship_UPDATE_STATE = 0x100A,
            // Команда открытия портала
            Planet_PORTAL_OPEN = 0x100B,
            // Команда настройки хранилища игрока
            Player_STORAGE_CHANGE = 0x100C,
            // Команда обновления данных панели флота
            Player_HANGAR_UPDATE = 0x100D,
            // Команда показа окна деталей планеты
            Planet_DETAILS_SHOW = 0x100E,
            // Команда обновления данных хранилища планеты
            Planet_STORAGE_UPDATE = 0x100F,
            // Команда очистки слота хранилища планеты
            Planet_STORAGE_CLEAR = 0x1011,
            // Команда обновления данных хранилища игрока
            Player_STORAGE_UPDATE = 0x1012,
            // Команда загрузки технологий корабликов
            Player_TECH_WARShip_CREATE = 0x1013,
            // Команда обновления технологий корабликов
            Player_TECH_WARShip_UPDATE = 0x1014,
            // Команда завершения загрузки созвездия клиенту
            CMD_SYSTEM_LOAD_COMPLETE = 0x1015,
            // Команда загрузки технологий строений
            Player_TECH_BUILDING_CREATE = 0x1016,
            // Команда обновления данных строения
            Planet_BUILDING_UPDATE = 0x1017,
            // Команда обновления технологий строений
            Player_TECH_BUILDING_UPDATE = 0x1018,
            // Команда загрузки данных строений
            Connection_BUILDINGS_LOAD = 0x101A,
            // Команда загрузки данных корабликов
            Connection_WARShipS_LOAD = 0x101B,
            // Команда обновления состояние планетоида
            Planet_STATE_UPDATE = 0x101C,
            // Команда установки времени таймера переключения состояния
            Planet_STATE_TIME = 0x101D,
            // Команда обновления уровня видимости планетоида
            Planet_VISIBILITY_UPDATE = 0x101E,
            // Команда смены состояния подписки на планетоид
            Planet_SUBSCRIPTION_CHANGED = 0x101F,
            // Команда смены владельца планетоида
            Planet_OWNER_CHANGED = 0x1020,
            // Команда обновления типа покрытия планетоида
            Planet_COVERAGE_UPDATE = 0x1021,
            // Команда смены направления торгового пути
            Planet_TRADEPATH_UPDATE = 0x1022,
            // Команда закрытия портала
            Planet_PORTAL_CLOSE = 0x1023,
            // Команда обновления наличия электроэнергии
            Planet_ELECTRO_UPDATE = 0x1024,
            // Команда смены значения захвата планетоида
            Planet_CAPTURE_UPDATE = 0x1025,
            // Команда результата подписки на планетарку
            /*CMD_SYSTEM_LOAD_END = 0x1026,*/
            // Команда смены размера хранилища планетоида
            Planet_STORAGE_RESIZE = 0x1027,
            // Команда обновления количества модулей на планетоиде
            Planet_MODULES_UPDATE = 0x1028,
            // Команда обновления значения таймера кораблика
            Ship_UPDATE_TIMER = 0x1029,
            // Команда обновления параметров портала
            Planet_PORTAL_UPDATE = 0x1030,
            // Команда обновления признака низкой гравитации
            Planet_LOWGRAVITY_UPDATE = 0x1031,
            // Команда моментального перемещения корабля
            Ship_JUMP_TO = 0x1032,
            // Команда обновления уровня топлива
            Ship_REFILL = 0x1033
        };
    private:
        // Временный буффер записи
        transport::TSocketBuffer m_Buffer;
    public:/*/*/
        // Объект планетарного контроля
        class TPlanetarEngine * m_Engine = nullptr;
    private:
        // Цикл обработки
        void Work();
        // Создание корабля
        void ShipCreate(TShip * aShip, globals::TPlayer * aPlayer = nullptr);
        // Удаление корабля
        void ShipDelete(TShip * aShip, bool aExplosive);
        // Перемещение корабля
        void ShipMoveTo(TShip * aShip, TPlanet * aTargeTPlanet, int aTargetSlot);
        // Перемещение корабля
        void ShipJumpTo(TShip * aShip, TPlanet * aSourcePlanet, int aTargetSlot);
        // Обновление HP корабля
        void ShipUpdateHP(TShip * aShip);
        // Смена цели корабля
        void ShipRetarget(TShip * aShip, TShipWeaponType::E aWeapon, globals::TPlayer * aPlayer = nullptr);
        // Смена аттача корабля
        void ShipChangeAttach(TShip * aShip);
        // Обновление статуса корабля
        void ShipUpdateState(TShip * aShip);
        // Обновление заряда корабля
        void ShipRefill(TShip * aShip);
        // Обновление таймера корабля
        void ShipUpdateTimer(TShip * aShip, TShipTimer::E aTimer, int aSeconds);

        bool PlanetSubscribe(globals::TPlayer * aPlayer, TPlanet * aPlanet);
        bool PlanetUnsubscribe(globals::TPlayer * aPlayer, TPlanet * aPlanet);

        // Команда обновления подписки на планету
        void PlanetSubscriptionChange(TPlanet * aPlanet, bool aSubscribed, globals::TPlayer * aPlayer);
        // Команда смены владельца планетоида
        void PlanetOwnerChanged(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        // Команда обновления состояния планеты
        void PlanetStateUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        // Команда обновления покрытия планетоида
        void PlanetCoverageUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer, bool aIncrement);
        // Команда обновления видимости планетоида
        void PlanetVisibilityUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer, bool aHardLight, bool aIncrement);
        void PlanetPortalOpen(TPlanet * aSource, TPlanet * aTarget, bool aEnter, globals::TPlayer * aPlayer = nullptr);
        void PlanetPortalUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        void PlanetPortalClose(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        void PlanetCaptureUpdate(TPlanet * aPlanet);
        void PlanetLowGravityUpdate(TPlanet * aPlanet, bool aEnabled, globals::TPlayer * aPlayer = nullptr);
        void PlanetEnergyUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        void PlanetModulesUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        void PlanetTradePathUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        void PlanetStorageResize(TPlanet * aPlanet, bool aClear, globals::TPlayer * aPlayer = nullptr);
        void PlanetUpdateTimer(TPlanet * aPlanet, TPlanetTimer::E aTimer, int aSeconds);
        // Команда отображения деталей планеты
        void PlanetDetailsShow(TPlanet * aPlanet, globals::TPlayer * aPlayer);
        // Команда обновления деталей строения
        /*void PlanetBuildingUpdate(TBuilding * aBuiling, Globals::TPlayer * aPlayer = nullptr);*/
        // Команда обновления данных хранилища
        /*void PlanetStorageUpdate(TPlanet * aPlanet, TStorage * aStorage, Globals::TPlayer * aPlayer = nullptr);*/
        // Команда очистки хранилища
        void PlanetStorageClear(TPlanet * aPlanet, int aIndex);
        // Команда обновления ангара игрока
        void PlayerHangarUpdate(int aSlot, int aCount, TShipType::E aShipType, globals::TPlayer * aPlayer);
        // Команда создания хранилища игрока
        /*void PlayerStorageChange(int aSize, aHoldings : TGlStorageList, aPlayer : TGlPlayer);*/
        // Команда обновления хранилища игрока
        /*void PlayerStorageUpdate(aIndex: Int, aHolding : TGlStorageHolder, aPlayer : TGlPlayer);*/
        // Команда загрузки технологий кораблика
        void PlayerTechWarShipLoad(TShipTechProfile * aTechList, TShipTechValues * aPlayerList, globals::TPlayer * aPlayer);
        // Команда обновления технологии кораблика
        void PlayerTechWarShipUpdate(TShipType::E aShipType, TShipTech::E aTechType, globals::TPlayer * aPlayer);
        // Команда загрузки технологий зданий
        /*void PlayerTechBuildingLoad(TBuildingTechProfile * aTechList,  aUserList: TBuildingTechValues, aPlayer : TGlPlayer);*/
        // Команда обновления технологии здания
        /*void PlayerTechBuildingUpdate(aBuildingType: TBuildingType; TPlayer * aPlayer);*/
        // Отправка данных строений
        /*void ConnectionBuildingsLoad(aBuildings: TBuildingConnectionList, aPlayer : TGlPlayer);*/

        // Сообщение о завершении загрузки созвездия
        void SystemLoadEnd(globals::TPlayer * aPlayer);

        // Разрешение клиенту на подключение к галактике
        void GalaxyLoadAccept(globals::TPlayer * aPlayer);
        void GalaxyLoadBegin(globals::TPlayer * aPlayer);


    public:
        // Разрешение клиенту на подключение к созвездию
        void PlanetarStarted(globals::TPlayer * aPlayer);
        // Уведомление о результате подписки на планетарку
        void PlanetarSubscribe(globals::TPlayer * aPlayer);
    };
}