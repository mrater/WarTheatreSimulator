#include "battle.h"

const Field& BattleResult::getDefenderField()
{
    return this->defenderField;
}

int BattleResult::calculateDamage()
{
    const int baseAttack = attacker.getBaseAttack(defender.getType());
    const int terrainType = defenderField.getTerrainType();
    const int resultDamage = baseAttack*Terrain::TERRAIN_BONUS[terrainType]
        - (100 - attacker.getOrganization()) * IMPORTANCE::ATTACKER_ORG
        - (100 - attacker.getSupplyLevel()) * IMPORTANCE::ATTACKER_SUPPLY
        + (100 - defender.getOrganization()) * IMPORTANCE::DEFENDER_ORG
        + (100 - defender.getSupplyLevel()) * IMPORTANCE::DEFENDER_SUPPLY;
    
    return resultDamage;
}

int BattleResult::calculateBacklashDamage()
{
    if (attacker.getType() != UnitCategory::INFANTRY) return 0;
    //TODO: calculate backlash
    return 1;
}

int BattleResult::calculateAttackerSupplyLoss()
{
    //TODO: make this more interesting
    return 25;
}

int BattleResult::calculateDefenderSupplyLoss()
{
    //TODO: make this more intereting
    return 15;
}
BattleResult::BattleResult(const Unit &attackerUnit, const Unit &defenderUnit, const Field &fieldOfDefender) : attacker(attackerUnit),
    defender(defenderUnit), defenderField(fieldOfDefender){}
