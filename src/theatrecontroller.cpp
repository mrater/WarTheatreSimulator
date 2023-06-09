#include "theatrecontroller.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <random>

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

bool TheatreController::attackFromDistance(const FieldID &fieldID)
{
    return false;
}

bool TheatreController::moveAndAttack(const FieldID &fieldID)
{
    return false;
}

bool TheatreController::move(const UnitID &unitID, const Position &position)
{
    int distanceToPosition = units[unitID].getPosition().distanceTo(position);
    if (!isRealPosition(position) or units[unitID].getMovementPoints() < distanceToPosition) return false;
    units[unitID].setPosition(position);
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
 
    for (FactionID faction = 1; faction <= countFactions(); faction++)
    {
        if (isBot(faction))
        {
            throw "Bots not supported.";
            //TODO: add bot behaviour here
        } else
        {
            //handle human (interactive) decisions
            handlePlayerTurn();
        }
    }
    
}

void TheatreController::handlePlayerTurn()
{
    bool endTurn = false;
    while (true)
    {
        std::cout << "Enter command~\n";
        char command;
        std::cin >> command;        
        switch(command)
        {
            case 'm':
            {   
                UnitID commandedUnit;
                Position targetPosition;
                std::cin >> commandedUnit >> targetPosition.q >> targetPosition.r;
                if (!move(commandedUnit, targetPosition))
                {
                        std::cout << "This field is occupied, does not exist or not within range of this unit\n";
                } else endTurn = true;
                break;
            }
            case 'x':
                // attackFromDistance()

                break;
                
            case 'h':
                std::cout << "h - print this help message\n";
                std::cout << "m UNIT_ID Q R - move unit to position (Q,R)\n";
                std::cout << "p - print information about all units\n";
                std::cout << "x UNIT_ID Q R - order unit to attack this field\n";
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
}

void TheatreController::printUnitsInfo()
{
    for (const auto &unit : units)
    {
        printUnitInfo(unit.first);
    }
}

const int TheatreController::countFactions() const
{
    return this->botPlayers.size() + this->humanPlayers.size();
}
