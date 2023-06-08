#include "mapeditor.h"
#include <exception>
#include <iostream>

MapEditor::MapEditor()
{
    units.clear();
    fields.clear();
    // std::cout << "OK";
}

Area MapEditor::generateArea()
{
    Area resultArea(this->fields, this->units);
    resultArea.numberOfFactions = this->numberOfFactions;
    return resultArea;
}

void MapEditor::addUnit(const int &q, const int &r, const UnitType &unitType, const FactionID &unitFactionID, const UnitID &unitID)
{
    if (unitFactionID > this->numberOfFactions or unitFactionID < 1){
        throw std::invalid_argument("ID of this faction is wrong");
    }

    // std::cout << globalUnitIndex <<"<---";
    this->units[unitID] = Unit(Position(q,r), unitType, unitFactionID, unitID); 
}

void MapEditor::addUnit(const int &q, const int &r, const UnitType &unitType, const FactionID &unitFactionID)
{
    addUnit(q,r,unitType, unitFactionID, globalUnitIndex++);
}

void MapEditor::addField(const int &q, const int &r, const TerrainType &terrainType, const FieldID &fieldID)
{
    this->fields[fieldID] = Field(fieldID, q, r, terrainType);
}
void MapEditor::addField(const int &q, const int &r, const TerrainType &terrainType)
{
    addField(q,r,terrainType, globalFieldIndex++);
}
void MapEditor::setFactionsNumber(const int &numberOfFactions)
{
    this->numberOfFactions = numberOfFactions;
}
