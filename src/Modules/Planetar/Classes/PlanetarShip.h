//todo///////////////////////////////////////////////
//
// ������ ���������� ����������� �����
// Copyright(c) 2016 UAShota
//
// Rev F  2018.08.10
//
/////////////////////////////////////////////////

#pragma once

#include "Globals/Player.h"

namespace planetar
{
    // ���������� �������
    namespace TShipTech
    {
        // ���� ���������� ����������
        enum E
        {
            // ������ ����
            Empty,
            // ������ ����
            WeaponeBullet,
            // ����������� ���������
            Active,
            // �����������
            Annihilation,
            // �����
            Armor,
            // ������ ������� �������������
            SolidBody,
            // ����
            Cost,
            // ���������� � �����
            Count,
            // ��������� �����
            Damage,
            // �����������
            Repair,
            // ������� �����������
            Hidden,
            // ���������
            Hp,
            // TODO - omdv : ��������� ���������� 
            Mirror,
            // ����������� ������
            StablePortal,
            // ��������� �������
            Production,
            // ������� ������ ������
            Fix,
            // ���������� ���������
            Storage,
            // ��� �����
            Weight,
            // ����� �������
            SkillConstructor,
            // ������ ������ �������������� �����������
            SkillConstructorEnemy,
            // ������ ������ � �������������� ���������
            SkillConstructorFriend,
            // ��������������
            Stationary,
            // ��������� �����
            Priority,
            // ������������� ������ ������
            LowOrbit,
            // ���� � ����������
            Faster,
            // ������ �� ���� ��������� � ������ �������
            RangeDefence,
            // ������ ��������� ����� ����
            WeaponeOvershot,
            // ����������� ����� � ���
            IntoBackzone,
            // ����������� ����������� � �����
            CornerBlock,
            // ������ ������� ����
            WeaponeDoubleBullet,
            // ���� ��� ���������
            OvershotTarget,
            // ������ �����
            WeaponeLaser,
            // ������ ������
            WeaponeRocket,
            // ������ ����������
            Capturer,
            // ���������� ���������
            OvershotBlocker,
            // ������ ������� �����
            WeaponeDoubleLaser,
            // ���������� ������ �������
            SpeedBlocker,
            // ������������ ��
            WormholeGuard,
            // ��������� ������
            Construction,
            // ����� �������
            _Count
        };
    }

    // ��� �������
    namespace TShipType
    {
        enum E
        {
            // ������
            Empty,
            // ���������
            Transport,
            // �����
            Cruiser,
            // ��������
            Drednout,
            // ������
            Corvete,
            // ����������
            Devastator,
            // ���������
            Invader,
            // ������
            Millitary,
            // �����
            Shipyard,
            // ������� ����
            Scient,
            // ��������� ���������
            Service,
            // �������
            Flagship,
            // ����� �������
            _Count
        };
    }

    // ����� ������
    namespace TShipMode
    {
        enum E
        {
            // �������
            Active,
            // ���������� � �����
            Blocked,
            // ����� ��� ���������
            Full,
            // � �������� ������
            Offline,
            // ���� �������������
            Construction,
            // ����� �������
            _Count
        };
    }

    // ��������� �������
    namespace TShipState
    {
        enum E
        {
            // �����
            Iddle,
            // � �������� ����� �������
            MovingLocal,
            // � �������� ����� ���������
            MovingGlobal,
            // ���������
            Parking,
            // ��������� �������� � ������
            PortalJump,
            // ����������� �����������
            Annihilation,
            // ����� �������
            _Count
        };
    }

    // ��� ����������� ��������
    namespace TShipDestroyed
    {
        enum E
        {
            // �����, �����
            None,
            // ���������
            Destruct,
            // ���� �����
            Silent,
            // ����� �������
            _Count
        };
    }

    // ������� �������
    namespace TShipTimer
    {
        enum E
        {
            // ���������
            OpConstruction,
            // ������ � ������
            OpPortalJump,
            // ����������
            OpRefill,
            // �����
            OpFlight,
            // ��������
            OpParking,
            // �����������
            OpAnnihilation,
            // �����������
            OpFix,
            // ������ ��������
            OpRepair,
            // ����� ������� �����
            CdConstructor,
            // ����� �������
            _Count
        };
    }

