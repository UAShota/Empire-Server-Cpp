#include "pch.h"
#include "PlanetarEngine.h"

namespace planetar
{
    TPlanetarEngine::TPlanetarEngine(globals::TPlayer * aPlayer)
    {
        m_Player = aPlayer;
        (std::thread&)m_Thread = std::thread(Execute, this);

        m_SocketWriter.m_Engine = this;
        m_SocketReader.m_Engine = this;
    }

    TPlanetarEngine::~TPlanetarEngine()
    {
        m_Thread.Terminate();
    }

    bool TPlanetarEngine::Available()
    {
        return m_Available;
    }

    bool TPlanetarEngine::Command(globals::TPlayer * aPlayer)
    {
        if (m_Available)
        {
            /*m_SocketReader.Command(aPlayer->Connection->Buffer);*/
            return true;
        }
        else
            return false;
    }

    void TPlanetarEngine::Subscribe(globals::TPlayer * aPlayer)
    {
        m_SocketWriter.PlanetarSubscribe(aPlayer);
    }

    void TPlanetarEngine::Unsubscribe(globals::TPlayer * aPlayer)
    {
    }

    int TPlanetarEngine::SizeX()
    {
        return m_SizeX;
    }

    int TPlanetarEngine::SizeY()
    {
        return m_SizeY;
    }

    TPlanet::Map TPlanetarEngine::Planets()
    {
        return m_Planets;
    }

    void TPlanetarEngine::Execute(TPlanetarEngine * aInstance)
    {
        aInstance->Work();
    }

    void TPlanetarEngine::LoadParams()
    {
    }

    void TPlanetarEngine::Work()
    {
        // Загрузка параметров созвездия
        LoadParams();
        // Контроллеры
        /*
        ControlPlanets.Start();
        ControlShips.Start();
        */
        // Загрузка завершена
        m_Available = true;

        // Время загрузки
        Log("Planetar loaded");
        /*TLogAccess.Write(ClassName,  format(' #%d ticks %d', [Player.UID, GetTickCount64() - tmpTime]));*/

        // Отправим игроку приглашение присоединиться
        if (!m_Player->IsBot)
            m_SocketWriter.PlanetarStarted(m_Player);

        // Запускаем поток обработки
        while (!m_Thread.IsTerminated())
        {
            m_SocketReader.Work();
            Sleep(50);
        }
    }
}