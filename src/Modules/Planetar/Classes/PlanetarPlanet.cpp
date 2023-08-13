#include "pch.h"
#include "PlanetarPlanet.h"

namespace planetar
{
    TPlanet::TPlanet() noexcept
    {

    }

    TPlanet::~TPlanet()
    {
    }

    bool TPlanet::IsValidDistance(TPlanet * aTarget)
    {
        return (this == aTarget)
            || (sqrt(pow(aTarget->CoordX - CoordX, 2)
                + pow(aTarget->CoordY - CoordY, 2)) <= TPlanet::ciFlyRadius);
    }

    bool TPlanet::IsManned()
    {
        return (Type == TPlanetType::Small) || (Type == TPlanetType::Big);
    }

    bool TPlanet::VisibleByPlayer(globals::TPlayer * aPlayer, bool aHardLight, bool aStrict)
    {
        // ��� � �� ������� ������ ������
        if (!aStrict && (IsBigHole || IsBigEdge))
            return true;
        // ������� �������
        TShipMap * tmpMap = nullptr;
        if (aHardLight)
            tmpMap = &PlayerLightHard;
        else
            tmpMap = &PlayerLightSoft;
        // �������� ������� �������
        if (tmpMap->size() == 0)
            return false;
        // ������ ��� ��������� ��� ������� ������
        for (auto &tmpIt : *tmpMap)
        {
            if (aPlayer->IsRoleFriend(tmpIt.first))
                return true;
        }
        return false;
    }

    int TPlanet::CoverageByPlayer(globals::TPlayer * aPlayer, bool aFullData, int * aFriendCount, int * aEnemyCount)
    {
        int tmpResult = 0;
        aFriendCount = 0;
        aEnemyCount = 0;
        // �������� ������� �������
        if (PlayerCoverage.size() == 0)
            return tmpResult;
        // ������ ��� ����� ��������
        for (auto tmpIt : PlayerCoverage)
        {
            globals::TPlayerRole::E tmpRole = aPlayer->Role(tmpIt.first);
            if (tmpRole == globals::TPlayerRole::Self)
                tmpResult++;
            else if (tmpRole == globals::TPlayerRole::Enemy)
                aEnemyCount++;
            else if (tmpRole == globals::TPlayerRole::Friends)
                aFriendCount++;
        }
        // ���� � ������ ��� ��������� � ���� ��������� - �������� ���� �������
        if ((!aFullData) && (aEnemyCount > 0))
        {
            aFriendCount = 0;
            tmpResult = 0;
        }
        // ������ ������ ��������
        return 0;
    }

    TPlanetState::E TPlanet::StateByVisible(bool aVisible)
    {
        // ��������� ���������� ������ ��� �� ��� ������� ������ ������
        if (((Type == TPlanetType::Hole) && (State != TPlanetState::Inactive)) || (aVisible))
            return State;
        else
            return TPlanetState::Inactive;
    }
}