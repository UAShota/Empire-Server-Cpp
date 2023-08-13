//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "PlanetarEngine.h"
#include "Modules/Planetar/Classes/PlanetarHangar.h"
#include "Modules/Planetar/Classes/PlanetarShip.h"

namespace globals
{
    class TPlayer;
}

/*        // �������� ������ ���������� ����������
        SocketWriter.PlayerTechWarShipLoad(tmpProfile.TechShipProfile, tmpProfile.TechShipValues, aPlayer);
        // �������� ������ ���������� ��������
        SocketWriter.PlayerTechBuildingLoad(tmpProfile.TechBuildingProfile, tmpProfile.TechBuildingValues, aPlayer);
                // �������� ������ ���������
        SocketWriter.PlayerStorageChange(aPlayer.Storage.Size, aPlayer.Storage.Storages, aPlayer);
        // �������� �����
        for tmpI : = 0 to TPlanetar(aPlayer.Planetar).Hangar.Size do
            begin
            SocketWriter.PlayerHangarUpdate(tmpI,
                TPlanetar(aPlayer.Planetar).Hangar.Slots[tmpI].Count,
                TPlanetar(aPlayer.Planetar).Hangar.Slots[tmpI].ShipType, aPlayer);
        end;

*/

namespace planetar
{
    // ����� ���������� ����������� ��������
    class TProfile
    {
    private:
        // ����� ��������� ��������
        class globals::TPlayer * m_Player = nullptr;
        // ������ �� ���� ���������
        TPlanetarEngine * m_Engine = nullptr;
        // ������ �� ��������� ��������
        TPlanetarEngine * m_Subscribe = nullptr;
        // ����������� ����� �������
        THangar m_Hangar;
        // ��������� ���� ������
        TShipTechValues * m_TechShipValues = nullptr;
        // ������ �� ���� ���� ������
        TShipTechProfile * m_TechShipProfile = nullptr;
        // ��������� ���� ��������
    /*TechBuildingValues: TPlBuildingTechValues;
        // ������ �� ���� ���� ������
    TechBuildingProfile: PPlBuildingTechProfile;*/
    private:
        // �������� ���������� ����������
        void LoadTechWarShips();
        // �������� ���������� ��������
        void LoadTechBuildings();
        // �������� ������
        void LoadHangar();
    public:
        // �����������
        TProfile(globals::TPlayer * aPlayer);
        // �������� �������
        void Start();
        // �������� �������
        void Stop();
        // ������� ����������� ���������
        bool Available();
        // �������� ���������� ������ � ������� ����������
        bool Subscribe(globals::TPlayer * aPlayer);
        // ������� �������� ������
        void Unsubscribe();
        // �������� ������� � ���������
        bool Command();

        // ������� ���������� ���������
        void BuyTech(TShipType::E aShipType, TShipTech::E aTech, globals::TPlayer * aPlayer);
        // ������� ���������� ��������
        /*procedure BuyTech(aBuildingType: TPlBuildingType; aPlayer: TGlPlayer); overload;*/
        // ��������� ���������� ���������� ���������
        TShipTechItem * Tech(TShipType::E aShipType, TShipTech::E aTech);
        // ��������� ���������� ���������� ��������
        /*function TechBuilding(aBuildingType: TPlBuildingType; aTech: TPlBuildingTechType) : Int; overload;*/
    };
}