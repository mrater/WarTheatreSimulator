/**
 * @file battle.h
 * @author Maciej Sikorski
 * @brief File with classes to resolve battles between two units
 */

#include "units.h"
#include "field.h"

/**
 * @brief Class containing information regarding battle results
 */
class BattleResult{
    /// @brief ID of attacking unit
    UnitID attackerID;

    /// @brief ID of defending unit
    UnitID defenderID;

    public:
        /// @brief get field of defender
        /// @return id of defended field
        const FieldID getDefenderField();

        /// @brief Calculate damage dealt to defender.
        /// Damage is equivalent to organization loss of defender
        /// @return organization loss of defender
        int calculateDamage();

        /// @brief Calculate damage dealt to attacker
        /// @return organization loss of attacker
        int calculateBackslashDamage();


        /// @brief Calculate attacker loss in equipment. 
        /// @return loss of supply level of attacker
        int calculateAttackerSupplyLoss();

        /// @brief Calculate defender loss in equipment
        /// @return loss of supply level of defender
        int calculateDefenderSupplyLoss();

};