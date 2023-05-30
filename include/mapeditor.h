#include "area.h"
#include "units.h"
#include "field.h"

class MapEditor{
    private:
    /// @brief Array with fields of the area
    std::map<FieldID, Field> fields;

    /// @brief Units present in arrea
    std::map<UnitID, Unit> units;
    
    public:
        Area generateArea();
        void addUnit(const int &q, const int &r, const UnitType unitType);
        void addField(const int &q, const int &r, const TerrainType terrainType);
};