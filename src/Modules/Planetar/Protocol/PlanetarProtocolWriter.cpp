#include "pch.h"
#include "PlanetarProtocolWriter.h"
#include "Modules/Planetar/Engine/PlanetarEngine.h"
#include "Modules/Planetar/Classes/PlanetarShip.h"

namespace planetar
{
    void TPlanetarProtocolWriter::PlanetarSubscribe(globals::TPlayer * aPlayer)
    {
        // Возможность отправки
        if (!m_Engine->Available())
            return;
        // Запишем новый буффер
        m_Buffer.WriteCommand(CMD_SYSTEM_LOAD_BEGIN);
        // Запись размеров созвездия, в секторах
        m_Buffer.WriteInt(m_Engine->SizeX());
        m_Buffer.WriteInt(m_Engine->SizeY());
        // Запись количества передаваемых планет
        m_Buffer.WriteInt(m_Engine->Planets().size());
        // Передача данных планеты
        for (auto tmpPlanetPair : m_Engine->Planets())
        {
            TPlanet * tmpPlanet = tmpPlanetPair.second;
            int tmpCountFriend;
            int tmpCountEnemy;
            // Видимость ядра планеты - видно только соседние планеты
            bool tmpHardLight = tmpPlanet->VisibleByPlayer(aPlayer, true, true);
            bool tmpSoftLight = tmpHardLight || tmpPlanet->VisibleByPlayer(aPlayer, false, true);
            int tmpCountSelf = tmpPlanet->CoverageByPlayer(aPlayer, true, &tmpCountFriend, &tmpCountEnemy);
            TPlanetState::E tmpState = tmpPlanet->StateByVisible(tmpSoftLight);
            // И запишем в стрим
            m_Buffer.WriteInt(tmpPlanet->ID);
            m_Buffer.WriteInt(tmpPlanet->CoordX);
            m_Buffer.WriteInt(tmpPlanet->CoordY);
            m_Buffer.WriteInt(tmpPlanet->Type);
            m_Buffer.WriteInt(tmpPlanet->Owner->UID);
            m_Buffer.WriteInt(tmpState);
            m_Buffer.WriteBool(tmpHardLight);
            m_Buffer.WriteBool(tmpSoftLight);
            m_Buffer.WriteInt(tmpCountSelf);
            m_Buffer.WriteInt(tmpCountFriend);
            m_Buffer.WriteInt(tmpCountEnemy);
            m_Buffer.WriteBool(tmpPlanet->IsBigHole);
        }
        // Передача данных ссылок каждой планеты
        /*for (TPlanetListIt tmpPlanetIt = m_Engine->Planets().begin(); tmpPlanetIt != m_Engine->Planets().end(); ++tmpPlanetIt)
        {
            TPlanet * tmpPlanet = *tmpPlanetIt;
            m_Buffer.WriteInt(tmpPlanet->Links->size());
            for (TPlanetListIt tmpPlanetLinkIt = tmpPlanet->Links->begin(); tmpPlanetIt != tmpPlanet->Links->end(); ++tmpPlanetLinkIt)
                m_Buffer.WriteInt((*tmpPlanetLinkIt)->ID);
        }*/
        m_Buffer.Commit();
        // Команда завершения загрузки
        m_Buffer.WriteCommand(CMD_SYSTEM_LOAD_COMPLETE);
        // Отправим данные игроку
        aPlayer->Send(m_Buffer);
    }

    void TPlanetarProtocolWriter::PlanetarStarted(globals::TPlayer * aPlayer)
    {
        m_Buffer.WriteCommand(CmdPlanetarStarted);
        m_Buffer.WriteInt(aPlayer->UID);
        aPlayer->Send(m_Buffer);
    }
}