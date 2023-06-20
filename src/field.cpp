#include "field.h"
#include <set>
#include <iostream>
#include <assert.h>

double Field::getBonus() const
{
    return Terrain::TERRAIN_BONUS[fieldType];
}

Field::Field(const FieldID &_fieldID, const int &q, const int &r, const TerrainType &terrainType)
{
    this->fieldID = _fieldID;
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
    return 1;
    int l = abs(this->q - anotherPosition.q) 
        + abs(this->q + this->r - anotherPosition.q - anotherPosition.r)
        + abs(this->r - anotherPosition.r);
    std::cerr << "Warning: distanceTo() returns " << l << "\n";
    assert((l & 1) == 0);
    return l / 2;
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