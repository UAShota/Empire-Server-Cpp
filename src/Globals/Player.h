/////////////////////////////////////////////////
//
// Модуль описания игрока
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
	// Предопределенный профиль планетарки
	class TProfile;
}

namespace globals
{
	// Роли игроков относительно друг-друга
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

	// Класс описания игрока
	class TPlayer
	{
	private:
		// Признак активного профиля игрока
		bool m_Active = false;
	public:
		// Имя
		string Name;
		// Хеш пароля
		string Password;
		// Идентификатор
		int UID = 0;
		// Количество валюты
		int Gold = 0;
		// Количество доната
		int Credits = 0;
		// Количество топлива
		int Fuel = 0;
		// Признак бота
		bool IsBot = false;
		// Глобальное хранилище
		TRaceType::E Race = TRaceType::Empty;
		// Информация о соединении
		transport::TSocketConnection* Connection;
		// Планетарный профиль
		class planetar::TProfile* Planetar = nullptr;
	private:
		// Загрузка хранилища игрока
		void LoadHoldings();
	public:
		TPlayer() noexcept;
		~TPlayer();
		// Запуск модулей игрока
		void Start();
		// Остановка модулей игрока
		void Stop();
		// Роль двух игроков по отношению друг к другу с учетом сокрытия противника
		TPlayerRole::E Role(TPlayer* aVersus, bool aHideEnemy = false);
		// Быстрое получение роли союзника
		bool IsRoleFriend(TPlayer* aVersus);
		// Отправка команды неуправляемый буфер
		void Send(transport::TSocketBuffer* aBuffer, bool aAutoCommit = true);
		// Отправка команды управляемый буфер
		void Send(transport::TSocketBuffer& aBuffer);
	};

	// Карта игроков
	typedef std::map<int, TPlayer*> TPlayerMap;
}