/**
 * @file area.h
 * @brief This class manages whole war area 
 * @details This manages states of a world, including units stats, fields, their terrain types etc.
 * It DOES NOT handle changes of such world.
 */
#pragma once
#include <vector>
#include <map>
#include <assert.h>
#include <set>
#include "units.h"
#include <string>
// #include "infrastructure.h"

class Area{
    private:
        friend class TheatreController;
    protected:
        /// @brief Array with fields of the area
        std::map<FieldID, Field> fields;

        /// @brief Units present in arrea
        std::map<UnitID, Unit> units;

        /// @brief magazines of fuel on the map
        // std::map<FacilityID, FuelDepot> fuelMagazines;

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

        UnitID getUnitOnField(const FieldID &field) const;

        /// @brief get units of faction
        /// @param unitFactionID faction of unit
        /// @return vector of units that belong to faction
        std::set<UnitID> getUnitsOfFaction(const FactionID &unitFactionID) const;

        // std::vector<UnitID> getUnitsOfFaction(const FactionID &unitFactionID) const;

        bool isUnitOnPosition(const Position &position) const;

        bool isUnitOnField(const FieldID &field) const;

        /// @brief get unit of certain ID
        /// @param unitID ID of wanted unit
        /// @return constant pointer to unit or NULL if not found
        const Unit& getUnitConstantReference(const UnitID &unitID) const;
        
        /// @brief get unit of certain ID
        /// @param unitID ID of wanted unit
        /// @return reference to unit or NULL if not found    
        Unit &getUnit(const UnitID &unitID);

        // FuelDepot &getFuelDepot(const FacilityID &facilityID);
        // const FuelDepot &getFuelDepot(const FacilityID &facilityID) const;

        const Field &getFieldWithUnit(const UnitID &unitID) const;

        void fillNeighbours(const Position &fromPosition, const int &range, std::set<FieldID> &fields);

        std::set<FieldID> getFieldsWithinRange(const Position &fromPosition, const int &range);

        std::set<FieldID> getFieldsSuitableToMove(const Position &position, const int &range);

        /// @return sum of movement points of all units in faction 
        int getTotalMovementPointsOfFaction(const FactionID &factionID) const;

        //check if unit with given id exists
        bool existsUnit(const UnitID &unitID) const;

        //check if faction exists
        bool existsFaction(const FactionID &faction) const;

        // set movement points to 0 in order to proceed without moving or attacking
        /// @return false if operation is impossible
        bool skipMovement(const UnitID &unitID);

        // skip all movement of faction
        /// @return false if operation impossible
        bool skipAllMovementOfFaction(const FactionID &faction);

        
        std::set<UnitID> getFriendlyUnitsWithinRange(const Position &fromPosition, const int &range, const FactionID &faction);

        /// @brief get all factions that exists
        /// @return set of FactionIDs of existing factions (i.e. ones who have at least one unit)
        std::set<FactionID> getAllFactions();

        // export units to csv of type (unitID, factionID, organisation, supply level, movement points, type, position.Q, position.R)
        void exportUnitsToCSV(const std::string &filename) const;

        // export fields to csv
        void exportFieldsToCSV(const std::string &filename) const;
        
        /// @brief export data about fields and units to csv
        /// @param fieldsFilename filename of fields data
        /// @param unitsFilename filename of units data
        void exportAllToCSV(const std::string &fieldsFilename, const std::string &unitsFilename);
};