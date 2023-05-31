#include "area.h"
#include "map"

Area::Area()
{
    fields.clear();
    units.clear();
}

Area::Area(std::map<FieldID, Field> newFields, std::map<UnitID, Unit> newUnits)
{
    this->fields = newFields;
    this->units = newUnits;
}

bool Area::isRealPosition(const Position &position) const
{
    for (const auto &field : fields)
    {
        if (field.second.getPosition() == position)
            return true;
    }
    return false;
}

UnitID Area::getUnitOnPosition(const Position &position) const
{
    for (const auto &unit : units)
    {
        if (unit.second.getPosition() == position)
            return unit.first;
    }
    return -1;
}

std::vector<UnitID> Area::getUnitsOfFaction(const UnitFactionID &unitFactionID)
{
    std::vector<UnitID> result;
    for (const auto &unit : units)
    {
        if (unit.second.getUnitFactionID() == unitFactionID)
            result.push_back(unitFactionID);
    }
    return result;
}

Unit Area::getUnit(const UnitID &unitID)
{
    return units[unitID];
}
const Field &Area::getFieldWithUnit(const UnitID &unitID) const
{
    const Position &unitPosition = units.at(unitID).getPosition();
    for (const auto &field : fields)
    {
        if (field.second.getPosition() == unitPosition) return field.second;
    }
    return fields.end()->second;
}
