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
        bool move(const UnitID &unitID, const Position &position);
        bool isHuman(const FactionID &faction) const;
        bool isBot(const FactionID &faction) const;
        void startNextRound();
        void handlePlayerTurn();
        void handleBotTurn();
        void loadMap(const Area &area, const std::vector<FactionID> &humanFactions, const std::vector<FactionID> &botFactions);
        void printUnitInfo(const UnitID &unitID);
        void printUnitsInfo();
        const int countFactions() const;

        const bool existsUnit(const UnitID &unitID) const;
};