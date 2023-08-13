#include "pch.h"
#include "PlanetarProfile.h"

namespace planetar
{
    TProfile::TProfile(globals::TPlayer * aPlayer)
    {
       m_Player = aPlayer;
    }

    void TProfile::Start()
    {
       m_Engine = new TPlanetarEngine(m_Player);
    }

    void TProfile::Stop()
    {
        delete(m_Engine);
    }

    bool TProfile::Available()
    {
        return m_Engine && m_Engine->Available();
    }

    bool TProfile::Subscribe(globals::TPlayer * aPlayer)
    {
        return m_Engine && m_Engine->Command(aPlayer);
    }

    void TProfile::Unsubscribe()
    {
       m_Subscribe->Unsubscribe(m_Player);
       m_Subscribe = nullptr;
    }

    bool TProfile::Command()
    {
        return m_Subscribe && m_Subscribe->Command(m_Player);
    }

    void TProfile::LoadTechWarShips()
    {
    }

    void TProfile::LoadTechBuildings()
    {
    }

    void TProfile::LoadHangar()
    {
    }

    void TProfile::BuyTech(TShipType::E aShipType, TShipTech::E aTech, globals::TPlayer * aPlayer)
    {
    }

    TShipTechItem * TProfile::Tech(TShipType::E aShipType, TShipTech::E aTech)
    {
        return nullptr;/* (TechShipProfile[AShipType])[ATech];*/
    }
}