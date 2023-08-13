#include "pch.h"
#include "PlanetarShipControlConstruct.h"
#include "Modules/Planetar/Engine/PlanetarProfile.h"

namespace planetar
{
    int TShipControlConstruct::GetHPperTick(TShip * aShip)
    {

        // Найдем количество верфей строящегося игрока, 1 верфь есть всегда по умолчанию
        if (true/*!aShip->Planet->Constructors->TryGetValue(aShip->Owner, tmpCount)*/)
        {
            if (aShip->TechActive(TShipTech::Stationary))
                /*tmpCount->Value = 1*/;
            else
                return -1;
        }
        // Минимум 150хп // сек
        return std::min(0/*tmpCount->Value*/, I_MAX_SHIPYARD_ACTIVE) * aShip->TechValue(TShipTech::Construction);
    }

    bool TShipControlConstruct::OnTimer(TShip * aShip, int & aCounter, int & aValue)
    {
        // Попробуем завершить постройку
        if (aCounter == 0)
        {
            if (!aShip->CanOperable(true))
                return false;
            aShip->HP = aShip->TechValue(TShipTech::Hp);
            // Завершим постройку
            /*FThread->SocketWriter->ShipUpdateHP(aShip);
            // Выставим стартовые состояния если кораблик не в состоянии полета
           m_Thread->ControlShips->StandUp->Execute(aShip);
            // Обновим параметры планеты для стационарных построек
           m_Thread->ControlPlanets->UpdateShipList(aShip, aShip->Count);*/
           // Отправим смену таймера
            return true;
        }
        // Определим хп
        int tmpCount = GetHPperTick(aShip);
        int tmpTotal = (aShip->Count * aShip->TechValue(TShipTech::Hp));
        // Нельзя строить не в простое
        if (aShip->CanOperable(true))
            aShip->HP += tmpCount;
        else
            tmpCount = -tmpCount;
        // Если построены все юниты - уведомим
        if (aShip->HP >= tmpTotal)
            aCounter = 0;
        // Если нет - проверим, изменилась ли скорость
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
        // Найдем свободный слот
        int tmpSlot = GetFreeSlot(tmpBackzone, aPlanet, tmpLowOrbit, aPlayer);
        if (tmpSlot == 0)
        {
            Log("Slot");
            return nullptr;
        }
        // Попытка высадить ожидаемый кораблик в указанный слот
        if (!CheckArrival(aPlanet, tmpLowOrbit, tmpSlot, tmpSlot, aPlanet, aPlanet->Owner, false))
        {
            Log("Arriva");
            return nullptr;
        }
        // Дабы не захламлять
        int tmpCount = std::min(aCount, aPlayer->Planetar->Tech(aShipType, TShipTech::Count)->Value);
        int tmpCost = tmpCount * aPlayer->Planetar->Tech(aShipType, TShipTech::Cost)->Value;
        // Проверить наличие ресурсов для постройки
        /*if (aPlanet->ResAvailIn[resModules] < tmpCost) then
            begin
            TLogAccess->Write(ClassName, 'Modules');
        Exit();
        end;*/
        // Если все есть - построим кораблик
        TShip * tmpShip = CreateShip(aPlanet, aShipType, tmpSlot, tmpCount, aPlayer);
        tmpShip->Mode = TShipMode::Construction;
        tmpShip->HP = 0;
        // Уменьшим количество затраченных ресурсов
        /*FThread->ControlStorages->DecrementResource(resModules, aPlanet, tmpCost);
        // Добавим созданный кораблик на планеты
       m_Thread->ControlShips->AddToPlanet->Execute(tmpShip, aPlanet,false,false, aPlanet->Timer[ppltmBattle]);
        // Отправим сообщение
       m_Thread->SocketWriter->ShipCreate(tmpShip);
        // Добавим таймер
       m_Thread->WorkerShips->TimerAdd(Result, TShipTimer::OpConstruction, GetHPperTick(Result),
            OnTimer, tmpShip->Count * Result->TechValue(TShipTech::Hp) // GetHPperTick(Result));
            */
        return tmpShip;
    }

    void TShipControlConstruct::Player(TPlanet * aPlanet, TShipType::E aShipType, int aCount, globals::TPlayer * aPlayer)
    {
        // Нельзя строить непонятное количество юнитов
        if (aCount <= 0)
        {
            Log("Count");
            return;
        }
        // Нельзя строить если планета в бою
        if (aPlanet->Timer[TPlanetTimer::Battle])
        {
            Log("Battle");
            return;
        }
        // Нельзя строить если технология закрыта
        if (aPlayer->Planetar->Tech(aShipType, TShipTech::Active)->Value == 0)
        {
            Log("Tech");
            return;
        }
        // Определим параметры будущего юнита
        bool tmpStationary = aPlayer->Planetar->Tech(aShipType, TShipTech::Stationary)->Supported;
        // Проверка постройки нестационарнго флота
        if (!aPlanet->IsManned())
        {
            // Нельзя строить на чужой планете
            if (!aPlanet->Owner->IsRoleFriend(aPlayer))
            {
                Log("Role");
                return;
            }
            // На нежилых можно строить только стационарки
            if (!tmpStationary)
            {
                Log("Manned");
                return;
            }
        }
        // На жилых не стационарный флот можно строить только если есть верфь
        if ((!tmpStationary)
            && (!true/*aPlanet->Constructors->ContainsKey(aPlayer)*/))
        {
            Log("Shipyard");
            return;
        }
        // Иначе построим кораблик
        Execute(aPlanet, aShipType, aCount, aPlayer);
    }
}