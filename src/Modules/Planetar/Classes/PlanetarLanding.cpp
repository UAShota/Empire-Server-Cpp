#include "pch.h"
#include "PlanetarLanding.h"
#include "PlanetarPlanet.h"

namespace planetar
{
	void TLandings::Add(TShip * aShip)
	{
		m_Landings[aShip->Landing].Ship = aShip;
		aShip->Planet->Ships->push_back(aShip);
	}

	void TLandings::Remove(TShip * aShip)
	{
		m_Landings[aShip->Landing].Ship = nullptr;
		aShip->Planet->Ships->remove(aShip);
	}

	bool TLandings::HaveShip(int aPosition, TShip * aShip)
	{
		aShip = m_Landings[aPosition].Ship;
		return aShip;
	}
}