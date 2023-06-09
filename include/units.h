/**
 * @file units.h
 * @brief This file consists of classes of Units, i.e. Infantry, Tank, Artillery
 * \{
 */
#pragma once
#include"field.h"


typedef int UnitType;
typedef int UnitID;
typedef int FactionID;

/// @brief namespace with unit types category IDs
namespace UnitCategory{
    constexpr UnitType NONE = 0;
    constexpr UnitType INFANTRY = 1;
    constexpr UnitType ARTILLERY = 2;
    constexpr UnitType TANK = 3;
    const char* const LITERAL[] = {"NONE", "INFANTRY", "ARTILLERY", "TANK"};
    // const int a[] = {1,2};
};


/// @brief namespace with constants of X_Y attack.
/// X_Y means that X attacks Y with this basic damage
namespace baseAttack{
    /// @brief base attack when type of units are wrong
    constexpr int ERROR_PAIR = -1;

    constexpr int INFRANTRY_TO_INFANTRY = 60;
    constexpr int INFANTRY_TO_ARTILLERY = 100;
    
    constexpr int ARTILLERY_TO_ARTILLERY = 100;
    constexpr int ARTILLERY_TO_INFANTRY = 100;

    /// @brief [X][Y] - how X attacks Y
    constexpr int DAMAGE_MATRIX[][4] = {
        //type NONE
        {ERROR_PAIR, ERROR_PAIR, ERROR_PAIR, ERROR_PAIR},
        
        //type INFANTRY
        {ERROR_PAIR, INFRANTRY_TO_INFANTRY, INFANTRY_TO_ARTILLERY, 0},

        //type ARTILLERY
        {ERROR_PAIR, ARTILLERY_TO_INFANTRY, ARTILLERY_TO_ARTILLERY, 0},

        //type TANK
        {0,0,0,0}
    };
}
namespace baseMovementPoints{
    constexpr int INFANTRY = 2;
    constexpr int ARTILLERY = 1;
    constexpr int TANK = 2;
    constexpr int MATRIX[] = {0,INFANTRY,ARTILLERY,TANK};
}

namespace base{
    constexpr int ORGANIZATION = 100;
    constexpr int SUPPLY_LEVEL = 100;
}

//unit can attack iff has supply lvl >= this value
constexpr int BASIC_ATTACK_SUPPLY_REQUIREMENT = 25;

/// @brief contains info about attack range of every unit type 
namespace attackRange{
    constexpr int INFANTRY = 1;
    constexpr int ARTILLERY = 2;
    constexpr int TANK = 1;

    constexpr int MATRIX[] = {0, INFANTRY, ARTILLERY, TANK};
}

/**
 * @brief Basic class for all unit types
 * 
 */
class Unit{
    protected:
        /// @brief individual identifier for a unit
        UnitID ID;

        /// @brief type of this unit
        UnitType unitType;

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
        // int baseStrength; this actually shouldn't exist - it's a constant property 

        /// @brief position of a unit
        Position position;

        /// @brief ID of faction that owns the unit`
        FactionID unitFactionId = 0;

        /// @brief range of an attack of a unit
        /// unitRange = X means that every enemy unit in (manhattan distance) X of our unit can be attacked
        // int unitRange; (but actually it shouldn't exist because it's a constant property depending on type)

        /// \brief how far this unit can move in this turn
        int movementPoints;

    public:
        Unit(const Position &newPosition, const UnitType &unitType, const FactionID &unitFactionID, const UnitID &unitID);
        Unit();
        /// @brief get type ID of a unit
        /// @return ID of unit type
        UnitType getType() const;

        /// @return Position of unit
        Position getPosition() const;

        /// @brief  Get base attack, a value that might be unique for every pair (UNIT_TYPE, DEFENDER_UNIT_TYPE)
        /// @param unitType type of enemy unit that we deal with
        /// @return base attack of this unit type
        virtual int getBaseAttack(const UnitType &enemyUnitType) const;

        /// @brief get ID of unit faction
        /// @return ID of a faction of unit
        FactionID getUnitFactionID() const; 

        /// @brief change position of a unit
        // void changeUnitPosition(const Position &position);

        /// @brief get level of supply of unit
        int getSupplyLevel() const;

        /// @brief get organisation
        int getOrganization() const;

        UnitID getUnitID() const;


        int getMovementPoints() const;

        /// \return initial movement points of this unit's type 
        int getBaseMovementPoints() const;

        void decreaseMovementPoints(const int &loss);

        int getAttackRange() const;
        int distanceTo(const Unit &anotherUnit) const;
        int distanceTo(const Position &position) const;

        //true if movement points and supply level are sufficient for an attack
        bool canAttack() const;

        /// @brief increase supply level of unit but not exceed 100
        /// @param supplyGain amount of supply level to add
        /// @return supply points really needed (i.e. 100 - currentSupply)
        int gainSupply(const int &supplyGain);

        void resetMovement();
        void setPosition(const Position &position);

        void dealDamage(const int &receivedDamage);
        void dealSupplyLoss(const int &supplyLoss);
};

// class Infantry : public Unit {
//     public:
//         /// @return UnitCategory::INFANTRY
//         const UnitType getType();

//         /// @brief get Base attack of infantry
//         /// @param unitType type of enemy unit
//         /// @return base attack for infantry when dealing with certain enemy
//         const int getBaseAttack(const UnitID &unitType);
// };

// class Tank : public Unit {
//     public:
//         /// @return UnitCategory::TANK
//         const UnitType getType(){
//             return UnitCategory::TANK;
//         }

//         /// @brief get Base attack of tank
//         /// @param unitType type of enemy unit
//         /// @return base attack for tank when dealing with certain enemy
//         const int getBaseAttack(const UnitID &unitType);
        
// };

// class Artillery : public Unit{
//     public:
//         /// @return UnitCategory::ARTILLERY
//         const UnitType getType(){
//             return UnitCategory::ARTILLERY;
//         }
        
//         /// @brief get Base attack of artillery
//         /// @param unitType type of enemy unit
//         /// @return base attack for artillery when dealing with certain enemy
//         const int getBaseAttack(const UnitID &unitType);
// };