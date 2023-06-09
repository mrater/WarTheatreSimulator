#include "infrastructure.h"

int FuelDepot::getTotalSupplyPoints() const
{
    return this->totalSupplyPoints;
}

int FuelDepot::getRange() const
{
    return FUEL_DEPOT_RANGE;
}

const Position FuelDepot::getPosition() const
{
    return this->position;
}

FactionID FuelDepot::getFactionID() const
{
    return this->factionID;
}