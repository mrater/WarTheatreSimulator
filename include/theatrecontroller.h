#pragma once
#include "area.h"

class TheatreController : public Area {
    private:
        bool simulationStarted = false;

        //factions controlled by humans
        std::vector<UnitFactionID> humanPlayers;

        //factions controlled by bots
        std::vector<UnitFactionID> botPlayers; 
    protected:
    public:
        TheatreController();
        bool attackFromDistance(const FieldID &fieldID);
        bool moveAndAttack(const FieldID &fieldID);
        bool move(const Field &Field);
        void startNextTurn();
        void handlePlayerTurn();
        void handleBotTurn();
        void generateMap(const unsigned int &size);
        void loadMap(const Area &area, const std::vector<UnitFactionID> &humanFactions, const std::vector<UnitFactionID> &botFactions);
        void printUnitInfo(const UnitID &unitID);
        void printUnitsInfo();
};