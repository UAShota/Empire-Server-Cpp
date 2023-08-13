#include "pch.h"
#include "ModuleAuthorization.h"
#include "Components/Database/Dataset.h"

namespace server
{
    void TAuthorization::Start()
    {
        (std::thread&)m_Thread = std::thread(Execute, this);
    }

    void TAuthorization::Stop()
    {
        m_Thread.Terminate();
        m_Queue.Awake();
    }

    void TAuthorization::Command(transport::TSocketConnection * aConnection)
    {
        /*   m_Queue.Push(aConnection->Buffer);        */
    }

    void TAuthorization::Execute(TAuthorization * aInstance)
    {
        aInstance->WorkRead();
    }

    void TAuthorization::WorkRead()
    {
        // Ïîêà èäåò ïîòîê, îáðàáîòàåì î÷åðåäü
        while (!m_Thread.IsTerminated())
        {
            m_BufferRead = m_Queue.Pop();
            if (!m_BufferRead)
                continue;
            // Îïðåäåëèì êîìàíäó        
            int tmpCmd = m_BufferRead->ReadCommand();
            switch (tmpCmd)
            {
            case CMD_LOGIN_AUTH:
                CmdLogin();
                break;
            default:
                Log("Invalid command");
            }
            delete(m_BufferRead);
        }
    }

    globals::TPlayer * TAuthorization::LoadPlayer(int aUID)
    {
        // Çàãðóçèì ïðîôèëü èãðîêà
        database::TQuery tmpQuery("SHLoadProfile", "d", aUID);
        // Ïðîâåðèì ÷òî åñòü äàííûå äëÿ ÷òåíèÿ
        if (!tmpQuery.ReadRow())
        {
            Log("Invalid player UID");
            return NULL;
        }
        // Ñîõðàíèì ïàðàìåòðû èãðîêà
        globals::TPlayer * tmpPlayer = new globals::TPlayer();
        tmpPlayer->UID = aUID;
        tmpPlayer->Name = tmpQuery.ReadString("LOGIN");
        tmpPlayer->Gold = tmpQuery.ReadInt("MONEY_GOLD");
        tmpPlayer->Credits = tmpQuery.ReadInt("MONEY_CREDITS");
        tmpPlayer->Fuel = tmpQuery.ReadInt("MONEY_FUEL");
        tmpPlayer->Race = (globals::TRaceType::E)tmpQuery.ReadInt("ID_RACE");
        /*           if (!tmpData.ReadInt("STORAGE_SIZE", *tmpPlayer->Storage->Size))
                        break;*/
        tmpPlayer->Password = tmpQuery.ReadString("PWD_HASH");
        // Äîáàâèì åãî â ñëîâàðü
        m_Players.insert_or_assign(aUID, tmpPlayer);
        // Âåðíåì íàçàä
        return tmpPlayer;
    }

    globals::TPlayer * TAuthorization::FindPlayer(int aUID, bool aLoad)
    {
        // Ïðè ïîâòîðíîì çàïðîñå òîãî-æå ïåðñîíàæà, âåðíåì äàííûå ñ êåøà
        if (m_LastPlayerUID == aUID)
            return m_LastPlayer;
        // Èíà÷å ïîèùåì â ñïèñêå èëè çàãðóçèì ñ áàçû
        auto tmpIt = m_Players.find(aUID);
        globals::TPlayer * tmpPlayer = nullptr;
        // Ïðîâåðèì â ñïèñêå
        if (tmpIt != m_Players.end())
            tmpPlayer = tmpIt->second;
        else if (aLoad)
            tmpPlayer = LoadPlayer(aUID);
        // Åñëè íåòó - çàëîãèðóåì
        if (!tmpPlayer)
        {
            Log("Invalid player ID");
            return nullptr;
        }
        // Ñîõðàíèì â êýøå
        m_LastPlayer = tmpPlayer;
        m_LastPlayerUID = aUID;
        // Âåðíåì
        return m_LastPlayer;
    }

    bool TAuthorization::CmdLogin()
    {
        // Ïîëó÷èì ñâåäåíèÿ ïîñëå ñîåäèíåíèÿ êëèåíòà
        string tmpLogin = m_BufferRead->ReadString();
        string tmpPassword = m_BufferRead->ReadString();
        // Çàïðîñèì êîððåêòíîñòü àâòîðèçàöèè
        database::TQuery tmpQuery("SHLoadPlayer", "ss", tmpLogin, tmpPassword);
        if (tmpQuery.ReadRow())
        {
            int tmpPlayerID = tmpQuery.ReadInt("UID");
            auto tmpPlayer = FindPlayer(tmpPlayerID, true);
            // Åñëè íàøëè - îäîáðèì àâòîðèçàöèþ
            if (tmpPlayer)
            {
                ResponseLoginAccept(tmpPlayer);
                return true;
            }
        }
        ResponseLoginFailed();
        return false;
    }

    void TAuthorization::ResponseLoginAccept(globals::TPlayer * aPlayer)
    {
        // Îòêëþ÷èì ïðåäûäóùåãî èãðîêà
        /*if (aPlayer.Connection.Connected())
        {
            aPlayer.Send(new transport::TSocketBuffer(CMD_LOGIN_RELOG));
            /*aPlayer->Disconnect();
        }
/*        aPlayer.Connection = *m_BufferRead->SocketConnection();
        aPlayer.Connection->UserPointer = aPlayer;*/
        // Îòïðàâèì ñîîáùåíèå îá óñïåøíîé àâòîðèçàöèè äëÿ êýøà ïàðîëÿ
        m_BufferWrite.WriteCommand(CMD_LOGIN_ACCEPT);
        m_BufferWrite.WriteString(aPlayer->Password);
        m_BufferWrite.WriteInt(aPlayer->UID);
        m_BufferWrite.WriteInt(aPlayer->Race);
        aPlayer->Send(m_BufferWrite);
        aPlayer->Start();
        // Çàëîãèðóåì
        Log("accepted from", aPlayer->Connection->IP());
    }

    void TAuthorization::ResponseLoginFailed()
    {
        // Îòïðàâèì ñîîáùåíèå îá îøèáêå àâòîðèçàöèè
    /*    Transport::TSocketBuffer * tmpBuffer = new Transport::TSocketBuffer(m_BufferRead->UserPointer(), CMD_LOGIN_FAILED);
        tmpBuffer->WriteInt(I_ERROR_INVALID_CREDENTIALS);
        TEngine::Server.Send(tmpBuffer);*/
        // Çàëîãèðóåì
        Log("Login failed");
    }

    /*void TAuthorization::ChatMessage(const char * aText, Globals::TPlayer * aPlayer)
    {

        // Îòïðàâèì ñîîáùåíèå âñåì ó÷àñòíèêàì
        for (Globals::TPlayerMapIt tmpPlayer = m_Players->begin(); tmpPlayer != m_Players->end(); ++TmpPlayer)
        {
            Globals::TPlayerConnection * tmpConnection = tmpPlayer->second->Connection;
            // Ïðîïóñêàåì íåàêòèâíûå ïðîôèëè
            if (!tmpConnection)
                continue;
            // Ïåðåñûëàåì ñîîáùåíèå
            Transport::TSocketBuffer * tmpBuffer = tmpConnection->Writer->Buffer->Command(CMD_CHAT_MESSAGE);
            /*tmpBuffer->WriteString(aText);
            tmpBuffer->Commit();
            tmpConnection->Writer->Commit();
        }
    }*/
}