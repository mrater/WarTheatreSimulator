#include "area.h"
#include <map>
#include <set>

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

FieldID Area::getFieldByPosition(const Position &position) const
{
    for (const auto &field : this->fields)
    {
        if (field.second.getPosition() == position) return field.first;
    }
    return -1;
}


bool Area::existsPosition(const Position &position) const
{
    for (const auto &field : this->fields)
    {
        if (field.second.getPosition() == position) return true;
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

UnitID Area::getUnitOnField(const FieldID &field) const
{
    if (!fields.count(field)) return -1;
    return getUnitOnPosition(fields.at(field).getPosition());
}

std::vector<UnitID> Area::getUnitsOfFaction(const FactionID &unitFactionID) const
{
    std::vector<UnitID> result;
    for (const auto &unit : units)
    {
        if (unit.second.getUnitFactionID() == unitFactionID)
            result.push_back(unitFactionID);
    }
    return result;
}
bool Area::isUnitOnPosition(const Position &position) const
{
    return getUnitOnPosition(position) != -1;
}
bool Area::isUnitOnField(const FieldID &field)
{
    return isUnitOnPosition(fields[field].getPosition());
}
const Unit& Area::getUnit(const UnitID &unitID) const
{
    return units.at(unitID);
}
Unit& Area::getUnit(const UnitID &unitID)
{
    return units[unitID];
}
FuelDepot& Area::getFuelDepot(const FacilityID &facilityID)
{
    return fuelMagazines[facilityID];
}
const FuelDepot &Area::getFuelDepot(const FacilityID &facilityID) const
{
    return fuelMagazines.at(facilityID);
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

void Area::fillNeighbours(const Position &fromPosition, const int &range, std::set<FieldID> &withinRange)
{
    if (range == 0) return;
    std::set<Position> currentAdj = fromPosition.getPotentialAdjacentPositions();
    for (const auto &field : this->fields)
    {
        if (currentAdj.contains(field.second.getPosition()) && existsPosition(field.second.getPosition()))
        {
            if (!withinRange.contains(field.first))
            {
                withinRange.insert(field.first);
                fillNeighbours(field.second.getPosition(), range - 1, withinRange);
            }
        }
    }    
}
std::set<FieldID> Area::getFieldsWithinRange(const Position &fromPosition, const int &range)
{
    std::set<FieldID> availableToMove;
    fillNeighbours(fromPosition, range, availableToMove);
    availableToMove.erase(getFieldByPosition(fromPosition));
    return availableToMove;
}

std::set<FieldID> Area::getFieldsSuitableToMove(const Position &position, const int &range)
{
    auto fieldHasUnit = [&](const FieldID &fieldID) {return isUnitOnField(fieldID);};
    std::set<FieldID> properFields = getFieldsWithinRange(position, range);
    std::erase_if(properFields, fieldHasUnit);
    return properFields;
}

int Area::getTotalMovementPointsOfFaction(const FactionID &factionID) const {
    std::vector<UnitID> unitsOfFaction =  getUnitsOfFaction(factionID);
    int result = 0;
    for (const UnitID &unitID : unitsOfFaction)
    {
        result += getUnit(unitID).getMovementPoints();
    }
    return result;
}

std::set<UnitID> Area::getFriendlyUnitsWithinRange(const Position &fromPosition, const int &range, const FactionID &faction)
{
    std::set<FieldID> fieldsWithingRange = getFieldsWithinRange(fromPosition, range);
    assert(!fieldsWithingRange.empty());

    std::set<UnitID> friendlyUnits;

    for (FieldID fieldID : fieldsWithingRange)
    {
        const Unit &unit = getUnit(getUnitOnField(fieldID));
        if (unit.getUnitFactionID() == faction)
        {
            friendlyUnits.insert(unit.getUnitID());
        }
    }
    return friendlyUnits;
}
