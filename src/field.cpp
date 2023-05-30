#include "field.h"

const float Field::getBonus()
{
    return Terrain::TERRAIN_BONUS[fieldType];
}

Field::Field(const FieldID &fieldID, const int &q, const int &r, const TerrainType &terrainType)
{
    this->fieldID = fieldID;
    this->position = Position(q,r);
    this->fieldType = terrainType;
}

const Position Field::getPosition() const
{
    return this->position;
}

const TerrainType Field::getTerrainType()
{
    return this->fieldType;
}

const int Position::s()
{
    return -this->q - this->r;
}

Position::Position(const int &_q, const int &_r) : q(_q), r(_r) {}

Position::Position(){
    
}

bool Position::operator==(const Position &anotherPosition) const
{
    return this->q == anotherPosition.q && this->r == anotherPosition.r;
}
void Position::operator=(const Position &anotherPosition){
    this->q = anotherPosition.q;
    this->r = anotherPosition.r;
}

// const TerrainType ForestTerrain::getTerrainType()
// {
//     return Terrain::FOREST;
// }

// const TerrainType UrbanTerrain::getTerrainType()
// {
//     return Terrain::URBAN;
// }

// const TerrainType PlainTerrain::getTerrainType()
// {
//     return Terrain::PLAIN;
// }