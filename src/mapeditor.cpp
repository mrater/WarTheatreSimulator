#include "mapeditor.h"

Area MapEditor::generateArea()
{
    Area resultArea(this->fields, this->units);
    return resultArea;
}

void MapEditor::addUnit(const int &q, const int &r, const UnitType &unitType)
{
    this->units[globalUnitIndex++] = Unit(Position(q,r), unitType, ) 
}

void MapEditor::addField(const int &q, const int &r, const TerrainType &terrainType)
{
    this->fields[globalFieldIndex++] = Field(globalFieldIndex, q, r, terrainType);
}
