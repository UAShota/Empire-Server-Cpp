#pragma once

#include "Modules/Planetar/Classes/PlanetarShip.h"
#include "Modules/Planetar/Classes/PlanetarPlanet.h"

namespace planetar
{
    class TPlanetarProtocolReader
    {
    private:
        enum Commands
        {
            // Подписка на созвездие
            CMD_SYSTEM_SUBSCRIBE = 0x1F02,
            CMD_SHIP_MERGE = 0x1000,
            CMD_SHIP_MOVETO = 0x1001,
            CMD_SHIP_ATTACHTO = 0x1002,
            CMD_PLANET_TRADE_PATH = 0x1003,
            CMD_SHIP_FROM_HANGAR = 0x1004,
            CMD_PLANET_SUBSCRIBE = 0x1005,
            CMD_SHIP_MOVE_TO_HANGAR = 0x1006,
            CMD_PLANET_SHOW_DETAILS = 0x1007,
            CMD_RESOURCE_MOVE = 0x1008,
            CMD_SHIP_CONSTRUCT = 0x1009,
            CMD_TECH_WARSHIP_BUY = 0x100A,
            CMD_BUILDING_CONSTRUCT = 0x100B,
            CMD_TECH_BUILDING_BUY = 0x100C,
            CMD_SHIP_CHANGE_ACTIVE = 0x100D,
            CMD_SHIP_HYPODISPERSION = 0x100E,
            CMD_SHIP_MOVETO_GROUP = 0x100F,
            CMD_SHIP_SEPARATE = 0x1010,
            CMD_SHIP_PORTAL_OPEN = 0x1012,
            CMD_SHIP_DESTROY = 0x1013,
            CMD_SHIP_PORTAL_CLOSE = 0x1014,
            CMD_SHIP_PORTAL_JUMP = 0x1015,
            CMD_SHIP_ANNIHILATION = 0x1016,
            CMD_SHIP_SKILL_CONSTRUCTOR = 0x1017,
            CMD_SHIP_HANGAR_SWAP = 0x1018
        };
    private:
        const int ciMaxCommandsPerTick = 50;
        // Текущий игрок чтения
        globals::TPlayer * m_Player;
        // Текущий буффер чтения
        transport::TSocketBuffer * m_Buffer;
    public:
        class TPlanetarEngine * m_Engine;
        TAsyncQueue<transport::TSocketBuffer*> m_Queue;
    private:
        void SystemSubscribe();
        TPlanet * ReadPlanet();
        TShip * ReadShip();
        void ShipMerge();
        void ShipSeparate();
        void ShipMoveTo();
        void ShipMoveToGroup();
        void ShipAttachTo();
        void ShipFromHangar();
        void ShipToHangar();
        void ShipConstruct();
        void ShipChangeActive();
        void ShipChangeHypodispersion();
        void ShipPortalOpen();
        void ShipPortalClose();
        void ShipPortalJump();
        void ShipDestroy();
        void ShipSkillConstructor();
        void ShipAnnihilation();
        void ShipHangarSwap();
        void PlanetTradePath();
        void PlanetSubscribe();
        void PlanetShowDetails();
        void ResourceMove();
        void BuildingConstruct();
        void TechWarShipBuy();
        void TechBuildingBuy();
    public:
        void Work();
        void Command(transport::TSocketBuffer * aBuffer);
    };
}