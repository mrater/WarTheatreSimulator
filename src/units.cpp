#include "units.h"
#include <iostream>
Unit::Unit(const Position &newPosition, const UnitType &unitType, const FactionID &unitFactionID, const UnitID &unitID)
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

const int Unit::getBaseAttack(const UnitType &enemyUnitType) const
{
    return baseAttack::DAMAGE_MATRIX[this->getType()][enemyUnitType];
}

const FactionID Unit::getUnitFactionID() const
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

void Unit::resetMovement()
{
    this->movementPoints = baseMovementPoints::MATRIX[this->getType()];
}

const int Unit::getMovementPoints() const
{
    return movementPoints;
}

void Unit::setPosition(const Position &position)
{
    this->position = position;
}

void Unit::dealDamage(const int &receivedDamage)
{
    this->organization -= receivedDamage;
}

void Unit::dealSupplyLoss(const int &supplyLoss)
{
    this->supplyLevel = std::max(supplyLevel - supplyLevel, 0);
}

void Unit::decreaseMovementPoints(const int &loss){
    this->movementPoints -= loss;
}

const int Unit::getAttackRange() const
{
    return attackRange::MATRIX[this->getType()];
}
const int Unit::distanceTo(const Unit &anotherUnit) const
{
    return position.distanceTo(anotherUnit.getPosition());
}

const int Unit::distanceTo(const Position &position) const
{
    return this->position.distanceTo(position);
}

const bool Unit::canAttack() const
{
    return movementPoints >= 1 && getSupplyLevel() >= BASIC_ATTACK_SUPPLY_REQUIREMENT;
}
