#include "pch.h"
#include "Globals/Engine.h"
#include "Components/Database/Dataset.h"
#include "Modules/Planetar/Engine/PlanetarProfile.h"
#include "ModulePlanetar.h"

namespace planetar
{
    void TPlanetar::LoadAutoPlanetars()
    {
        // Выполним запрос
        database::TQuery tmpQuery("SHLoadBots");
        // Считаем планетарки
        while (tmpQuery.ReadRow())
        {
            int tmpPlayerID = tmpQuery.ReadInt("UID");
            // Если нашли - запустим планетарку
            auto tmpPlayer = TEngine::Server->FindPlayer(tmpPlayerID, true);
            if (tmpPlayer)
            {
                tmpPlayer->IsBot = true;
                tmpPlayer->Start();
            }
            else
                Log("Invalid bot");
        }
    }

    void TPlanetar::Start()
    {
        // Загрузим словарь планетарок
        /*TPlanetarDictionary.Start();*/
        // Запустим планетарки ботов
        LoadAutoPlanetars();
    }

    void TPlanetar::Stop()
    {
        /*TPlanetarDictionary.Stop();*/
    }

    void TPlanetar::Command(transport::TSocketConnection * aConnection)
    {
        // Найдем игрока
        m_Player = (globals::TPlayer*)aConnection->Owner;
        // Определим команду        
        int tmpCommand = aConnection->BufferRead.ReadCommand();
        // Проверим команду на исполнение
        switch (tmpCommand)
        {
        case CMD_AVAILABLE:
            CheckAvailable();
        case CMD_SUBSCRIBE:
            Subscribe();
        default:
            Retranslate();
        }
    }

    globals::TPlayer * TPlanetar::FindPlayer(int & aPlanetarID, int & aErrorCode)
    {
        // Считаем код планетарки
        aPlanetarID = m_Player->Connection->BufferRead.ReadInt();
        // Попробуем найти игрока для этой планетарки
        auto tmpPlayer = TEngine::Server->FindPlayer(aPlanetarID, false);
        if (!tmpPlayer)
        {
            aErrorCode = ERR_SYSTEM_UNLOADED;
            return nullptr;
        }
        // Определим доступность
        else if (!tmpPlayer->Planetar->Available())
        {
            aErrorCode = ERR_SYSTEM_UNAVAILABLE;
            return nullptr;
        }
        // Все хорошо
        else
        {
            aErrorCode = ERR_SUCCESS;
            return tmpPlayer;
        }
    }

    void TPlanetar::SendAvailable(int aPlanetarID, int aErrorCode)
    {
        m_Buffer.WriteCommand(CMD_AVAILABLE);
        m_Buffer.WriteInt(aPlanetarID);
        m_Buffer.WriteInt(aErrorCode);
        // Отправим ответ
        m_Player->Send(m_Buffer);
    }

    void TPlanetar::CheckAvailable()
    {
        int tmpErrorCode;
        int tmpPlanetarID;
        // Поищем профиль
        FindPlayer(tmpPlanetarID, tmpErrorCode);
        // Соберем ответ
        SendAvailable(tmpPlanetarID, tmpErrorCode);
    }

    void TPlanetar::Subscribe()
    {
        int tmpErrorCode;
        int tmpPlanetarID;
        // Поищем профиль
        globals::TPlayer * tmpPlayer = FindPlayer(tmpPlanetarID, tmpErrorCode);
        // Если профиля нет или подписка не удалась, вернем ответ
        if ((tmpErrorCode != ERR_SUCCESS) || (!tmpPlayer->Planetar->Subscribe(m_Player)))
            SendAvailable(tmpPlanetarID, tmpErrorCode);
    }

    void TPlanetar::Retranslate()
    {
        m_Player->Planetar->Command();
    }
}