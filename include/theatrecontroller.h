#pragma once
#include "area.h"
#include "battle.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <random>

class TheatreController : public Area {
    private:
        bool simulationStarted = false;

        //factions controlled by humans
        std::vector<FactionID> humanPlayers;

        //factions controlled by bots
        std::vector<FactionID> botPlayers;
        
        void resetAllUnitsMovementPoints();
    protected:
    public:
        TheatreController();
        bool isAttackPossible(const UnitID &unitID, const FieldID &fieldID);
        bool attack(const UnitID &unitID, const FieldID &fieldID);
        bool attack(const UnitID &attackerID, const Position &position);
        void removeUnitIfDead(const UnitID &unitID);
        // bool attackFromDistance(const FieldID &fieldID);

        /// @brief move unit to this field. Attack if something is there. 
        /// Function doesn't perform illegal operations
        /// Note that artillery cannot move and attack at the same time
        /// @param unitID unit to be moved
        /// @param fieldID target field
        /// @return false if operation cannot be done
        bool moveAndAttack(const UnitID &unitID, const FieldID &fieldID);

        bool move(const UnitID &unitID, const Position &position);
        // bool move(const UnitID &unitID, const Field &Field);
        bool isHuman(const FactionID &faction) const;
        bool isBot(const FactionID &faction) const;
        void startNextRound();
        void handlePlayerTurn();
        void handleBotTurn();
        void generateMap(const unsigned int &size);
        void loadMap(const Area &area, const std::vector<FactionID> &humanFactions, const std::vector<FactionID> &botFactions);
        void printUnitInfo(const UnitID &unitID);
        void printUnitsInfo();
        size_t countFactions() const;

        bool existsUnit(const UnitID &unitID) const;
        void resupplyFrom(const FacilityID &fuelDepotID);
        void resupplyAllUnits();
};