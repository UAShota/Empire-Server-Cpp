//todo///////////////////////////////////////////////
//
// Модуль управления планетарной зоной
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"

namespace planetar
{
    // Технологии корабля
    namespace TShipTech
    {
        // Типы технологий корабликов
        enum E
        {
            // Пустая теха
            Empty,
            // Оружие пули
            WeaponeBullet,
            // Возможность постройки
            Active,
            // Аннигиляция
            Annihilation,
            // Броня
            Armor,
            // Запрет разбора конструктором
            SolidBody,
            // Цена
            Cost,
            // Количество в стеке
            Count,
            // Множитель урона
            Damage,
            // Самопочинка
            Repair,
            // Скрытое перемещение
            Hidden,
            // Структура
            Hp,
            // TODO - omdv : Свободная технология 
            Mirror,
            // Безлимитный портал
            StablePortal,
            // Выработка ресурса
            Production,
            // Починка других юнитов
            Fix,
            // Переносное хранилище
            Storage,
            // Вес юнита
            Weight,
            // Скилл разбора
            SkillConstructor,
            // Элитка разбор дополнительных противников
            SkillConstructorEnemy,
            // Элитка разбор в дополнительных союзников
            SkillConstructorFriend,
            // Стационарность
            Stationary,
            // Приоритет атаки
            Priority,
            // Мспользование нижней орбиты
            LowOrbit,
            // Слет с планетоида
            Faster,
            // Защита от атак артилерии с другой планеты
            RangeDefence,
            // Оружие прострела через юнит
            WeaponeOvershot,
            // Возможность влета в тыл
            IntoBackzone,
            // Возможность блокировать с краев
            CornerBlock,
            // Оружие двойная пуля
            WeaponeDoubleBullet,
            // Цель для прострела
            OvershotTarget,
            // Оружие лазер
            WeaponeLaser,
            // Оружие ракета
            WeaponeRocket,
            // Захват лояльности
            Capturer,
            // Блокиратор прострела
            OvershotBlocker,
            // Оружие двойной лазер
            WeaponeDoubleLaser,
            // Блокиратор бытрых юнитовы
            SpeedBlocker,
            // Стабилизатор ЧТ
            WormholeGuard,
            // Строитель юнитов
            Construction,
            // Всего записей
            _Count
        };
    }

    // Тип корабля
    namespace TShipType
    {
        enum E
        {
            // Пустой
            Empty,
            // Транспорт
            Transport,
            // Крыса
            Cruiser,
            // Дредноут
            Drednout,
            // Корвет
            Corvete,
            // Девастатор
            Devastator,
            // Штурмовик
            Invader,
            // Военка
            Millitary,
            // Верфь
            Shipyard,
            // Научная база
            Scient,
            // Сервисная платформа
            Service,
            // Флагман
            Flagship,
            // Всего записей
            _Count
        };
    }

    // Режим корабя
    namespace TShipMode
    {
        enum E
        {
            // Активен
            Active,
            // Блокирован с краев
            Blocked,
            // Лимит для активации
            Full,
            // В походном режиме
            Offline,
            // Идет строительство
            Construction,
            // Всего записей
            _Count
        };
    }

    // Состояния корабля
    namespace TShipState
    {
        enum E
        {
            // Стоит
            Iddle,
            // В движении между слотами
            MovingLocal,
            // В движении между планетами
            MovingGlobal,
            // Паркуется
            Parking,
            // Готовится прыгнуть в портал
            PortalJump,
            // Запустилась аннигиляция
            Annihilation,
            // Всего записей
            _Count
        };
    }

    // Как уничтожился кораблик
    namespace TShipDestroyed
    {
        enum E
        {
            // Никак, живой
            None,
            // Взорвался
            Destruct,
            // Тихо исчез
            Silent,
            // Всего записей
            _Count
        };
    }

    // Таймеры корабля
    namespace TShipTimer
    {
        enum E
        {
            // Постройка
            OpConstruction,
            // Прыжок в портал
            OpPortalJump,
            // Дозаправка
            OpRefill,
            // Полет
            OpFlight,
            // Парковка
            OpParking,
            // Аннигиляция
            OpAnnihilation,
            // Самопочинка
            OpFix,
            // Ремонт союзника
            OpRepair,
            // Скилл разбора юнита
            CdConstructor,
            // Всего записей
            _Count
        };
    }

