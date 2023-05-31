#include "theatrecontroller.h"
#include <iostream>

TheatreController::TheatreController()
{

}

bool TheatreController::attackFromDistance(const FieldID &fieldID)
{
    return false;
}

bool TheatreController::moveAndAttack(const FieldID &fieldID)
{
    return false;
}

bool TheatreController::move(const Field &Field)
{
    return false;
}

void TheatreController::generateMap(const unsigned int &size)
{

}

void TheatreController::loadMap(const Area &area)
{
    this->fields = area.fields;
    this->units = area.units;
}

void TheatreController::printUnitInfo(const UnitID &unitID)
{
    const Unit &unit = this->units[unitID];
    std::cout << "Unit #" << unitID << " of faction #" << unit.getUnitFactionID() << " ("  << UnitCategory::LITERAL[unit.getType()] << ")\n";
    std::cout << "POSITION: " << unit.getPosition().q << ", " << unit.getPosition().r << "\n";
    std::cout << "ORGANIZATION:" << unit.getOrganization() << "\n";
    std::cout << "SUPPLY LEVEL:" << unit.getSupplyLevel() << "\n====\n";
    std::cout << "TYPE OF FIELD:" << Terrain::LITERAL[getFieldWithUnit(unit.getUnitID()).getTerrainType()] << "\n";
}

void TheatreController::printUnitsInfo()
{

    for (const auto &unit : units)
    {
        printUnitInfo(unit.first);
    }
}
