#include "infrastructure.h"

int FuelDepot::getSupplyRenewal() const
{
    return this->supplyRenewal;
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