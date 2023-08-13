/////////////////////////////////////////////////
//
// ������ ���������� ����� � ��������
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

namespace globals
{
	// ���� ������� ���
	namespace TRaceType
	{
		enum E
		{
			Empty,
			Human,
			Maloc,
			Peleng,
			Gaal,
			Feyan,
			Klisan,
			_Count
		};
	}

    // ����� ���������� ��������
	class TConsts
	{
	public:
		// �������� ������ ��� �������� ������
		const int MaxPersonalStorages = 100;
	};
}