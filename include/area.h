/**
 * @file area.h
 * @brief This class manages whole war area 
 * @details This manages states of a world, including units stats, fields, their terrain types etc.
 * It DOES NOT handle changes of such world.
 */
#pragma once
#include <vector>
#include <map>
#include <set>
#include "units.h"
#include "infrastructure.h"

class Area{
    private:
        friend class TheatreController;
    protected:
        /// @brief Array with fields of the area
        std::map<FieldID, Field> fields;

        /// @brief Units present in arrea
        std::map<UnitID, Unit> units;

        /// @brief magazines of fuel on the map
        std::map<FacilityID, FuelDepot> fuelMagazines;

        Area();
    public:
        int numberOfFactions;
        Area(std::map<FieldID, Field> newFields, std::map<UnitID, Unit> newUnits);
        /// @brief Check if given position exists in the area
        /// @param position checked position
        /// @return true if field of given position exists
        bool isRealPosition(const Position &position) const;

        FieldID getFieldByPosition(const Position &position) const;

        bool existsPosition(const Position &position) const;

        /// @brief get unit on position
        /// @param position position to search unit on
        /// @return pointer to unit on a given position. returns -1 if unavailable
        UnitID getUnitOnPosition(const Position &position) const;

        /// @brief get units of faction
        /// @param unitFactionID faction of unit
        /// @return vector of units that belong to faction
        std::vector<UnitID> getUnitsOfFaction(const FactionID &unitFactionID);

        const bool isUnitOnPosition(const Position &position) const;

        bool isUnitOnField(const FieldID &field);

        /// @brief get unit of certain ID
        /// @param unitID ID of wanted unit
        /// @return constant pointer to unit or NULL if not found
        Unit getUnit(const UnitID &unitID);

        const Field &getFieldWithUnit(const UnitID &unitID) const;

        void fillNeighbours(const Position &fromPosition, const int &range, std::set<FieldID> &fields);

        std::set<FieldID> getFieldsWithinRange(const Position &fromPosition, const int &range);

        std::set<FieldID> getFieldsSuitableToMove(const Position &position, const int &range);
        
        
        // std::map<UnitID, Unit> getUnits;
        // std::map<
};