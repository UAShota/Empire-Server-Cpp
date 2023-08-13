#include "pch.h"
#include "PlanetarShipControlConstruct.h"
#include "Modules/Planetar/Engine/PlanetarProfile.h"

namespace planetar
{
    int TShipControlConstruct::GetHPperTick(TShip * aShip)
    {

        // ������ ���������� ������ ����������� ������, 1 ����� ���� ������ �� ���������
        if (true/*!aShip->Planet->Constructors->TryGetValue(aShip->Owner, tmpCount)*/)
        {
            if (aShip->TechActive(TShipTech::Stationary))
                /*tmpCount->Value = 1*/;
            else
                return -1;
        }
        // ������� 150�� // ���
        return std::min(0/*tmpCount->Value*/, I_MAX_SHIPYARD_ACTIVE) * aShip->TechValue(TShipTech::Construction);
    }

    bool TShipControlConstruct::OnTimer(TShip * aShip, int & aCounter, int & aValue)
    {
        // ��������� ��������� ���������
        if (aCounter == 0)
        {
            if (!aShip->CanOperable(true))
                return false;
            aShip->HP = aShip->TechValue(TShipTech::Hp);
            // �������� ���������
            /*FThread->SocketWriter->ShipUpdateHP(aShip);
            // �������� ��������� ��������� ���� �������� �� � ��������� ������
           m_Thread->ControlShips->StandUp->Execute(aShip);
            // ������� ��������� ������� ��� ������������ ��������
           m_Thread->ControlPlanets->UpdateShipList(aShip, aShip->Count);*/
           // �������� ����� �������
            return true;
        }
        // ��������� ��
        int tmpCount = GetHPperTick(aShip);
        int tmpTotal = (aShip->Count * aShip->TechValue(TShipTech::Hp));
        // ������ ������� �� � �������
        if (aShip->CanOperable(true))
            aShip->HP += tmpCount;
        else
            tmpCount = -tmpCount;
        // ���� ��������� ��� ����� - ��������
        if (aShip->HP >= tmpTotal)
            aCounter = 0;
        // ���� ��� - ��������, ���������� �� ��������
        else if (tmpCount != aCounter)
        {
            aCounter = tmpCount;
            aValue = (tmpTotal - aShip->HP) / aCounter;
            return true;
        }
        return false;
    }

    TShip * TShipControlConstruct::Execute(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer)
    {
        bool tmpLowOrbit = aPlayer->Planetar->Tech(aShipType, TShipTech::LowOrbit)->Supported;
        bool tmpBackzone = aPlayer->Planetar->Tech(aShipType, TShipTech::IntoBackzone)->Supported;
        // ������ ��������� ����
        int tmpSlot = GetFreeSlot(tmpBackzone, aPlanet, tmpLowOrbit, aPlayer);
        if (tmpSlot == 0)
        {
            Log("Slot");
            return nullptr;
        }
        // ������� �������� ��������� �������� � ��������� ����
        if (!CheckArrival(aPlanet, tmpLowOrbit, tmpSlot, tmpSlot, aPlanet, aPlanet->Owner, false))
        {
            Log("Arriva");
            return nullptr;
        }
        // ���� �� ����������
        int tmpCount = std::min(aCount, aPlayer->Planetar->Tech(aShipType, TShipTech::Count)->Value);
        int tmpCost = tmpCount * aPlayer->Planetar->Tech(aShipType, TShipTech::Cost)->Value;
        // ��������� ������� �������� ��� ���������
        /*if (aPlanet->ResAvailIn[resModules] < tmpCost) then
            begin
            TLogAccess->Write(ClassName, 'Modules');
        Exit();
        end;*/
        // ���� ��� ���� - �������� ��������
        TShip * tmpShip = CreateShip(aPlanet, aShipType, tmpSlot, tmpCount, aPlayer);
        tmpShip->Mode = TShipMode::Construction;
        tmpShip->HP = 0;
        // �������� ���������� ����������� ��������
        /*FThread->ControlStorages->DecrementResource(resModules, aPlanet, tmpCost);
        // ������� ��������� �������� �� �������
       m_Thread->ControlShips->AddToPlanet->Execute(tmpShip, aPlanet,false,false, aPlanet->Timer[ppltmBattle]);
        // �������� ���������
       m_Thread->SocketWriter->ShipCreate(tmpShip);
        // ������� ������
       m_Thread->WorkerShips->TimerAdd(Result, TShipTimer::OpConstruction, GetHPperTick(Result),
            OnTimer, tmpShip->Count * Result->TechValue(TShipTech::Hp) // GetHPperTick(Result));
            */
        return tmpShip;
    }

    void TShipControlConstruct::Player(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer)
    {
        // ������ ������� ���������� ���������� ������
        if (aCount <= 0)
        {
            Log("Count");
            return;
        }
        // ������ ������� ���� ������� � ���
        if (aPlanet->Timer[TPlanetTimer::Battle])
        {
            Log("Battle");
            return;
        }
        // ������ ������� ���� ���������� �������
        if (aPlayer->Planetar->Tech(aShipType, TShipTech::Active)->Value == 0)
        {
            Log("Tech");
            return;
        }
        // ��������� ��������� �������� �����
        bool tmpStationary = aPlayer->Planetar->Tech(aShipType, TShipTech::Stationary)->Supported;
        // �������� ��������� �������������� �����
        if (!aPlanet->IsManned())
        {
            // ������ ������� �� ����� �������
            if (!aPlanet->Owner->IsRoleFriend(aPlayer))
            {
                Log("Role");
                return;
            }
            // �� ������� ����� ������� ������ �����������
            if (!tmpStationary)
            {
                Log("Manned");
                return;
            }
        }
        // �� ����� �� ������������ ���� ����� ������� ������ ���� ���� �����
        if ((!tmpStationary)
            && (!true/*aPlanet->Constructors->ContainsKey(aPlayer)*/))
        {
            Log("Shipyard");
            return;
        }
        // ����� �������� ��������
        Execute(aPlanet, aShipType, aCount, aPlayer);
    }
}