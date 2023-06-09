#pragma once
#include "field.h"
#include "units.h"

typedef int FacilityID;

constexpr int FUEL_DEPOT_RANGE = 4;

/// @brief Fuel magazine class
/// This facility distributes supply every turn among friendly units within range
class FuelDepot{ 
    private:
    FacilityID id;
    FactionID factionID;
    Position position;
    
    //value of supply points distributed among allies
    int totalSupplyPoints;


    public:
    int getTotalSupplyPoints() const;
    FactionID getFactionID() const;
    int getRange() const;
    const Position getPosition() const;
};