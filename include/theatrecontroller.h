#pragma once
#include "area.h"

class TheatreController : public Area {
    private:
        bool simulationStarted = false;
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
        void loadMap(const Area &area);
        void printUnitInfo(const UnitID &unitID);
        void printUnitsInfo();
};