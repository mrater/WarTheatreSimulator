#include "theatrecontroller.h"
#include "utilities.h"

void TheatreController::resetAllUnitsMovementPoints()
{
    for (auto &unit : units)
    {
        unit.second.resetMovement();
    }
}

TheatreController::TheatreController()
{

}


bool TheatreController::isAttackPossible(const UnitID &unitID, const Position &position) const
{
    // std::cerr << fields.at(getFieldByPosition(position)).getFieldID() << "<---";
    // Field targetField = fields.at(getFieldByPosition(position));

    //field doesn't exist
    if (!existsPosition(position)) return false;

    //attacker doesn't exist
    if (!existsUnit(unitID)) return false;
    
    //field is empty
    if (!isUnitOnField(getFieldByPosition(position))) return false;

    const Unit &attacker = getUnitConstantReference(unitID);
    const Unit &defender = getUnitConstantReference(getUnitOnPosition(position));
    //both units are from the same team
    if (defender.getUnitFactionID() == attacker.getUnitFactionID()) return false;

    // range not sufficient enough for an attack
    if (attacker.getAttackRange() < attacker.distanceTo(position)) return false;

    //finally return true if unit itself (regardless of position, enemy etc.) can attack enemies
    return attacker.canAttack();
}

///@brief get battle results and apply them to the battlefield
///@warning need assumption that attack is possible. Might break otherwise
BattleResult TheatreController::attack(const UnitID &attackerID, const FieldID &fieldID)
{
    const Field &targetField = fields.at(fieldID);
    Unit &attacker = getUnit(attackerID);
    const UnitID defenderID = getUnitOnField(fieldID);
    Unit &defender = getUnit(defenderID);

    //calculate battle results
    BattleResult battleResult = BattleResult(attacker, defender, targetField);

    //change org of units
    defender.dealDamage(battleResult.calculateDamage());
    attacker.dealDamage(battleResult.calculateBacklashDamage());

    //change supply level of units
    defender.dealSupplyLoss(battleResult.calculateDefenderSupplyLoss());
    attacker.dealSupplyLoss(battleResult.calculateAttackerSupplyLoss());
    
    //remove units from the board if their org is below 1
    removeUnitIfDead(attackerID);
    removeUnitIfDead(defenderID);

    attacker.setMovementPoints(0);
    return battleResult;
}
BattleResult TheatreController::attack(const UnitID &attackerID, const Position &position)
{
    FieldID targetField = getFieldByPosition(position);
    return attack(attackerID, targetField);
}

void TheatreController::removeUnitIfDead(const UnitID &unitID)
{
    if (getUnitConstantReference(unitID).getOrganization() <= 0)
    {
        //it is dead
        units.erase(unitID);
    }
}

bool TheatreController::move(const UnitID &unitID, const Position &position)
{
    // check if unit with this id exists
    if (!existsUnit(unitID)) return false;
    int distanceToPosition = units[unitID].getPosition().distanceTo(position);
    if (!isRealPosition(position) or units[unitID].getMovementPoints() < distanceToPosition) return false;
    if (isUnitOnPosition(position)) return false;

    units[unitID].setPosition(position);
    units[unitID].decreaseMovementPoints(distanceToPosition);
    return true;
}

bool TheatreController::isHuman(const FactionID &faction) const
{
    return std::count(this->humanPlayers.begin(), this->humanPlayers.end(), faction) != 0;
}
bool TheatreController::isBot(const FactionID &faction) const
{
    return std::count(this->botPlayers.begin(), this->botPlayers.end(), faction) != 0;
}


void TheatreController::startNextRound()
{
    //reset all movement points of all units.
    resetAllUnitsMovementPoints();

    //determine order of turns by the following random permutation
    std::vector<FactionID> turnOrderPermutation = generateRandomPermutation(botPlayers.size() + humanPlayers.size());

    resupplyAllUnits();
    for (const FactionID &faction : turnOrderPermutation)
    {
        std::cout << "Faction #" << faction << " to move\n"; 
        if (isBot(faction))
        {
            throw std::invalid_argument("Bots not supported.");
        } else
        {
            //handle human (interactive) decisions
            handlePlayerTurn(faction);
        }
    }
    
}

