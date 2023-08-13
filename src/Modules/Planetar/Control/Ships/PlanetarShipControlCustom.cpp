#include "pch.h"
#include "PlanetarShipControlCustom.h"

namespace planetar
{
    TShipControlCustom::TShipControlCustom(TPlanetarEngine * aThread) noexcept
    {
        m_Engine = aThread;
    }

    TShip * TShipControlCustom::CreateShip(TPlanet * aPlanet, TShipType::E aType, int aSlot, int aCount, globals::TPlayer * aPlayer)
    {
        TShip * tmpShip = new TShip(aPlayer);
        /*tmpShip->ID  = m_Thread.ControlShips.ListShips.Count;*/
        tmpShip->Type = aType;
        /*        tmpShip->ChangeTech(aPlayer->Planetar->TechShipProfile[AType], aPlayer->Planetar->TechShipValues[AType]);*/
        tmpShip->Planet = aPlanet;
        tmpShip->Planet = aPlanet;
        tmpShip->Count = aCount;
        tmpShip->HP = tmpShip->TechValue(TShipTech::Hp);
        tmpShip->Fuel = I_MAX_FUEL_COUNT;
        /*tmpShip->Landing = aSlot;*/
        // ������� � ������ ����������
        /*FThread.ControlShips.ListShips.Add(tmpShip);*/
        return tmpShip;
    }

    TShip * TShipControlCustom::CheckShipBlocker(TShip * aShip, int aSlot, bool aEnemy, TShipMode::E aWantMode)
    {
        // ������� ������ ���� �������� �������, ��������� ��� ������
        if (!aShip->TechActive(TShipTech::CornerBlock))
            return nullptr;
        // �������� ��������� ������ �� ���������
        TShip * tmpShip = CheckShipSide(aShip->Planet, aSlot, aWantMode);
        if (!tmpShip)
            return nullptr;
        // ��������� ���������������
        bool tmpFriend = aShip->Owner->IsRoleFriend(tmpShip->Owner);
        // ������� ������ ���� �� ������ ������, � ���� - �������
        return (aEnemy == tmpFriend) ? nullptr : tmpShip;
    }

    TShip * TShipControlCustom::CheckShipSide(TPlanet * aDestination, int aSlot, TShipMode::E aWantMode)
    {
        // ������� ������� �������, ��� ����� ���� ��������� �� ����� ��� ����� �� � ������������ ������
        TShip * tmpShip = nullptr;
        if ((!aDestination->Landings->HaveShip(aSlot, tmpShip))
            || (tmpShip->State != TShipState::Iddle)
            || (tmpShip->Mode != aWantMode))
            return nullptr;
        else
            return tmpShip;

    }

    bool TShipControlCustom::CheckArrival(TPlanet * aDestination, bool aShipLowOrbit, int aSlotFrom, int aSlotTo, 
        TPlanet * aShipPlanet, globals::TPlayer * aShipOwner, bool aCheckOnePlanet)
    {
        // ���� ������ ������ - ��������� ��������� �� 6 ������ ����
        /*if ((!aSlotTo.IsLowOrbit)
            && ((aShipPlanet != aDestination) || !aSlotFrom.IsLowOrbit || !aCheckOnePlanet)
            && (aDestination.ShipCount.TryGetValue(aShipOwner, tmpCount))
            && (tmpCount.Exist == I_MAX_SHIP_COUNT))
        {
            TEngine::Log->Write("Ful");
            return false;
        }
        else*/
        return true;

    }

    bool TShipControlCustom::CheckMoveTo(TShip * aShip, TPlanet * aDestination, int aSlotTo, bool aCheckOnePlanet)
    {
        bool tmpArrival = CheckArrival(aDestination, aShip->TechActive(TShipTech::LowOrbit),
            aShip->Landing, aSlotTo, aShip->Planet, aShip->Owner, aCheckOnePlanet);
        bool tmpBackZone = CheckBackZone(aShip->TechActive(TShipTech::IntoBackzone),
            aDestination, aSlotTo, aShip->Owner);
        return tmpArrival && tmpBackZone;
    }

