#include "mapeditor.h"

Area MapEditor::generateArea()
{
    Area resultArea(this->fields, this->units);
    return resultArea;
}

void MapEditor::addUnit(const int &q, const int &r, const UnitType unitType)
{
}

void MapEditor::addField(const int &q, const int &r, const TerrainType terrainType)
{
}
