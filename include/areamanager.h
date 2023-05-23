/**
 * @file areamanager.h
 * @author Maciej Sikorski
 * @brief This file manages the game area and its metadadata 
 * It has no safeguards, so it should not be used in top-level UI.
 * This class won't calculate any results of any events.
 * @version 0.1
 * @date 22.05.2023
 */

#include "area.h"

class AreaManager : Area{

    /// @brief next unique identifier of a unit. Should increase when unit is created. Should not ever be decreased
    UnitID nextUnitID = 1;

    /// @brief next unique identifier of a field. Should increase for each new field. Should not ever be decreased
    FieldID nextFieldID = 1;
    
    /// @brief Spawn unit on a given position
    /// @param position Position of a unit 
    /// @param unit - unit to be spawned
    void createUnit(const Position &position, const Unit &unit);
    
    /// @brief  Remove unit from area
    /// @param unitID ID of removed unit
    void removeUnit(const UnitID &unitID);

    /// @brief Move unit to position
    /// @param UnitID ID of unit to be moved
    /// @param position position to be reached by unit
    void moveUnit(const UnitID &UnitID, const Position &position);
};