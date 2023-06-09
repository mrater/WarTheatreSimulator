#pragma once
#include "area.h"
#include "units.h"
#include "field.h"

class MapEditor{
    private:
        /// @brief Array with fields of the area
        std::map<FieldID, Field> fields;

        /// @brief Units present in arrea
        std::map<UnitID, Unit> units;

        FieldID globalFieldIndex = 1;
        UnitID globalUnitIndex = 1;

        int numberOfFactions = 0;
    
    public:
        MapEditor();
        Area generateArea();
        void addUnit(const int &q, const int &r, const UnitType &unitType, const FactionID &unitFactionID, const UnitID &unitID);
        void addUnit(const int &q, const int &r, const UnitType &unitType, const FactionID &unitFactionID);
        void addField(const int &q, const int &r, const TerrainType &terrainType, const FieldID &fieldID);
        void addField(const int &q, const int &r, const TerrainType &terrainType);
        void setFactionsNumber(const int &numberOfFactions);
};