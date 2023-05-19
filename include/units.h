/**
 * @file units.h
 * @brief This file consists of 
 */
typedef int UnitType;
namespace UnitCategory{
    constexpr UnitType NONE = 0;
    constexpr UnitType INFANTRY = 1;
    constexpr UnitType TANK = 2;
    constexpr UnitType ARTILLERY = 3;
};

class Unit{
    int organization;
    int supplyLevel;
    int baseStrength;
    const virtual UnitType getType(){};
};

class Infantry : Unit {
    const UnitType getType(){
        return UnitCategory::INFANTRY;
    }
};

class Tank : Unit {
    const UnitType getType(){
        return UnitCategory::TANK;
    }
};

class Artillery : Unit{
    const UnitType getType(){
        return UnitCategory::ARTILLERY;
    }
};