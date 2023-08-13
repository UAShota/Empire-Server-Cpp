#include "pch.h"
#include "Player.h"
#include "Modules/Planetar/Engine/PlanetarProfile.h"
#include "Globals/Engine.h"

namespace globals
{
    TPlayer::TPlayer() noexcept
    {
        Planetar = new planetar::TProfile(this);
    }

    TPlayer::~TPlayer()
    {
        delete(Planetar);
    }

    void TPlayer::LoadHoldings()
    {
        // �������� ������
/*        if (!TEngine::DB.Call(*tmpDataset, "SHLoadHolding", "d", UID))
            return;
        // �������� ��� ����� ���������
        while (tmpDataset.ReadRow())
        {
            /*if (!tmpData->ReadInt("POSITION", *tmpPos))
                continue;
            if (!tmpData->ReadInt("ID_TYPE", (int*)tmpHolder.Resource))
                continue;
            if (!tmpData->ReadInt("ID_ITEM", (int*)*tmpHolder.Type))
                continue;
            if (!tmpData->ReadInt("COUNT", (int*)*tmpHolder.Count))
                continue;
            // ������ ��������� - ��������
            Storage->Holders[tmpPos] = tmpHolder;
        }*/
    }

    void TPlayer::Start()
    {
        /*LoadHoldings();*/
        if (!m_Active)
        {
            Planetar->Start();
            m_Active = true;
        }
        else
            Planetar->Subscribe(this);
    }

    void TPlayer::Stop()
    {
        /*unsubscribe*/
        if (m_Active)
        {
            Planetar->Stop();
            m_Active = false;
        }
    }

    TPlayerRole::E TPlayer::Role(TPlayer * aVersus, bool aHideEnemy)
    {
        TPlayerRole::E tmpRole;
        // ������� ������ 1
        if ((UID == 1) || (aVersus->UID == 1))
            tmpRole = TPlayerRole::Neutral;
        // ����� - ������ ����
        else if (this == aVersus)
            tmpRole = TPlayerRole::Self;
        // ����� ����
        else
            tmpRole = TPlayerRole::Enemy;
        // ������ ������ ��� ��������� ���� ��� ���� �� �������������
        if ((aHideEnemy) && (tmpRole == TPlayerRole::Enemy))
            tmpRole = TPlayerRole::Neutral;
        // ������
        return tmpRole;
    }

    bool TPlayer::IsRoleFriend(TPlayer * aVersus)
    {
        TPlayerRole::E tmpRole = Role(aVersus);
        return (tmpRole == TPlayerRole::Self) || (tmpRole == TPlayerRole::Friends);
    }

    void TPlayer::Send(transport::TSocketBuffer * aBuffer, bool aAutoCommit)
    {
        if (aAutoCommit)
            aBuffer->Commit();
        // ������� ��� � �������
        /*Connection->QueueWrite.Push(aBuffer);*/
        // � �������� � ��������
        TEngine::Server->Send(Connection);
    }

    void TPlayer::Send(transport::TSocketBuffer & aBuffer)
    {
        // ������� ������ ������
        aBuffer.Commit();
        // ������� � ������� � ���������� ��������
        /*Connection->QueueWrite.Push(new transport::TSocketBuffer(aBuffer));*/
        TEngine::Server->Send(Connection);
        // ������� �����
        aBuffer.Reset(false);
    }
}