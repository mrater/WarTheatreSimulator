#include "theatrecontroller.h"
#include "mapeditor.h"

#include <iostream>



namespace FACTION{
    const FactionID HUMAN1 = 1;
    const FactionID HUMAN2 = 2;
}

MapEditor mapEditor;
inline TheatreController prepareExampleBoard(){
    const std::pair<int,int> plain_fields[] = {{-1,-1}, {-1, 0}, {-2, 1}, {1, -1}};
    const std::pair<int,int> forest_fields[] = {{0, -1}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}};
    
    for (const auto &position : plain_fields){
        mapEditor.addField(position.first, position.second, Terrain::PLAIN);
    }

    for (const auto &position : forest_fields){
        mapEditor.addField(position.first, position.second, Terrain::FOREST);
    }

    mapEditor.setFactionsNumber(2);
    mapEditor.addUnit(-1, -1, UnitCategory::INFANTRY, FACTION::HUMAN1);
    mapEditor.addUnit(0, 1, UnitCategory::INFANTRY, FACTION::HUMAN1);
    mapEditor.addUnit(1, -1, UnitCategory::ARTILLERY, FACTION::HUMAN2);
    
    TheatreController game = TheatreController();
    game.loadMap(mapEditor.generateArea(), {1, 2}, {});
    return game;
}
int main()
{
    TheatreController game = prepareExampleBoard();
    game.startInteractive();
}