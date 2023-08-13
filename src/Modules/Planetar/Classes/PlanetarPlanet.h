//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Consts.h"
#include "Globals/Player.h"
#include "Globals/Resource.h"
#include "PlanetarShip.h"

namespace planetar
{
	// ������� �������
	namespace TPlanetTimer
	{
		enum E
		{
			// ������ ���
			Battle,
			// ��� ��������
			Pulsar,
			// ������ ����������
			Capture,
			// ��� ��
			Wormhole,
			// ����� �������
			_Count
		};
	}

	// ��������� ����������
	namespace TPlanetState
	{
		enum E
		{
			// �������� ���������
			Active,
			// ��������� ������������
			Activation,
			// ��������� ���������
			Inactive
		};
	}

	// ���� ������
	namespace TPlanetType
	{
		enum E
		{
			// ���������
			Small,
			// ���������
			Big,
			// ������
			Sun,
			// �����������
			Hydro,
			// ������
			Rock,
			// ������ ����
			Hole,
			// �������
			Pulsar
		};
	}

	// ��� ����������� �������
	class TPlanet
	{
    public:
        // ����� ������
        typedef std::map<int, TPlanet*> Map;
        // ������ ������
        typedef std::vector<TPlanet*> Vector;
	public:
		const int ciFlyRadius = 150;
	public:
		// ���������� ������������� � ����
		int UID = 0;
		// ���� � ������
		int ID = 0;
		// �������� �������
		globals::TPlayer * Owner = nullptr;
		// ��� �������
		const char * Name = nullptr;
		// ��� �������
		TPlanetType::E Type = TPlanetType::Small;
		// ������� ������� �� �������
		int Energy = 0;
		// ������� �������
		int Level = 0;
		// ���������� �� ����� �� X
		int CoordX = 0;
		// ���������� �� ����� �� Y
		int CoordY = 0;
		// ���� ����������� �������
		double DateDiscover = 0;
		// �������� �������
	/*Buildings: TPlBuildingList;
		// ��������� ������� c ���������
	Storages: TPlStorages;
		// ������ ������ ��������� ������
	StoragesFree: TIntList;
		// ������ ������ ������ ��� ����������
	StoragesInactive: TIntList;
	*/
	// ���������� ��������
		int StoragesCount = 0;
		// ������������� ����������
		globals::TPlayer * CapturePlayer = nullptr;
		// ������� ���������� ����������
		double CaptureValue = 0;
		// ������, �������������� ��������
		globals::TResourceType::E ResFactory = globals::TResourceType::Empty;
		// ���������� �������� ��� ���������
	/*ResAvailIn: TResListData;
		// ���������� ���������� ����� ��� �������������
	ResAvailOut: TResListData;
		// ���������� ������������ �������� �� ���� �������
	ResUseIn: TResListData;
		// ���������� ��������� �������� �� ���� �������
	ResUseOut: TResListData;
		// �������, ����������� �� �������
	ResTravel: TResListData;
		// �������� �������� ���� �� �������
	ResPathIn: TPlPlanetList;
		// ��������� �������� ���� � �������
		*/
		TPlanet * ResPathOut = nullptr;
		// ������� ����������� ������������
		bool HaveProduction = false;
		// ���������� ����� �������
		class TLandings * Landings = nullptr;
		// ������ �������� �������
		TShipList * Ships = nullptr;;
		// ������ ���������� �������� ������� ���������
		TShipMap * ShipCount = nullptr;;
		// ������ ���������� ������������ ������� ���������
		TShipMap * Constructors = nullptr;;
		// ������ ������� ��������, ���������� �� �������
		TShipList * RangeAttackers = nullptr;;
		// ���������� �������� ��������
		int Services = 0;
		// ����� ��������
		bool Timer[TPlanetTimer::_Count] = {};
		// ���������� ������� ������� ������, ������������ ������ ��������� ����������
		TShipMap PlayerLightSoft;
		// ���������� ������� ������� ������, ������������ ��������� ��������� ����������
		TShipMap PlayerLightHard;
		// ���������� ������� ������� ������, ������� ���������� ������� ��������
		TShipMap PlayerCoverage;
		// ��������� ���������� �������
		TPlanetState::E State = TPlanetState::Inactive;
		// ����� ����� ��������� ����������
		int StateTime = 0;
		// ��������� �����
		int Fuel = 0;
		// ������ �������� ������
		Vector Links;
		// ������ �� ������ ��� �������
		class TPortal * Portal = nullptr;
		// ������� ��� ������� �������������
		bool InCapture = false;
		// ������� �������������� ���������
		bool IsLowGravity = false;
		// ������� ��� ������� ������ ������������� �������
		bool IsRetarget = false;
		// ������� ������ ����
		bool IsBigHole = false;
		// ������� ������ ������ ����
		bool IsBigEdge = false;
	public:
		TPlanet() noexcept;
		~TPlanet();
		// �������� ���������� ����� ����� ���������
		bool IsValidDistance(TPlanet * aTarget);
		// ������� ��������� �������
		bool IsManned();
		// ����������� ��������� ��� ������
		bool VisibleByPlayer(globals::TPlayer * aPlayer, bool aHardLight = false, bool aStrict = false);
		// ����������� �������� ��� ������
		int CoverageByPlayer(globals::TPlayer * aPlayer, bool aFullData, int *AFriendCount, int *AEnemyCount);
		// ����������� ��������� ��� ���� ������
		TPlanetState::E StateByVisible(bool aVisible);
	};
}