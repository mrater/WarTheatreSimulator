/**
 * @file units.h
 * @brief This file consists of classes of Units, i.e. Infantry, Tank, Artillery
 */
#include"field.h"
typedef int UnitType;
typedef int UnitID;
typedef int UnitFactionID;

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
class Unit{
    protected:
        /// @brief individual identifier for a unit
        UnitID ID;

        /// @brief  organization stat of a unit.
        /** It is similar to HP in strategy games. When organization is below 0, a unit dissolves.
         *  Movement, attack and defence cost some degree of organization 
        */
        int organization;

        /// @brief Level of logistic supply of a unit
        /** Level of supply is determined by fuel source nearby.
         *  It decreases during: defence, attack, movement.
         *  100 supply level is considered enough (more gives no bonuses nor punishments)
        */
        int supplyLevel;

        /// @brief basic strength of a unit (it is determined only by type of unit)
        int baseStrength;

        /// @brief position of a unit
        Position position;

        /// @brief ID of faction that owns the unit`
        UnitFactionID unitFactionId;

    public:
        /// @brief get type ID of a unit
        /// @return ID of unit type
        const virtual UnitType getType(){};
};

class Infantry : Unit {
    public:
        /// @return UnitCategory::INFANTRY
        const UnitType getType(){
            return UnitCategory::INFANTRY;
        }
};

class Tank : Unit {
    public:
        /// @return UnitCategory::TANK
        const UnitType getType(){
            return UnitCategory::TANK;
        }
};

class Artillery : Unit{
    public:
        /// @return UnitCategory::ARTILLERY
        const UnitType getType(){
            return UnitCategory::ARTILLERY;
        }
};