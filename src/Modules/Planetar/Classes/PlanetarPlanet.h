//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
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
	// Таймеры корабля
	namespace TPlanetTimer
	{
		enum E
		{
			// Боевой тик
			Battle,
			// Тик пульсара
			Pulsar,
			// Захват лояльности
			Capture,
			// Тик ЧТ
			Wormhole,
			// Всего записей
			_Count
		};
	}

	// Состояние планетоида
	namespace TPlanetState
	{
		enum E
		{
			// Активный планетоид
			Active,
			// Планетоид активируется
			Activation,
			// Планетоид неактивен
			Inactive
		};
	}

	// Типы планет
	namespace TPlanetType
	{
		enum E
		{
			// Маленькая
			Small,
			// Обитаемая
			Big,
			// Звезда
			Sun,
			// Гидросостав
			Hydro,
			// Карлик
			Rock,
			// Черная дыра
			Hole,
			// Пульсар
			Pulsar
		};
	}

	// Тип описывающий планету
	class TPlanet
	{
    public:
        // Карта планет
        typedef std::map<int, TPlanet*> Map;
        // Массив планет
        typedef std::vector<TPlanet*> Vector;
	public:
		const int ciFlyRadius = 150;
	public:
		// Уникальный идентификатор в базе
		int UID = 0;
		// Ключ в списке
		int ID = 0;
		// Владелец планеты
		globals::TPlayer * Owner = nullptr;
		// Имя планеты
		const char * Name = nullptr;
		// Тип планеты
		TPlanetType::E Type = TPlanetType::Small;
		// Уровень энергии на планете
		int Energy = 0;
		// Уровень планеты
		int Level = 0;
		// Координаты на сетке по X
		int CoordX = 0;
		// Координаты на сетке по Y
		int CoordY = 0;
		// Дата обнаружения планеты
		double DateDiscover = 0;
		// Строения планеты
	/*Buildings: TPlBuildingList;
		// Хранилища планеты c объектами
	Storages: TPlStorages;
		// Список пустых доступных слотов
	StoragesFree: TIntList;
		// Список пустых слотов для транспорта
	StoragesInactive: TIntList;
	*/
	// Количество хранилищ
		int StoragesCount = 0;
		// Идентификатор захватчика
		globals::TPlayer * CapturePlayer = nullptr;
		// Уровень лояльности захватчика
		double CaptureValue = 0;
		// Ресурс, вырабатываемый планетой
		globals::TResourceType::E ResFactory = globals::TResourceType::Empty;
		// Количество ресурсов для выработки
	/*ResAvailIn: TResListData;
		// Количество свободного места для складирования
	ResAvailOut: TResListData;
		// Количество используемых ресурсов за такт времени
	ResUseIn: TResListData;
		// Количество выработки ресурсов за такт времени
	ResUseOut: TResListData;
		// Ресурсы, необходимые по цепочке
	ResTravel: TResListData;
		// Входящие торговые пути на планету
	ResPathIn: TPlPlanetList;
		// Исходящий торговый пути с планеты
		*/
		TPlanet * ResPathOut = nullptr;
		// Признак включенного производства
		bool HaveProduction = false;
		// Посадочные места планеты
		class TLandings * Landings = nullptr;
		// Список кораблей планеты
		TShipList * Ships = nullptr;;
		// Список количества кораблей каждого участника
		TShipMap * ShipCount = nullptr;;
		// Список количества постройщиков каждого участника
		TShipMap * Constructors = nullptr;;
		// Список внешних кораблей, нацеленных на планету
		TShipList * RangeAttackers = nullptr;;
		// Количество активных сервисок
		int Services = 0;
		// Набор таймеров
		bool Timer[TPlanetTimer::_Count] = {};
		// Количество отрядов каждого игрока, определяющие полную видимость планетоида
		TShipMap PlayerLightSoft;
		// Количество отрядов каждого игрока, определяющие частичную видимость планетоида
		TShipMap PlayerLightHard;
		// Количество отрядов каждого игрока, которые определяют область закраски
		TShipMap PlayerCoverage;
		// Состояние активности планеты
		TPlanetState::E State = TPlanetState::Inactive;
		// Время смены состояния планетоида
		int StateTime = 0;
		// Топливный запас
		int Fuel = 0;
		// Список соседних планет
		Vector Links;
		// Ссылка на портал для планеты
		class TPortal * Portal = nullptr;
		// Признак что планета захватывается
		bool InCapture = false;
		// Включен гравитационный потенциал
		bool IsLowGravity = false;
		// Признак что планета должна переприцелить корабли
		bool IsRetarget = false;
		// Признак черной дыры
		bool IsBigHole = false;
		// Признак округи черной дыры
		bool IsBigEdge = false;
	public:
		TPlanet() noexcept;
		~TPlanet();
		// Проверка расстояния между двумя объектами
		bool IsValidDistance(TPlanet * aTarget);
		// Признак обитаемой планеты
		bool IsManned();
		// Определение видимости для игрока
		bool VisibleByPlayer(globals::TPlayer * aPlayer, bool aHardLight = false, bool aStrict = false);
		// Определение покрытия для игрока
		int CoverageByPlayer(globals::TPlayer * aPlayer, bool aFullData, int *AFriendCount, int *AEnemyCount);
		// Определения состояния для роли игрока
		TPlanetState::E StateByVisible(bool aVisible);
	};
}