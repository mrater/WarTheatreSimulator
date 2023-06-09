#pragma once
#include "area.h"

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
        bool attackFromDistance(const FieldID &fieldID);
        bool moveAndAttack(const FieldID &fieldID);
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
        const int countFactions() const;
};