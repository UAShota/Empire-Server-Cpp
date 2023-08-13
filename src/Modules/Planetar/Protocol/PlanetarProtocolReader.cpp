#include "pch.h"
#include "PlanetarProtocolReader.h"
#include "Modules/Planetar/Engine/PlanetarEngine.h"

namespace planetar
{
    void TPlanetarProtocolReader::Command(transport::TSocketBuffer * aBuffer)
    {
        aBuffer->Reset(true);
        m_Queue.Push(aBuffer);
    }

    void TPlanetarProtocolReader::Work()
    {
        int tmpMaxCount = ciMaxCommandsPerTick;
        // Поищем буфер для работы
        while (tmpMaxCount-- > 0)
        {
            m_Buffer = m_Queue.Pop();
            if (m_Buffer == nullptr)
                break;
            /*else
                m_Player = (globals::TPlayer*)((transport::TSocketConnection*)m_Buffer->UserObject())->UserPointer;*/
            // Определим команду
            int tmpCommand = m_Buffer->ReadCommand();
            // Проверим команду на исполнение            
            switch (tmpCommand)
            {
            case CMD_SYSTEM_SUBSCRIBE:
                SystemSubscribe();
                break;
            case CMD_SHIP_MERGE:
                ShipMerge();
                break;
            case CMD_SHIP_SEPARATE:
                ShipSeparate();
                break;
            case CMD_SHIP_MOVETO:
                ShipMoveTo();
                break;
            case CMD_SHIP_MOVETO_GROUP:
                ShipMoveToGroup();
                break;
            case CMD_SHIP_ATTACHTO:
                ShipAttachTo();
                break;
            case CMD_PLANET_TRADE_PATH:
                PlanetTradePath();
                break;
            case CMD_SHIP_FROM_HANGAR:
                ShipFromHangar();
                break;
            case CMD_SHIP_MOVE_TO_HANGAR:
                ShipToHangar();
                break;
            case CMD_SHIP_CONSTRUCT:
                ShipConstruct();
                break;
            case CMD_SHIP_CHANGE_ACTIVE:
                ShipChangeActive();
                break;
            case CMD_SHIP_HYPODISPERSION:
                ShipChangeHypodispersion();
                break;
            case CMD_PLANET_SUBSCRIBE:
                PlanetSubscribe();
                break;
            case CMD_PLANET_SHOW_DETAILS:
                PlanetShowDetails();
                break;
            case CMD_RESOURCE_MOVE:
                ResourceMove();
                break;
            case CMD_TECH_WARSHIP_BUY:
                TechWarShipBuy();
                break;
            case CMD_TECH_BUILDING_BUY:
                TechBuildingBuy();
                break;
            case CMD_BUILDING_CONSTRUCT:
                BuildingConstruct();
                break;
            case CMD_SHIP_PORTAL_OPEN:
                ShipPortalOpen();
                break;
            case CMD_SHIP_PORTAL_CLOSE:
                ShipPortalClose();
                break;
            case CMD_SHIP_PORTAL_JUMP:
                ShipPortalJump();
                break;
            case CMD_SHIP_DESTROY:
                ShipDestroy();
                break;
            case CMD_SHIP_ANNIHILATION:
                ShipAnnihilation();
                break;
            case CMD_SHIP_SKILL_CONSTRUCTOR:
                ShipSkillConstructor();
                break;
            case CMD_SHIP_HANGAR_SWAP:
                ShipHangarSwap();
                break;
            default:
                Log("Invalid command");
            }
        }
    }

    void TPlanetarProtocolReader::SystemSubscribe()
    {
        m_Engine->Subscribe(m_Player);
    }

    TPlanet * TPlanetarProtocolReader::ReadPlanet()
    {
        return nullptr;
    }

    TShip * TPlanetarProtocolReader::ReadShip()
    {
        return nullptr;
    }

    void TPlanetarProtocolReader::ShipMerge()
    {
    }

    void TPlanetarProtocolReader::ShipSeparate()
    {
    }

    void TPlanetarProtocolReader::ShipMoveTo()
    {
    }

    void TPlanetarProtocolReader::ShipMoveToGroup()
    {
    }

    void TPlanetarProtocolReader::ShipAttachTo()
    {
    }

    void TPlanetarProtocolReader::ShipFromHangar()
    {
    }

    void TPlanetarProtocolReader::ShipToHangar()
    {
    }

    void TPlanetarProtocolReader::ShipConstruct()
    {
    }

    void TPlanetarProtocolReader::ShipChangeActive()
    {
    }

    void TPlanetarProtocolReader::ShipChangeHypodispersion()
    {
    }

    void TPlanetarProtocolReader::ShipPortalOpen()
    {
    }

    void TPlanetarProtocolReader::ShipPortalClose()
    {
    }
    void TPlanetarProtocolReader::ShipPortalJump()
    {
    }

    void TPlanetarProtocolReader::ShipDestroy()
    {
    }

    void TPlanetarProtocolReader::ShipSkillConstructor()
    {
    }

    void TPlanetarProtocolReader::ShipAnnihilation()
    {
    }

    void TPlanetarProtocolReader::ShipHangarSwap()
    {
    }

    void TPlanetarProtocolReader::PlanetTradePath()
    {
    }

    void TPlanetarProtocolReader::PlanetSubscribe()
    {
    }

    void TPlanetarProtocolReader::PlanetShowDetails()
    {
    }

    void TPlanetarProtocolReader::ResourceMove()
    {
    }

    void TPlanetarProtocolReader::BuildingConstruct()
    {
    }

    void TPlanetarProtocolReader::TechWarShipBuy()
    {
    }

    void TPlanetarProtocolReader::TechBuildingBuy()
    {
    }
}