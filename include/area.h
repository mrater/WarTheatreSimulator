/**
 * @file area.h
 * @author Maciej Sikorski
 * @brief This class manages whole war area 
 * This manages states of a world, including units stats, fields, their terrain types etc.
 * It DOES NOT handle changes of such world
 * @version 0.1
 * @date 20.05.2023
 */

#include <vector>
#include "field.h"
#include "units.h"

class Area{
    /// @brief Array with fields of the area
    std::vector<Field> fields;

    /// @brief Units present in arrea
    std::vector<Unit> units;

    /// @brief Check if given position exists in the area
    /// @param position - checked position
    /// @return true if field of given position exists
    bool isRealPosition(const Position &position);

    /// @brief get unit on position
    /// @param position - position to search unit on
    /// @return pointer to unit on a given position. units.end() is returned if none is available
    Unit& getUnitOnPosition(const Position &position);


    /// @brief get units of faction
    /// @param unitFactionID faction of unit
    /// @return vector of units that belong to faction
    std::vector<Unit> getUnitsOfFaction(const UnitFactionID &unitFactionID) const;
};