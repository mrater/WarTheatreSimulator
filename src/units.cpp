#include "units.h"
#include <iostream>
Unit::Unit(const Position &newPosition, const UnitType &unitType, const UnitFactionID &unitFactionID, const UnitID &unitID)
{
    this->ID = unitID;
    this->position = Position(newPosition.q, newPosition.r);
    this->unitType = unitType;
    this->unitFactionId = unitFactionID;
    this->movementPoints = baseMovementPoints::MATRIX[unitType];
    this->organization = base::ORGANIZATION;
    this->supplyLevel = base::SUPPLY_LEVEL;
}

Unit::Unit()
{
    // std::cerr << "Why am I even here?\n";
}

const UnitType Unit::getType() const
{
    return this->unitType;
}

const Position Unit::getPosition() const
{
    return this->position;
}

const int Unit::getBaseAttack(const UnitType &enemyUnitType)
{
    return baseAttack::DAMAGE_MATRIX[this->getType()][enemyUnitType];
}

const UnitFactionID Unit::getUnitFactionID() const
{
    return this->unitFactionId;
}

const int Unit::getSupplyLevel() const
{
    return this->supplyLevel;
}

const int Unit::getOrganization() const
{
    return this->organization;
}

const UnitID Unit::getUnitID() const
{
    return ID;
}