void TheatreController::handlePlayerTurn(const FactionID &faction)
{
    resetAllUnitsMovementPoints();
    while (true)
    {
        std::cout << "Enter command:\n~";
        char command;
        std::cin >> command;        
        switch(command)
        {
            //move
            case 'm':
            {   
                UnitID commandedUnit;
                Position targetPosition;
                std::cin >> commandedUnit >> targetPosition.q >> targetPosition.r;
                if (getUnitConstantReference(commandedUnit).getUnitFactionID() != faction)
                {
                    std::cout << "This unit is not from this faction\n";
                } else 
                if (!move(commandedUnit, targetPosition))
                {
                    std::cout << "This field is occupied, does not exist, not within range or unit out of needed movement points\n";
                } else 
                {
                    std::cout << "Unit #" << commandedUnit << " is now on (" << targetPosition.q << ", " << targetPosition.r << ")\n";
                }
                break;
            }
            //attack
            case 'x':{
                UnitID commandedUnit;
                Position targetPosition;

                std::cin >> commandedUnit >> targetPosition.q >> targetPosition.r;
                if (getUnitConstantReference(commandedUnit).getUnitFactionID() != faction){
                    std::cout << "Unit not from your faction\n";
                } else {
                    // const auto &targetFieldID = getFieldByPosition(targetPosition);
                    // std::cerr << targetFieldID << "to be attacked\n";
                    if (!isAttackPossible(commandedUnit, targetPosition)) {
                        std::cout << "This attack is not possible.\n";
                    } else {
                        BattleResult battle = attack(commandedUnit, targetPosition);
                        battle.briefBattleResult();
                    }
                }
                break;
            }
            
            //print info about all units
            case 'p':{
                printUnitsInfo();
                break;
            }

            case 's':{
                UnitID unitID;
                std::cin >> unitID;
                if (!existsUnit(unitID)){
                    std::cout << "Unit doesn't exists.\n";
                }
                else if (getUnitConstantReference(unitID).getUnitFactionID() != faction){
                    std::cout << "Unit not from your faction\n";
                } 
                else if (!skipMovement(unitID))
                {
                    std::cout << "Unit doesn't exists\n"; 
                } else std::cout << "Done.\n";

                break;
            }
            case 'e':{
                std::cout << "All remaining movement skipped.\n";
                skipAllMovementOfFaction(faction);
                break;
            }
            case 'w':{
                std::string unitsFilename, fieldsFilename;
                std::cin >> fieldsFilename >> unitsFilename;
                exportAllToCSV(fieldsFilename + ".csv", unitsFilename + ".csv");
                break;
            }


            case 'h':
                std::cout << "h - print this help message\n";
                std::cout << "m UNIT_ID Q R - move unit to position (Q,R)\n";
                std::cout << "p - print information about all units\n";
                std::cout << "x UNIT_ID Q R - order unit to attack this position\n";
                std::cout << "s UNIT_ID - skip every other action of this unit\n";
                std::cout << "e - skip all remaining unit actions and proceed to next turn\n";
                std::cout << "w FIELDS UNITS - export csv with fields info to FIELDS.csv and units info to UNITS.csv";
                break;
            default:
                std::cout << "Command unrecognized. Enter h for help\n";
                break;
            
        }
        // std::cerr << "total movpo" << getTotalMovementPointsOfFaction(faction);
        if (getTotalMovementPointsOfFaction(faction) == 0) return;
        if (countFactions() < 2) return;
    }
}

void TheatreController::loadMap(const Area &area, const std::vector<FactionID> &humanFactions, const std::vector<FactionID> &botFactions)
{
    this->fields = area.fields;
    this->units = area.units;
    this->humanPlayers = humanFactions;
    this->botPlayers = botFactions;
}


void TheatreController::printUnitInfo(const UnitID &unitID)
{
    const Unit &unit = this->units[unitID];
    std::cout << "Unit #" << unitID << " of faction #" << unit.getUnitFactionID() << " ("  << UnitCategory::LITERAL[unit.getType()] << ")\n";
    std::cout << "POSITION: " << unit.getPosition().q << ", " << unit.getPosition().r << "\n";
    std::cout << "ORG:" << unit.getOrganization() << ", " << "SUPPLY LVL:" << unit.getSupplyLevel() << "\n";
    std::cout << "MOVEMENT POINTS: " << unit.getMovementPoints() << "/" << unit.getBaseMovementPoints() << "\n";
    std::cout << "TERRAIN:" << Terrain::LITERAL[getFieldWithUnit(unit.getUnitID()).getTerrainType()] << "\n";
    std::cout << "==================\n";
}

void TheatreController::printUnitsInfo()
{
    for (const auto &unit : units)
    {
        printUnitInfo(unit.first);
    }
}

void TheatreController::startInteractive()
{
    int rounds = 0;
    while (countFactions() > 1)
    {
        std::cout << "Round #" << ++rounds << "\n";
        startNextRound();

        // std::cerr << countFactions() << "<-----\n";
    }
    std::cout << "Simulation finished. ";
    if (countFactions() == 0) std::cout << "No factions persisted\n";
    else {
        std::cout << "Remaining factions: ";
        const std::set<FactionID> remainingFactions = getAllFactions();
        for (auto const &factionID : remainingFactions)
        {
            std::cout << factionID << " ";
        }
        std::cout << "\n";
    }
}
size_t TheatreController::countFactions() const
{
    std::set<FactionID> existingFactions;
    for(const auto &unit : units)
    {
        existingFactions.insert(unit.second.getUnitFactionID());
    }
    return existingFactions.size();
}
bool TheatreController::existsUnit(const UnitID &unitID) const {
    return units.count(unitID) > 0;
}

void TheatreController::resupplyAllUnits()
{
    for (auto &unit : units)
    {
        unit.second.gainSupply(15);
    }
}