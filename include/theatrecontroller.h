#include "areamanager.h"

class TheatreController : public AreaManager{
    private:
        bool simulationStarted;
    public:
        bool attackFromDistance(const FieldID &fieldID);
        bool moveAndAttack(const FieldID &fieldID);
        void startNextTurn();
        void handlePlayerTurn();
        void handleBotTurn();
        void generateMap(const unsigned int &size);
        void loadMap(const Area &area);
};