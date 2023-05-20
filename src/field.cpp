#include "field.h"

Position Field::getPosition()
{
    return this->position;
}

const int Position::s()
{
    return -this->q - this->r;
}

Position::Position(const int &_q, const int &_r) : q(_q), r(_r) {};

const TerrainType ForestTerrain::getTerrainType()
{
    return Terrain::FOREST;
}

const TerrainType UrbanTerrain::getTerrainType()
{
    return Terrain::URBAN;
}

const TerrainType PlainTerrain::getTerrainType()
{
    return Terrain::PLAIN;
}