    bool TShipControlCustom::CheckBackZone(bool aIgnoreBackZone, TPlanet * aDestination, int aSlot, globals::TPlayer * aOwner)
    {
        // � ����� ����� � ��� ����� �����
        if (aIgnoreBackZone)
            return true;
        // ����� ���� ����, ������� �������� �� ���� ����
        TShip * tmpLeft = CheckShipSide(aDestination, aSlot - 1, TShipMode::Active);
        if ((!tmpLeft) || (tmpLeft->Owner->IsRoleFriend(aOwner)))
            return true;
        // ������ ���� ����, ������� �������� �� ���� ����
        TShip * tmpRight = CheckShipSide(aDestination, aSlot + 1, TShipMode::Active);
        if ((!tmpRight) || (tmpRight->Owner->IsRoleFriend(aOwner)))
            return true;
        // ���� ������� ��������� �� ������� ���� �����, �� ���� ���
        return !tmpRight->Owner->IsRoleFriend(tmpLeft->Owner);
    }

    int TShipControlCustom::GetFreeSlot(bool aIgnore, TPlanet * aDestination, bool aShipLowOrbit, globals::TPlayer * aOwner)
    {
        /* var
              tmpSlot : TPlLanding;
          begin
              Result : = 0;
          try
              tmpSlot : = 1;
          repeat
              // ������� ����� ���������� ����
              if (aShipLowOrbit) then
                  tmpSlot.Dec()
              else
                  tmpSlot.Inc();
          // �������� ����� ���� ��� ������ � �� �����
          if (aDestination->Landings->IsEmpty(tmpSlot))
              && (CheckBackZone(aIgnore, aDestination, tmpSlot, aOwner))
              then
              Exit(tmpSlot);
          until(tmpSlot = 1);*/
        return 0;
    }

    int TShipControlCustom::DealDamage(TShip * aShip, int aDamage, bool aDestruct)
    {
        // ������� ������������ �������
        if (!aShip)
            return 0;
        // ���������� ����� ������ ������� � �������� �������
        if (aShip->Count == 0)
            return 0;
        // ��������� ���������� ������ � ����� ����
        int tmpHP = aShip->TechValue(TShipTech::Hp);
        int tmpKilled = std::min(aShip->Count, (int)std::trunc(aDamage / tmpHP));
        int tmpDamage = tmpKilled * tmpHP;
        // ����� �������� ����, ������ ����������, ������ ������
        int tmpResult = tmpDamage;
        aDamage -= tmpDamage;
        aShip->Count -= tmpKilled;
        if (aDestruct)
            aShip->Destructed += tmpKilled;
        // �������� ������� ����������
        if (aShip->Count > 0)
        {
            tmpDamage = std::min(aShip->HP, aDamage);
            aShip->HP -= tmpDamage;
            tmpResult += aDamage;
            // ������ ������� ��� �� � ����
            if (aShip->HP == 0)
            {
                aShip->HP = tmpHP - (aDamage - tmpDamage);
                aShip->Count--;
                // ������ ������ ���� �����
                if (aDestruct)
                    aShip->Destructed++;
            }
        }
        // ���� ���� ���� - ������� ������ �������
        /*if (tmpKilled > 0)
           m_Thread.ControlPlanets.UpdateShipList(aShip, -TmpKilled);*/
           // ������� ��������� �������, ���� �� ������ - ��������
        if (aDestruct)
            aShip->IsDestroyed = TShipDestroyed::Destruct;
        else
            aShip->IsDestroyed = TShipDestroyed::Silent;
        return tmpDamage;
    }

    void TShipControlCustom::WorkShipHP(TPlanet * aPlanet)
    {
        /*  var
               tmpI : Int;
       tmpShip: TPlShip;
           begin
               try
               for tmpI : = Pred(aPlanet.Ships.Count) downto 0 do
                   begin
                   tmpShip : = aPlanet.Ships[tmpI];
           if (tmpShip.IsDestroyed = pshchNone) then
               Continue;
           // ���� �� ���� - ������� ������
           if (tmpShip.Count > 0) then
               begin
               tmpShip.IsDestroyed : = pshchNone;
           TPlanetarThread(Engine).ControlShips.Repair.Check(tmpShip);
           TPlanetarThread(Engine).SocketWriter.ShipUpdateHP(tmpShip);
           end else
               // ������ � �������
               begin
               TPlanetarThread(Engine).ControlShips.RemoveFromPlanet.Execute(
                   tmpShip, True, tmpShip.IsDestroyed = pshchDestruct, True);
           end;
           end;*/
    }
}