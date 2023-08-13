#include "pch.h"
#include "PlanetarShipControlTargetLocal.h"

namespace planetar
{
    bool TShipControlTargetLocal::GetShipPriority(TShip * aLeft, TShip * aRight)
    {
        // ����� ����� ���� ��� ������� ��� ���� ��� �����
        return (aLeft)
            && (!aRight
                || (aLeft->Type == aRight->Type)
                || (aLeft->TechValue(TShipTech::Priority) <= aRight->TechValue(TShipTech::Priority)));
    }

    int TShipControlTargetLocal::GetShipRange(TShip * aLeft, TShip * aRight)
    {
        int tmpRange = std::abs(aLeft->Landing - aRight->Landing);
        // ���������� �����
        int tmpRevert = 0;/*TLanding->Offset(-Result);*/
    // ������
        if (tmpRevert < tmpRange)
            tmpRange = tmpRevert;
        return tmpRange;
    }

    bool TShipControlTargetLocal::GetShipNear(TShip * aCenter, TShip * aLeft, TShip * aRight)
    {
        // ����� ����� ���� ��� ������� ��� ���� �� ������� �����
        return (aLeft)
            && (!aRight 
                || (GetShipRange(aCenter, aLeft) <= GetShipRange(aCenter, aRight)));
    }

    bool TShipControlTargetLocal::GetTargetingToHead(TShip * aShip, TShip * aRightShip, TShip * aLeftShip, TShip * & aWeapone)
    {
        TShip * tmpTargetCenter;
        if (GetShipNear(aShip, aLeftShip, aRightShip))
            tmpTargetCenter = aLeftShip;
        else
            tmpTargetCenter = aRightShip;
        // �������� ���������
        if (aWeapone != tmpTargetCenter)
        {
            aWeapone = tmpTargetCenter;
            return true;
        };
        return false;
    }

    bool TShipControlTargetLocal::GetTargetingToCorners(TShip * aShip, TShip * aRightShip, TShip * aLeftShip)
    {
        // ������������ ������� �� ������ ���� ��� ����
        if (!aLeftShip)
            aLeftShip = aRightShip;
        if (!aRightShip)
            aRightShip = aLeftShip;
        // �������� ���������
        if (aShip->TargetRight != aRightShip)
        {
            aShip->TargetRight = aRightShip;
            return true;
        };
        if (aShip->TargetLeft != aLeftShip)
        {
            aShip->TargetLeft = aLeftShip;
            return true;
        };
        return false;
    }

    bool TShipControlTargetLocal::GetTargetingToInner(TShip * aShip, TShip * aRightShip, TShip * aLeftShip, TShip * aRightShipInner, TShip * aLeftShipInner)
    {
        return false;
    }


    bool TShipControlTargetLocal::GetTargetingToDouble(TShip * aShip, TShip * aRightShip, TShip * aLeftShip, TShip * aRightShipInner, TShip * aLeftShipInner)
    {
        // ������� ������� ������ �� ��������
        if (GetShipNear(aShip, aLeftShipInner, aRightShip))
            aRightShip = aLeftShipInner;
        else if (GetShipNear(aShip, aRightShipInner, aLeftShip))
            aLeftShip = aRightShipInner;
        // ������������ ������� �� ������ ���� ��� ����
        if (!aRightShip)
            aRightShip = aLeftShip;
        if (!aLeftShip)
            aLeftShip = aRightShip;
        // �������� ������� ������
        if (aShip->TargetRight != aRightShip)
        {
            aShip->TargetRight = aRightShip;
            return true;
        };
        // �������� ������ ������
        if (aShip->TargetLeft != aLeftShip)
        {
            aShip->TargetLeft = aLeftShip;
            return true;
        };
        return false;
    }

    TShip * TShipControlTargetLocal::GetTargetShip(TShip * aShip, bool aIgnoreFriend, bool aLeft, bool aOneStep, globals::TPlayer * aOwner)
    {
        /*	int tmpSlot = aShip->Landing;
            do
            {
                // ������� ����
                if (aLeft)
                    tmpSlot--;
                else
                    tmpSlot++;
                // ����� �������� �� �����
                TShip * tmpShip = nullptr;
                if (aShip->Planet->Landings->HaveShip(tmpSlot, tmpShip))
                {
                    // ���� ��� ��������� - �� ������ ���� �������� ��� ���������
                    if (!tmpShip->Owner->IsRoleFriend(aOwner))
                    {
                        if ((tmpShip->IsStateActive())
                            || (0/*tmpShip->Planet->ShipCount[AShip.Owner].Active * /== 0))
                            return tmpShip;
                    }
                    else
                    {
                        // ����� �������, ����� �� ������������� ������
                        if ((!aIgnoreFriend)
                            && (aShip->IsStateActive()))
                            return nullptr;
                    }
                    // ���� �������� �� ������ - ������ ����������
                    tmpShip = nullptr;
                }
                // ����� ������ �������� ��������
                if (aOneStep)
                    break;
            } while (tmpSlot == aShip->Landing);
        }

        bool TShipControlTargetLocal::GetWeaponeOvershot(TShip * aShip)
        {
    /*	TShip *tmpShipRight = GetTargetShip(aShip,false, true,false, aShip->Owner);
        TShip *tmpShipLeft = GetTargetShip(aShip,false,false,false, aShip->Owner);
            // �������� �������� ������
            if assigned(tmpShipRight)
                and (not tmpShipRight.TechActive(plttOvershotblocker))
                and (GetShipRange(aShip, tmpShipRight) = 1)
                then
                tmpShipInnerRight : = GetTargetShip(tmpShipRight,false, True, True, aShip.Owner)
            else
                tmpShipInnerRight : = nil;
            // �������� �������� �����
            if assigned(tmpShipLeft)
                and (not tmpShipLeft.TechActive(plttOvershotblocker))
                and (GetShipRange(aShip, tmpShipLeft) = 1)
                then
                tmpShipInnerLeft : = GetTargetShip(tmpShipLeft,false,false, True, aShip.Owner)
            else
                tmpShipInnerLeft : = nil;
            // ��������� ������ ����
            TargetingToInner(aShip, tmpShipRight, tmpShipLeft, tmpShipInnerRight, tmpShipInnerLeft);*/
        return nullptr;
    }

    bool TShipControlTargetLocal::GetWeaponeOverFriends(TShip * aShi, TShip * * aWeapone)
    {
        return false;
    }

    bool TShipControlTargetLocal::GetWeaponeDoubleLaser(TShip * aShip)
    {
        return false;
    }

    bool TShipControlTargetLocal::GetWeaponeDoubleBullet(TShip * aShip)
    {
        TShip * tmpShipRight = GetTargetShip(aShip, false, true, false, aShip->Owner);
        TShip * tmpShipLeft = GetTargetShip(aShip, false, false, false, aShip->Owner);
        // ��������� ������ ����, ������ ����� ��������
        return GetTargetingToCorners(aShip, tmpShipRight, tmpShipLeft);
    }

    bool TShipControlTargetLocal::GetWeaponeBullet(TShip * aShip)
    {
        return false;
    }

    void TShipControlTargetLocal::Execute(TShip * aShip)
    {
    }
}