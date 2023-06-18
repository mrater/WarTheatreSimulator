#include "theatrecontroller.h"

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


bool TheatreController::isAttackPossible(const UnitID &unitID, const FieldID &fieldID)
{
    const Field &targetField = fields[fieldID];
    const Unit &attacker = getUnit(unitID);
    const Unit &defender = getUnit(getUnitOnField(fieldID));
    
    //field doesn't exist
    if (!fields.count(fieldID)) return false;

    //attacker doesn't exist
    if (!existsUnit(unitID)) return false;
    
    //field is empty
    if (!isUnitOnField(fieldID)) return false;

    //both units are from the same team
    if (defender.getUnitFactionID() == attacker.getUnitFactionID()) return false;

    // range not sufficient enough for an attack
    if (attacker.getAttackRange() < attacker.distanceTo(targetField.getPosition())) return false;

    //finally return true if unit itself (regardless of position, enemy etc.) can attack enemies
    return attacker.canAttack();
}
bool TheatreController::attack(const UnitID &attackerID, const FieldID &fieldID)
{
    if (!isAttackPossible(attackerID, fieldID)) return false;

    const Field &targetField = fields[fieldID];
    Unit &attacker = getUnit(attackerID);
    const UnitID defenderID = getUnitOnField(fieldID);
    Unit &defender = getUnit(defenderID);

    //calculate battle results
    BattleResult battleReults = BattleResult(attacker, defender, targetField);

    //change org of units
    defender.dealDamage(battleReults.calculateDamage());
    attacker.dealDamage(battleReults.calculateBacklashDamage());

    //change supply level of units
    defender.dealSupplyLoss(battleReults.calculateDefenderSupplyLoss());
    attacker.dealSupplyLoss(battleReults.calculateAttackerSupplyLoss());
    
    //remove units from the board if their org is below 1
    removeUnitIfDead(attackerID);
    removeUnitIfDead(defenderID);
    return true;
}
bool TheatreController::attack(const UnitID &attackerID, const Position &position)
{
    FieldID targetField = getFieldByPosition(position);
    return attack(attackerID, targetField);
}

void TheatreController::removeUnitIfDead(const UnitID &unitID)
{
    if (getUnit(unitID).getOrganization() <= 0)
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
    std::vector<FactionID> turnOrderPermutation(this->humanPlayers.size() + this->botPlayers.size());
    std::iota(turnOrderPermutation.begin(), turnOrderPermutation.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(turnOrderPermutation.begin(), turnOrderPermutation.end(), g);
 
    for (const FactionID &faction : turnOrderPermutation)
    {
        std::cout << "Faction #" << faction << " to move\n"; 
        if (isBot(faction))
        {
            throw "Bots not supported.";
            //TODO: add bot behaviour here
        } else
        {
            //handle human (interactive) decisions
            handlePlayerTurn(faction);
        }
    }
    
}

void TheatreController::handlePlayerTurn(const FactionID &faction)
{
    bool endTurn = false;
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
                if (getUnit(commandedUnit).getUnitFactionID() != faction)
                {
                    std::cout << "This unit is not from this faction\n";
                } else 
                if (!move(commandedUnit, targetPosition))
                {
                    std::cout << "This field is occupied, does not exist or not within range of this unit\n";
                } else std::cout << "Done.\n";
                break;
            }
            //attack
            case 'x':{
                UnitID commandedUnit;
                if (getUnit(commandedUnit).getUnitFactionID() != faction){
                    std::cout << "Unit not from your faction\n";
                }
                Position targetPosition;
                if (!attack(commandedUnit, targetPosition)){
                    std::cout << "This attack is not possible.\n";
                } else std::cout << "Done.\n";
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
                if (getUnit(unitID).getUnitFactionID() != faction){
                    std::cout << "Unit not from your faction\n";
                } else 
                if (!skipMovement(unitID))
                {
                    std::cout << "Unit doesn't exists\n"; 
                } else std::cout << "Done.\n";

                break;
            }
            case 'e':{
            }

            case 'h':
                std::cout << "h - print this help message\n";
                std::cout << "m UNIT_ID Q R - move unit to position (Q,R)\n";
                std::cout << "p - print information about all units\n";
                std::cout << "x UNIT_ID Q R - order unit to attack this position\n";
                std::cout << "s UNIT_ID - skip every other action of this unit\n";
                std::cout << "e - skip all remaining unit actions and proceed to next turn\n";
                break;
            default:
                std::cout << "Command unrecognized. Enter h for help\n";
                break;
            
        }
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
    std::cout << "ORGANIZATION:" << unit.getOrganization() << "\n";
    std::cout << "SUPPLY LEVEL:" << unit.getSupplyLevel() << "\n====\n";
    std::cout << "TYPE OF FIELD:" << Terrain::LITERAL[getFieldWithUnit(unit.getUnitID()).getTerrainType()] << "\n";
    std::cout << "REMAINING MOVEMENT POINTS: " << unit.getMovementPoints() << "/" << unit.getBaseMovementPoints() << "\n";
}

void TheatreController::printUnitsInfo()
{
    for (const auto &unit : units)
    {
        printUnitInfo(unit.first);
    }
}

int TheatreController::countFactions() const
{
    return this->botPlayers.size() + this->humanPlayers.size();
}
void TheatreController::startInteractive()
{
    int rounds = 0;
    while (rounds++ <= 10)
    {
        std::cout << "Round #" << rounds << "\n";
        startNextRound();
    }
}