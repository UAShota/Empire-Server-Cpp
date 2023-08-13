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
        // Выполним запрос
/*        if (!TEngine::DB.Call(*tmpDataset, "SHLoadHolding", "d", UID))
            return;
        // Загрузим все слоты хранилища
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
            // Данные загружены - сохраним
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
        // Нейтрал всегда 1
        if ((UID == 1) || (aVersus->UID == 1))
            tmpRole = TPlayerRole::Neutral;
        // Равен - значит свой
        else if (this == aVersus)
            tmpRole = TPlayerRole::Self;
        // Иначе враг
        else
            tmpRole = TPlayerRole::Enemy;
        // Прячем врагов под нейтралов если нет прав на идентификацию
        if ((aHideEnemy) && (tmpRole == TPlayerRole::Enemy))
            tmpRole = TPlayerRole::Neutral;
        // Вернем
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
        // Добавим его в очередь
        /*Connection->QueueWrite.Push(aBuffer);*/
        // И отправим в плавание
        TEngine::Server->Send(Connection);
    }

    void TPlayer::Send(transport::TSocketBuffer & aBuffer)
    {
        // Запишем размер буфера
        aBuffer.Commit();
        // Засунем в очередь и засигналим отправку
        /*Connection->QueueWrite.Push(new transport::TSocketBuffer(aBuffer));*/
        TEngine::Server->Send(Connection);
        // Сбросим буфер
        aBuffer.Reset(false);
    }
}