#include "pch.h"
#include "Globals/Engine.h"
#include "Components/Database/Dataset.h"
#include "Modules/Planetar/Engine/PlanetarProfile.h"
#include "ModulePlanetar.h"

namespace planetar
{
    void TPlanetar::LoadAutoPlanetars()
    {
        // �������� ������
        database::TQuery tmpQuery("SHLoadBots");
        // ������� ����������
        while (tmpQuery.ReadRow())
        {
            int tmpPlayerID = tmpQuery.ReadInt("UID");
            // ���� ����� - �������� ����������
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
        // �������� ������� ����������
        /*TPlanetarDictionary.Start();*/
        // �������� ���������� �����
        LoadAutoPlanetars();
    }

    void TPlanetar::Stop()
    {
        /*TPlanetarDictionary.Stop();*/
    }

    void TPlanetar::Command(transport::TSocketConnection * aConnection)
    {
        // ������ ������
        m_Player = (globals::TPlayer*)aConnection->Owner;
        // ��������� �������        
        int tmpCommand = aConnection->BufferRead.ReadCommand();
        // �������� ������� �� ����������
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
        // ������� ��� ����������
        aPlanetarID = m_Player->Connection->BufferRead.ReadInt();
        // ��������� ����� ������ ��� ���� ����������
        auto tmpPlayer = TEngine::Server->FindPlayer(aPlanetarID, false);
        if (!tmpPlayer)
        {
            aErrorCode = ERR_SYSTEM_UNLOADED;
            return nullptr;
        }
        // ��������� �����������
        else if (!tmpPlayer->Planetar->Available())
        {
            aErrorCode = ERR_SYSTEM_UNAVAILABLE;
            return nullptr;
        }
        // ��� ������
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
        // �������� �����
        m_Player->Send(m_Buffer);
    }

    void TPlanetar::CheckAvailable()
    {
        int tmpErrorCode;
        int tmpPlanetarID;
        // ������ �������
        FindPlayer(tmpPlanetarID, tmpErrorCode);
        // ������� �����
        SendAvailable(tmpPlanetarID, tmpErrorCode);
    }

    void TPlanetar::Subscribe()
    {
        int tmpErrorCode;
        int tmpPlanetarID;
        // ������ �������
        globals::TPlayer * tmpPlayer = FindPlayer(tmpPlanetarID, tmpErrorCode);
        // ���� ������� ��� ��� �������� �� �������, ������ �����
        if ((tmpErrorCode != ERR_SUCCESS) || (!tmpPlayer->Planetar->Subscribe(m_Player)))
            SendAvailable(tmpPlanetarID, tmpErrorCode);
    }

    void TPlanetar::Retranslate()
    {
        m_Player->Planetar->Command();
    }
}