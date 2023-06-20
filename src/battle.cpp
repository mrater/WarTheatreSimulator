#include "battle.h"

const Field& BattleResult::getDefenderField() const
{
    return this->defenderField;
}

int BattleResult::calculateDamage() const
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

int BattleResult::calculateBacklashDamage() const
{
    if (attacker.getType() != UnitCategory::INFANTRY) return 0;
    //TODO: calculate backlash
    return 25;
}

int BattleResult::calculateAttackerSupplyLoss() const
{
    return 25;
}

int BattleResult::calculateDefenderSupplyLoss() const
{
    return 15;
}
void BattleResult::briefBattleResult() const
{
    std::cout << "Result of this attack:\n";
    std::cout << "Attacker: Unit #" << attacker.getUnitID() << "(" << attacker.getUnitFactionID() << "), " << UnitCategory::LITERAL[attacker.getType()] << ":\n";
    if (attacker.getOrganization() - calculateBacklashDamage() <= 0)
    {
        std::cout << "ATTACKER UNIT DESTROYED.\n";
    } else {
        std::cout << "ORG: " << attacker.getOrganization() - calculateBacklashDamage() << "/ 100 (-" << calculateBacklashDamage() << ")\n";
        std::cout << "SUPPLY : " << attacker.getSupplyLevel() - calculateAttackerSupplyLoss() << " / 100 (-" << calculateAttackerSupplyLoss() << ")\n";
    }
    std::cout << "Defender: Unit #" << defender.getUnitID() << "(" << defender.getUnitFactionID() << "), " << UnitCategory::LITERAL[defender.getType()] << ":\n";
    if (defender.getOrganization() - calculateDamage() <= 0)
    {
        std::cout << "DEFENDER UNIT DESTROYED.\n";
    } else {
        std::cout << "ORG: " << defender.getOrganization() - calculateDamage() << "/ 100 (-" << calculateDamage() << ")\n";
        std::cout << "SUPPLY : " << defender.getSupplyLevel() - calculateDefenderSupplyLoss() << " / 100 (-" << calculateDefenderSupplyLoss() << ")\n";
    }
}

BattleResult::BattleResult(const Unit &attackerUnit, const Unit &defenderUnit, const Field &fieldOfDefender) : attacker(attackerUnit),
                                                                                                               defender(defenderUnit), defenderField(fieldOfDefender) {}
