#include "area.h"

std::vector<Unit> Area::getUnitsOfFaction(const UnitFactionID &unitFactionID) const
{
    std::vector<Unit> result;
    for (const Unit &unit : this->units)
    {
        if (unit.getUnitFactionID() == unitFactionID)
        {
            result.push_back(unit);
        }
    }
    return result;
}