    // Тип орудийной системы
    namespace TShipWeaponType
    {
        enum E
        {
            // Центральное
            pswCenter,
            // Левое
            pswLeft,
            // Правое
            pswRight,
            // Ракета
            pswRocket
        };
    }

    // Элемент технологии словаря
    struct TShipTechItem
    {
        // Поддерживаемость технологии
        bool Supported;
        // Количество технологий
        int Count;
        // Уровни
        int Levels[5];
        // Время отката
        int Cooldowns[5] = {};
        // Текущий уровень
        int Level;
        // Текуший уровень
        int Value;
        // Текущий кулдаун
        int Cooldown;
    };

    // Купленные технологии
    typedef int TShipTechKeys[TShipTech::_Count];

    // Значения технологии для юнита
    typedef TShipTechKeys TShipTechValues[TShipType::_Count];

    // Ссылка на технологии для юнита
    typedef TShipTechItem TShipTechUnit[TShipTech::_Count];

    // Ссылка на технологии для профиля
    typedef TShipTechUnit TShipTechProfile[TShipType::_Count];

    // Словарь всех технологий
    typedef TShipTechProfile TShipTechRace[globals::TRaceType::_Count];

    // Класс планетарного кораблика
    class TShip
    {
    private:
        // Ссылка на технологии типа
        const TShipTechUnit * m_TechUnit = nullptr;
        // Ссылка на технологии пользователя
        const TShipTechKeys * m_TechKeys = nullptr;
    public:
        // Идентификатор кораблика
        int ID = 0;
        // Владелец кораблика
        globals::TPlayer * Owner = nullptr;
        // Планета, на которой находится кораблик
        class TPlanet * Planet = nullptr;
        // Тип кораблика
        TShipType::E Type = TShipType::Empty;
        // Режим
        TShipMode::E Mode = TShipMode::Active;
        // Состояние
        TShipState::E State = TShipState::Iddle;
        // Количество
        int Count = 0;
        // Здоровье
        int HP = 0;
        // Противник на центральное орудие
        TShip * TargetCenter = nullptr;
        // Противник на левое орудие
        TShip * TargetLeft = nullptr;
        // Противник на правое орудие
        TShip * TargetRight = nullptr;
        // Противник на ракетное орудие
        TShip * TargetRocket = nullptr;
        // Количество топлива
        int Fuel = 0;
        // Количество убитых стеков
        int Destructed = 0;
        // Планета, к которой привязан кораблик
        class TPlanet * attached = nullptr;
        // Слот на планете
        int Landing = 0;
        // Признак, что кораблик захватывает планету
        bool IsCapture = false;
        // Признак автоприцела
        bool IsAutoTarget = false;
        // Признак автоаттача при прилете на планету
        bool IsAutoAttach = false;
        // Признак изменения состояния кораблика
        TShipDestroyed::E IsDestroyed = TShipDestroyed::None;
        // Набор таймеров
        bool Timer[TShipTimer::_Count] = {};
        // Группа, в которой состоит кораблик
        class TShipGroup * Group = nullptr;
        // Текущая планета кораблике в списке планет группы
        int GroupHope = 0;
    public:
        TShip(globals::TPlayer * aOwner) noexcept;
        ~TShip();
        // Возможность автоматического нацеливания арты
        bool CanRangeAutoTarget();
        // Возможность взаимодействовать с кораблем
        bool CanOperable(bool aIgnoreConstruct = false);
        // Смена набора технологий
        void ChangeTech(const TShipTechUnit * aTechUnit, const TShipTechKeys * aTechKeys);
        // Смена группы кораблика
        void ChangeGroup(TShipGroup * aGroup = nullptr);
        // Признак что кораблик активен
        bool IsStateActive();
        // Признак прикрепленной арты
        bool IsAttachedRange(bool aRangeShip);
        // Признак нацеленного кораблика
        bool GetTargeted();
        void SetTargeted(bool aValue);
        // Значение технологии
        int TechValue(TShipTech::E aTechType);
        // Доступность технологии
        int TechActive(TShipTech::E aTechType);
        // Время отката технологии
        int TechCooldown(TShipTech::E aTechType);
    };

    // Словарь кораблей
    typedef std::map<globals::TPlayer *, TShip *> TShipMap;

    // Список кораблей
    typedef std::list<TShip *> TShipList;
}