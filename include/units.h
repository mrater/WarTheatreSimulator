/**
 * @file units.h
 * @brief This file consists of classes of Units, i.e. Infantry, Tank, Artillery
 */
#include "field.h"
typedef int UnitType;

/// @brief namespace with unit types category IDs
namespace UnitCategory{
    constexpr UnitType NONE = 0;
    constexpr UnitType INFANTRY = 1;
    constexpr UnitType TANK = 2;
    constexpr UnitType ARTILLERY = 3;
};


/**
 * @brief Basic class for all unit types
 * 
 */
class Unit : Field{
    int organization;
    int supplyLevel;
    int baseStrength;

    public:
        /// @brief get type ID of a unit
        /// @return ID of unit type
        const virtual UnitType getType(){};
};

class Infantry : Unit {
    public:
        const UnitType getType(){
            return UnitCategory::INFANTRY;
        }
};

class Tank : Unit {
    public:
        const UnitType getType(){
            return UnitCategory::TANK;
        }
};

class Artillery : Unit{
    public:
        const UnitType getType(){
            return UnitCategory::ARTILLERY;
        }
};