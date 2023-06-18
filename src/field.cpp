#include "field.h"
#include <set>
#include <iostream>

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

Field::Field(){}

const Position Field::getPosition() const
{
    return this->position;
}

TerrainType Field::getTerrainType() const
{
    return this->fieldType;
}

int Position::distanceTo(const Position &anotherPosition) const
{
    std::cerr << "Warning: distanceTo() returns constant 1\n";
    return 1;
}

int Position::s()
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

bool Position::operator<(const Position &anotherPosition) const
{
    //this could be anything
    return this->q < anotherPosition.q;
}

std::set<Position> Position::getPotentialAdjacentPositions() const
{
    std::set<Position> result;
    result.insert(Position(q - 1,r));
    result.insert(Position(q + 1, r));
    result.insert(Position(q, r - 1));
    result.insert(Position(q, r + 1));
    result.insert(Position(q + 1, r - 1));
    result.insert(Position(q - 1, r + 1));
    return result;
}