    // ��� ��������� �������
    namespace TShipWeaponType
    {
        enum E
        {
            // �����������
            pswCenter,
            // �����
            pswLeft,
            // ������
            pswRight,
            // ������
            pswRocket
        };
    }

    // ������� ���������� �������
    struct TShipTechItem
    {
        // ���������������� ����������
        bool Supported;
        // ���������� ����������
        int Count;
        // ������
        int Levels[5];
        // ����� ������
        int Cooldowns[5] = {};
        // ������� �������
        int Level;
        // ������� �������
        int Value;
        // ������� �������
        int Cooldown;
    };

    // ��������� ����������
    typedef int TShipTechKeys[TShipTech::_Count];

    // �������� ���������� ��� �����
    typedef TShipTechKeys TShipTechValues[TShipType::_Count];

    // ������ �� ���������� ��� �����
    typedef TShipTechItem TShipTechUnit[TShipTech::_Count];

    // ������ �� ���������� ��� �������
    typedef TShipTechUnit TShipTechProfile[TShipType::_Count];

    // ������� ���� ����������
    typedef TShipTechProfile TShipTechRace[globals::TRaceType::_Count];

    // ����� ������������ ���������
    class TShip
    {
    private:
        // ������ �� ���������� ����
        const TShipTechUnit * m_TechUnit = nullptr;
        // ������ �� ���������� ������������
        const TShipTechKeys * m_TechKeys = nullptr;
    public:
        // ������������� ���������
        int ID = 0;
        // �������� ���������
        globals::TPlayer * Owner = nullptr;
        // �������, �� ������� ��������� ��������
        class TPlanet * Planet = nullptr;
        // ��� ���������
        TShipType::E Type = TShipType::Empty;
        // �����
        TShipMode::E Mode = TShipMode::Active;
        // ���������
        TShipState::E State = TShipState::Iddle;
        // ����������
        int Count = 0;
        // ��������
        int HP = 0;
        // ��������� �� ����������� ������
        TShip * TargetCenter = nullptr;
        // ��������� �� ����� ������
        TShip * TargetLeft = nullptr;
        // ��������� �� ������ ������
        TShip * TargetRight = nullptr;
        // ��������� �� �������� ������
        TShip * TargetRocket = nullptr;
        // ���������� �������
        int Fuel = 0;
        // ���������� ������ ������
        int Destructed = 0;
        // �������, � ������� �������� ��������
        class TPlanet * attached = nullptr;
        // ���� �� �������
        int Landing = 0;
        // �������, ��� �������� ����������� �������
        bool IsCapture = false;
        // ������� �����������
        bool IsAutoTarget = false;
        // ������� ���������� ��� ������� �� �������
        bool IsAutoAttach = false;
        // ������� ��������� ��������� ���������
        TShipDestroyed::E IsDestroyed = TShipDestroyed::None;
        // ����� ��������
        bool Timer[TShipTimer::_Count] = {};
        // ������, � ������� ������� ��������
        class TShipGroup * Group = nullptr;
        // ������� ������� ��������� � ������ ������ ������
        int GroupHope = 0;
    public:
        TShip(globals::TPlayer * aOwner) noexcept;
        ~TShip();
        // ����������� ��������������� ����������� ����
        bool CanRangeAutoTarget();
        // ����������� ����������������� � ��������
        bool CanOperable(bool aIgnoreConstruct = false);
        // ����� ������ ����������
        void ChangeTech(const TShipTechUnit * aTechUnit, const TShipTechKeys * aTechKeys);
        // ����� ������ ���������
        void ChangeGroup(TShipGroup * aGroup = nullptr);
        // ������� ��� �������� �������
        bool IsStateActive();
        // ������� ������������� ����
        bool IsAttachedRange(bool aRangeShip);
        // ������� ����������� ���������
        bool GetTargeted();
        void SetTargeted(bool aValue);
        // �������� ����������
        int TechValue(TShipTech::E aTechType);
        // ����������� ����������
        int TechActive(TShipTech::E aTechType);
        // ����� ������ ����������
        int TechCooldown(TShipTech::E aTechType);
    };

    // ������� ��������
    typedef std::map<globals::TPlayer *, TShip *> TShipMap;

    // ������ ��������
    typedef std::list<TShip *> TShipList;
}