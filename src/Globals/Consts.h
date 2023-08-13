/////////////////////////////////////////////////
//
// Модуль глобальных типов и констант
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

namespace globals
{
	// Типы игровых рас
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

    // Класс глобальных констант
	class TConsts
	{
	public:
		// Максимум слотов для хранилща игрока
		const int MaxPersonalStorages = 100;
	};
}