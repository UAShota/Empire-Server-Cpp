#include "pch.h"
#include "PlanetarShipGroup.h"

namespace planetar
{
/*    TShipGroup::TShipGroup(TPlanetList * aPlanetList, TShipList * aShipList)
    {
       m_Planets = aPlanetList;
       m_Ships = aShipList;
        // Зададим корабликам нашу группу
        for (TShipListIt tmpShip = m_Ships->begin(); tmpShip != m_Ships->end(); ++tmpShip)
            (*tmpShip)->ChangeGroup(this);
    }*/

    TShipGroup::~TShipGroup()
    {
       /* delete(m_Planets);*/
        delete(m_Ships);
    }

    void TShipGroup::SortByPriority()
    {
    }

    void TShipGroup::SortBySlot()
    {
    }

    void TShipGroup::Remove(TShip * aShip)
    {
       m_Ships->remove(aShip);
    }
}