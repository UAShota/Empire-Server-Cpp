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
            // ������� ���������� � �������� ���������
            CmdPlanetarStarted = 0x1000, /*��������� ����*/
            // ������� ������� �������� ��������� �������
            CMD_SYSTEM_LOAD_BEGIN = 0x1001,
            // ������� ����������� �������
            Ship_MOVE_TO = 0x1002,
            // ������� �������� �������
            Ship_CREATE = 0x1003,
            // ������� �������� �������
            Ship_DELETE = 0x1005,
            // ������� ���������� ������� �������
            Planet_UPDATE_TIMER = 0x1006,
            // ������� ���������� HP �������
            Ship_UPDATE_HP = 0x1007,
            // ������� ����� ������ �������
            Ship_CHANGE_ATTACH = 0x1008,
            // ������� ����� ���� �������
            Ship_CHANGE_TARGET = 0x1009,
            // ������� ���������� ��������� �������
            Ship_UPDATE_STATE = 0x100A,
            // ������� �������� �������
            Planet_PORTAL_OPEN = 0x100B,
            // ������� ��������� ��������� ������
            Player_STORAGE_CHANGE = 0x100C,
            // ������� ���������� ������ ������ �����
            Player_HANGAR_UPDATE = 0x100D,
            // ������� ������ ���� ������� �������
            Planet_DETAILS_SHOW = 0x100E,
            // ������� ���������� ������ ��������� �������
            Planet_STORAGE_UPDATE = 0x100F,
            // ������� ������� ����� ��������� �������
            Planet_STORAGE_CLEAR = 0x1011,
            // ������� ���������� ������ ��������� ������
            Player_STORAGE_UPDATE = 0x1012,
            // ������� �������� ���������� ����������
            Player_TECH_WARShip_CREATE = 0x1013,
            // ������� ���������� ���������� ����������
            Player_TECH_WARShip_UPDATE = 0x1014,
            // ������� ���������� �������� ��������� �������
            CMD_SYSTEM_LOAD_COMPLETE = 0x1015,
            // ������� �������� ���������� ��������
            Player_TECH_BUILDING_CREATE = 0x1016,
            // ������� ���������� ������ ��������
            Planet_BUILDING_UPDATE = 0x1017,
            // ������� ���������� ���������� ��������
            Player_TECH_BUILDING_UPDATE = 0x1018,
            // ������� �������� ������ ��������
            Connection_BUILDINGS_LOAD = 0x101A,
            // ������� �������� ������ ����������
            Connection_WARShipS_LOAD = 0x101B,
            // ������� ���������� ��������� ����������
            Planet_STATE_UPDATE = 0x101C,
            // ������� ��������� ������� ������� ������������ ���������
            Planet_STATE_TIME = 0x101D,
            // ������� ���������� ������ ��������� ����������
            Planet_VISIBILITY_UPDATE = 0x101E,
            // ������� ����� ��������� �������� �� ���������
            Planet_SUBSCRIPTION_CHANGED = 0x101F,
            // ������� ����� ��������� ����������
            Planet_OWNER_CHANGED = 0x1020,
            // ������� ���������� ���� �������� ����������
            Planet_COVERAGE_UPDATE = 0x1021,
            // ������� ����� ����������� ��������� ����
            Planet_TRADEPATH_UPDATE = 0x1022,
            // ������� �������� �������
            Planet_PORTAL_CLOSE = 0x1023,
            // ������� ���������� ������� ��������������
            Planet_ELECTRO_UPDATE = 0x1024,
            // ������� ����� �������� ������� ����������
            Planet_CAPTURE_UPDATE = 0x1025,
            // ������� ���������� �������� �� ����������
            /*CMD_SYSTEM_LOAD_END = 0x1026,*/
            // ������� ����� ������� ��������� ����������
            Planet_STORAGE_RESIZE = 0x1027,
            // ������� ���������� ���������� ������� �� ����������
            Planet_MODULES_UPDATE = 0x1028,
            // ������� ���������� �������� ������� ���������
            Ship_UPDATE_TIMER = 0x1029,
            // ������� ���������� ���������� �������
            Planet_PORTAL_UPDATE = 0x1030,
            // ������� ���������� �������� ������ ����������
            Planet_LOWGRAVITY_UPDATE = 0x1031,
            // ������� ������������� ����������� �������
            Ship_JUMP_TO = 0x1032,
            // ������� ���������� ������ �������
            Ship_REFILL = 0x1033
        };
    private:
        // ��������� ������ ������
        transport::TSocketBuffer m_Buffer;
    public:/*/*/
        // ������ ������������ ��������
        class TPlanetarEngine * m_Engine = nullptr;
    private:
        // ���� ���������
        void Work();
        // �������� �������
        void ShipCreate(TShip * aShip, globals::TPlayer * aPlayer = nullptr);
        // �������� �������
        void ShipDelete(TShip * aShip, bool aExplosive);
        // ����������� �������
        void ShipMoveTo(TShip * aShip, TPlanet * aTargeTPlanet, int aTargetSlot);
        // ����������� �������
        void ShipJumpTo(TShip * aShip, TPlanet * aSourcePlanet, int aTargetSlot);
        // ���������� HP �������
        void ShipUpdateHP(TShip * aShip);
        // ����� ���� �������
        void ShipRetarget(TShip * aShip, TShipWeaponType::E aWeapon, globals::TPlayer * aPlayer = nullptr);
        // ����� ������ �������
        void ShipChangeAttach(TShip * aShip);
        // ���������� ������� �������
        void ShipUpdateState(TShip * aShip);
        // ���������� ������ �������
        void ShipRefill(TShip * aShip);
        // ���������� ������� �������
        void ShipUpdateTimer(TShip * aShip, TShipTimer::E aTimer, int aSeconds);

        bool PlanetSubscribe(globals::TPlayer * aPlayer, TPlanet * aPlanet);
        bool PlanetUnsubscribe(globals::TPlayer * aPlayer, TPlanet * aPlanet);

        // ������� ���������� �������� �� �������
        void PlanetSubscriptionChange(TPlanet * aPlanet, bool aSubscribed, globals::TPlayer * aPlayer);
        // ������� ����� ��������� ����������
        void PlanetOwnerChanged(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        // ������� ���������� ��������� �������
        void PlanetStateUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer = nullptr);
        // ������� ���������� �������� ����������
        void PlanetCoverageUpdate(TPlanet * aPlanet, globals::TPlayer * aPlayer, bool aIncrement);
        // ������� ���������� ��������� ����������
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
        // ������� ����������� ������� �������
        void PlanetDetailsShow(TPlanet * aPlanet, globals::TPlayer * aPlayer);
        // ������� ���������� ������� ��������
        /*void PlanetBuildingUpdate(TBuilding * aBuiling, Globals::TPlayer * aPlayer = nullptr);*/
        // ������� ���������� ������ ���������
        /*void PlanetStorageUpdate(TPlanet * aPlanet, TStorage * aStorage, Globals::TPlayer * aPlayer = nullptr);*/
        // ������� ������� ���������
        void PlanetStorageClear(TPlanet * aPlanet, int aIndex);
        // ������� ���������� ������ ������
        void PlayerHangarUpdate(int aSlot, int aCount, TShipType::E aShipType, globals::TPlayer * aPlayer);
        // ������� �������� ��������� ������
        /*void PlayerStorageChange(int aSize, aHoldings : TGlStorageList, aPlayer : TGlPlayer);*/
        // ������� ���������� ��������� ������
        /*void PlayerStorageUpdate(aIndex: Int, aHolding : TGlStorageHolder, aPlayer : TGlPlayer);*/
        // ������� �������� ���������� ���������
        void PlayerTechWarShipLoad(TShipTechProfile * aTechList, TShipTechValues * aPlayerList, globals::TPlayer * aPlayer);
        // ������� ���������� ���������� ���������
        void PlayerTechWarShipUpdate(TShipType::E aShipType, TShipTech::E aTechType, globals::TPlayer * aPlayer);
        // ������� �������� ���������� ������
        /*void PlayerTechBuildingLoad(TBuildingTechProfile * aTechList,  aUserList: TBuildingTechValues, aPlayer : TGlPlayer);*/
        // ������� ���������� ���������� ������
        /*void PlayerTechBuildingUpdate(aBuildingType: TBuildingType; TPlayer * aPlayer);*/
        // �������� ������ ��������
        /*void ConnectionBuildingsLoad(aBuildings: TBuildingConnectionList, aPlayer : TGlPlayer);*/

        // ��������� � ���������� �������� ���������
        void SystemLoadEnd(globals::TPlayer * aPlayer);

        // ���������� ������� �� ����������� � ���������
        void GalaxyLoadAccept(globals::TPlayer * aPlayer);
        void GalaxyLoadBegin(globals::TPlayer * aPlayer);


    public:
        // ���������� ������� �� ����������� � ���������
        void PlanetarStarted(globals::TPlayer * aPlayer);
        // ����������� � ���������� �������� �� ����������
        void PlanetarSubscribe(globals::TPlayer * aPlayer);
    };
}