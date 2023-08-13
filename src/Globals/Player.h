/////////////////////////////////////////////////
//
// ������ �������� ������
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Consts.h"
#include "Components/Transport/Socket.h"

namespace planetar
{
	// ���������������� ������� ����������
	class TProfile;
}

namespace globals
{
	// ���� ������� ������������ ����-�����
	namespace TPlayerRole
	{
		enum E
		{
			Self,
			Enemy,
			Friends,
			Neutral
		};
	}

	// ����� �������� ������
	class TPlayer
	{
	private:
		// ������� ��������� ������� ������
		bool m_Active = false;
	public:
		// ���
		string Name;
		// ��� ������
		string Password;
		// �������������
		int UID = 0;
		// ���������� ������
		int Gold = 0;
		// ���������� ������
		int Credits = 0;
		// ���������� �������
		int Fuel = 0;
		// ������� ����
		bool IsBot = false;
		// ���������� ���������
		TRaceType::E Race = TRaceType::Empty;
		// ���������� � ����������
		transport::TSocketConnection* Connection;
		// ����������� �������
		class planetar::TProfile* Planetar = nullptr;
	private:
		// �������� ��������� ������
		void LoadHoldings();
	public:
		TPlayer() noexcept;
		~TPlayer();
		// ������ ������� ������
		void Start();
		// ��������� ������� ������
		void Stop();
		// ���� ���� ������� �� ��������� ���� � ����� � ������ �������� ����������
		TPlayerRole::E Role(TPlayer* aVersus, bool aHideEnemy = false);
		// ������� ��������� ���� ��������
		bool IsRoleFriend(TPlayer* aVersus);
		// �������� ������� ������������� �����
		void Send(transport::TSocketBuffer* aBuffer, bool aAutoCommit = true);
		// �������� ������� ����������� �����
		void Send(transport::TSocketBuffer& aBuffer);
	};

	// ����� �������
	typedef std::map<int, TPlayer*> TPlayerMap;
}