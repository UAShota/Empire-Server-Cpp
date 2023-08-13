#include "pch.h"
#include "PlanetarShip.h"
#include "PlanetarPlanet.h"
#include "PlanetarShipGroup.h"

namespace planetar
{
	TShip::TShip(globals::TPlayer * aOwner) noexcept
	{
        Owner = aOwner;
	}

	TShip::~TShip()
	{
		ChangeGroup();
	}

	bool TShip::CanRangeAutoTarget()
	{
		return (TechActive(TShipTech::WeaponeRocket))
			&& (!attached)
			&& (!Planet->Timer[TPlanetTimer::Battle])
			&& (IsStateActive());
	}

	bool TShip::CanOperable(bool aIgnoreConstruct)
	{
		return ((State == TShipState::Iddle) || (State == TShipState::Parking))
			&& (aIgnoreConstruct || (Mode != TShipMode::Construction));
	}

	void TShip::ChangeTech(const TShipTechUnit * aTechUnit, const TShipTechKeys * aTechKeys)
	{
		m_TechUnit = aTechUnit;
		m_TechKeys = aTechKeys;
	}

	void TShip::ChangeGroup(TShipGroup * aGroup)
	{
		if (!Group)
			Group->Remove(this);
		Group = aGroup;
		GroupHope = 0;
	}

	bool TShip::IsStateActive()
	{
		return (State == TShipState::Iddle)
			&& (Mode == TShipMode::Active);
	}

	bool TShip::IsAttachedRange(bool aRangeShip)
	{
		return (attached)
			&& (attached != Planet)
			&& (!aRangeShip || (TechActive(TShipTech::WeaponeRocket)));
	}

	bool TShip::GetTargeted()
	{
		return (TargetCenter) || (TargetLeft) || (TargetRight) || (TargetRocket);
	}

	void TShip::SetTargeted(bool aValue)
	{
		if (!aValue)
		{
			TargetCenter = nullptr;
			TargetLeft = nullptr;
			TargetRight = nullptr;
			TargetRocket = nullptr;
			IsAutoTarget = false;
		}
	}

	int TShip::TechValue(TShipTech::E aTechType)
	{
		return m_TechUnit[aTechType]->Levels[*m_TechKeys[aTechType]];
	}

	int TShip::TechActive(TShipTech::E aTechType)
	{
		return (TechValue(aTechType) > 0);
	}

	int TShip::TechCooldown(TShipTech::E aTechType)
	{
		return m_TechUnit[aTechType]->Cooldowns[*m_TechKeys[aTechType]];
	}
}