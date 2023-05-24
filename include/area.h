/**
 * @file area.h
 * @brief This class manages whole war area 
 * @details This manages states of a world, including units stats, fields, their terrain types etc.
 * It DOES NOT handle changes of such world.
 */

#include <vector>
#include <map>
#include "units.h"
class Area{

    protected:
        /// @brief Array with fields of the area
        std::map<FieldID, Field> fields;

        /// @brief Units present in arrea
        std::map<UnitID, Unit> units;
    public:
        /// @brief Check if given position exists in the area
        /// @param position checked position
        /// @return true if field of given position exists
        bool isRealPosition(const Position &position);

        /// @brief get unit on position
        /// @param position position to search unit on
        /// @return pointer to unit on a given position. units.end() is returned if none is available
        Unit& getUnitOnPosition(const Position &position);

        /// @brief get units of faction
        /// @param unitFactionID faction of unit
        /// @return vector of units that belong to faction
        std::vector<UnitID> getUnitsOfFaction(const UnitFactionID &unitFactionID) const;

        /// @brief get unit of certain ID
        /// @param unitID ID of wanted unit
        /// @return constant pointer to unit or NULL if not found
        const Unit &getUnit(const UnitID &unitID);

        
    
};