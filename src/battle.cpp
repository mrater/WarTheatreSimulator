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
    return 0;
}

int BattleResult::calculateAttackerSupplyLoss()
{
    return 0;
}

int BattleResult::calculateDefenderSupplyLoss()
{
    return 0;
}

void BattleResult::loadBattle(const Unit &attackerUnit, const Unit &defenderUnit, const Field &fieldOfDefender)
{
    this->attacker = attackerUnit;
    this->defender = defenderUnit;
    this->defenderField = fieldOfDefender;
}
