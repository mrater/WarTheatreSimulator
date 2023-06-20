/**
 * @file battle.h
 * @author Maciej Sikorski
 * @brief File with classes to resolve battles between two units
 */
#pragma once
#include "units.h"
#include <iostream>
/// @brief importance of each parameters  
namespace IMPORTANCE{
    const double ATTACKER_ORG = 0.05;
    const double ATTACKER_SUPPLY = 0.4;
    const double DEFENDER_SUPPLY = 0.3;
    const double DEFENDER_ORG = 0.25;
};

/**
 * @brief Class containing information regarding battle results
 */
class BattleResult{
    /// @brief attacking unit
    const Unit &attacker;

    /// @brief defending unit
    const Unit &defender;

    /// @brief field of defender
    const Field &defenderField;

    public:
        /// @brief get field of defender
        /// @return id of defended field
        const Field &getDefenderField();

        /// @brief Calculate damage dealt to defender.
        /// Damage is equivalent to organization loss of defender
        /// @return organization loss of defender
        int calculateDamage();

        /// @brief Calculate damage dealt to attacker
        /// @return organization loss of attacker
        int calculateBacklashDamage();

        /// @brief Calculate attacker loss in equipment. 
        /// @return loss of supply level of attacker
        int calculateAttackerSupplyLoss();

        /// @brief Calculate defender loss in equipment
        /// @return loss of supply level of defender
        int calculateDefenderSupplyLoss();

        void briefBattleResult();

        BattleResult(const Unit &attackerUnit, const Unit &defenderUnit, const Field &fieldOfDefender);
};