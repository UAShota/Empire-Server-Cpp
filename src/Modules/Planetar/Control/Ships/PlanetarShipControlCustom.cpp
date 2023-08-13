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
        // Добавим в список корабликов
        /*FThread.ControlShips.ListShips.Add(tmpShip);*/
        return tmpShip;
    }

    TShip * TShipControlCustom::CheckShipBlocker(TShip * aShip, int aSlot, bool aEnemy, TShipMode::E aWantMode)
    {
        // Корабль должен быть активной военкой, крейсером или дредом
        if (!aShip->TechActive(TShipTech::CornerBlock))
            return nullptr;
        // Проверим указанную сторну от кораблика
        TShip * tmpShip = CheckShipSide(aShip->Planet, aSlot, aWantMode);
        if (!tmpShip)
            return nullptr;
        // Определим дружественность
        bool tmpFriend = aShip->Owner->IsRoleFriend(tmpShip->Owner);
        // Корабль должен быть по центру врагом, с края - союзным
        return (aEnemy == tmpFriend) ? nullptr : tmpShip;
    }

    TShip * TShipControlCustom::CheckShipSide(TPlanet * aDestination, int aSlot, TShipMode::E aWantMode)
    {
        // Признак наличия корабля, нет блока если противник не стоит или стоит не в определенном режиме
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
        // Если орбита боевая - проверяем параметры на 6 стеков если
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
        // С техой влета в тыл везде можно
        if (aIgnoreBackZone)
            return true;
        // Левый слот тыла, быстрая проверка на свой юнит
        TShip * tmpLeft = CheckShipSide(aDestination, aSlot - 1, TShipMode::Active);
        if ((!tmpLeft) || (tmpLeft->Owner->IsRoleFriend(aOwner)))
            return true;
        // Правый слот тыла, быстрая проверка на свой юнит
        TShip * tmpRight = CheckShipSide(aDestination, aSlot + 1, TShipMode::Active);
        if ((!tmpRight) || (tmpRight->Owner->IsRoleFriend(aOwner)))
            return true;
        // Если крайние кораблики не союзные друг другу, то тыла нет
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
              // Попытка найти внутренний слот
              if (aShipLowOrbit) then
                  tmpSlot.Dec()
              else
                  tmpSlot.Inc();
          // Проверим чтобы слот был пустым и не тылом
          if (aDestination->Landings->IsEmpty(tmpSlot))
              && (CheckBackZone(aIgnore, aDestination, tmpSlot, aOwner))
              then
              Exit(tmpSlot);
          until(tmpSlot = 1);*/
        return 0;
    }

    int TShipControlCustom::DealDamage(TShip * aShip, int aDamage, bool aDestruct)
    {
        // Пропуск ненацеленных стволов
        if (!aShip)
            return 0;
        // Отключение атаки вторым стволом и ретаргет внешних
        if (aShip->Count == 0)
            return 0;
        // Посчитаем количество убитых и общий урон
        int tmpHP = aShip->TechValue(TShipTech::Hp);
        int tmpKilled = std::min(aShip->Count, (int)std::trunc(aDamage / tmpHP));
        int tmpDamage = tmpKilled * tmpHP;
        // Учтем итоговый урон, убавим остаточный, уберем убитые
        int tmpResult = tmpDamage;
        aDamage -= tmpDamage;
        aShip->Count -= tmpKilled;
        if (aDestruct)
            aShip->Destructed += tmpKilled;
        // Проверим наличие корабликов
        if (aShip->Count > 0)
        {
            tmpDamage = std::min(aShip->HP, aDamage);
            aShip->HP -= tmpDamage;
            tmpResult += aDamage;
            // Замена корабля при хп в ноле
            if (aShip->HP == 0)
            {
                aShip->HP = tmpHP - (aDamage - tmpDamage);
                aShip->Count--;
                // Убитые только если нужно
                if (aDestruct)
                    aShip->Destructed++;
            }
        }
        // Если юнит убит - обновим данные планеты
        /*if (tmpKilled > 0)
           m_Thread.ControlPlanets.UpdateShipList(aShip, -TmpKilled);*/
           // Обновим параметры корабля, если он удален - взрываем
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
           // Если ХП есть - обновим данные
           if (tmpShip.Count > 0) then
               begin
               tmpShip.IsDestroyed : = pshchNone;
           TPlanetarThread(Engine).ControlShips.Repair.Check(tmpShip);
           TPlanetarThread(Engine).SocketWriter.ShipUpdateHP(tmpShip);
           end else
               // Удалим с планеты
               begin
               TPlanetarThread(Engine).ControlShips.RemoveFromPlanet.Execute(
                   tmpShip, True, tmpShip.IsDestroyed = pshchDestruct, True);
           end;
           end;*/
    }
}