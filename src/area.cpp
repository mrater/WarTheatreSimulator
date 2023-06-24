#include "area.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>

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
    // assert(0);
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

std::set<UnitID> Area::getUnitsOfFaction(const FactionID &unitFactionID) const
{
    // std::cerr << "faction=" << unitFactionID << "\n";
    std::set<UnitID> result;
    for (const auto &unit : units)
    {
        if (unit.second.getUnitFactionID() == unitFactionID)
            {
                result.insert(unit.second.getUnitID());
            }
    }
    return result;
}
bool Area::isUnitOnPosition(const Position &position) const
{
    return getUnitOnPosition(position) != -1;
}
bool Area::isUnitOnField(const FieldID &field) const
{
    return isUnitOnPosition(fields.at(field).getPosition());
}
const Unit& Area::getUnitConstantReference(const UnitID &unitID) const
{
    return units.at(unitID);
}
Unit& Area::getUnit(const UnitID &unitID)
{
    return units[unitID];
}
// FuelDepot& Area::getFuelDepot(const FacilityID &facilityID)
// {
//     return fuelMagazines[facilityID];
// }
// const FuelDepot &Area::getFuelDepot(const FacilityID &facilityID) const
// {
//     return fuelMagazines.at(facilityID);
// }
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
    std::set<UnitID> unitsOfFaction =  getUnitsOfFaction(factionID);
    int result = 0;
    for (const UnitID &unitID : unitsOfFaction)
    {
        // std::cerr << "unit of faction=" << unitID <<" \n";
        result += getUnitConstantReference(unitID).getMovementPoints();
    }
    return result;
}


bool Area::existsUnit(const UnitID &unitID) const {
    return units.count(unitID) > 0;
}
bool Area::existsFaction(const FactionID &faction) const
{
    return !getUnitsOfFaction(faction).empty();
}
bool Area::skipMovement(const UnitID &unitID)
{
    if (!existsUnit(unitID)) return false;
    getUnit(unitID).setMovementPoints(0);
    return true;
}

bool Area::skipAllMovementOfFaction(const FactionID &faction)
{
    const auto unitsOfFaction = getUnitsOfFaction(faction);
    if (unitsOfFaction.empty()) return false;
    for (const auto unit : unitsOfFaction)
    {
        getUnit(unit).setMovementPoints(0);
    }

    return true;
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

std::set<FactionID> Area::getAllFactions()
{
    std::set<FactionID> result;
    for (const auto &unit : units)
    {
        result.insert(unit.second.getUnitFactionID());
    }
    return result;
}
void Area::exportUnitsToCSV(const std::string &filename) const
{
    std::ofstream file;
    file.open(filename);
    file << "unitID, factionID, organisation, supply, movementPoints, type, q, r\n";
    for (const auto &unitPair : units)
    {
        const auto &unit =  unitPair.second;
        file << unit.getUnitID() << ", " << unit.getUnitFactionID() << ", " << unit.getOrganization() << ", " << unit.getSupplyLevel() << ", " << 
            unit.getMovementPoints() << ", " << UnitCategory::LITERAL[unit.getType()] << ", " << unit.getPosition().q << ", " << unit.getPosition().r << "\n";
    }
    file.close();    
}
void Area::exportFieldsToCSV(const std::string &filename) const
{
    std::ofstream file;
    file.open(filename);
    file << "fieldID, fieldType, q, r\n";
    for (const auto &fieldPair : fields)
    {
        const auto &field = fieldPair.second;
        file << field.getFieldID() << ", " << Terrain::LITERAL[field.getTerrainType()] << ", " << field.getPosition().q << ", " << field.getPosition().r << "\n";
    }
    file.close();
}
void Area::exportAllToCSV(const std::string &fieldsFilename, const std::string &unitsFilename)
{
    exportFieldsToCSV(fieldsFilename);
    exportUnitsToCSV(unitsFilename);
}