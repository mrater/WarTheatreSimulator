/**
 * @file field.h
 * @brief File with field classes. 
 * @details Field is characterized with position (q,r, -q-r) and terrain type (forest, urban etc.)
 */

#include<utility>

/// @brief  type for identifiers of terrain
typedef int TerrainType;

/// @brief unique identifier of a field
typedef int FieldID;

/// @brief namespace consisting of terrain types IDs
namespace Terrain {
    const TerrainType NONE = 0;
    const TerrainType FOREST = 1;
    const TerrainType URBAN = 2;
    const TerrainType PLAIN = 3;
}

/**
 * @brief Class to store position of a field.
 * @details Coordinate systems which is going to be used for this hexagonal simulation is 
 * q, r for two axes and s for the third (however, s is "artificial" since s = -q - r) 
 */
class Position{
    private:
        int q,r;

        /// @brief calculate third s coordinate
        /// @return s, which equals -q - r
        const int s();
    public:
        Position (const int &_q, const int &_r);
};


/// @brief All fields will give certain punishments for movement and attack thus need to be distinguished
class FieldType{
    public:
        /// @brief get ID of terrain type of this field
        /// @return ID of terrain type for this field
        virtual const TerrainType getTerrainType();
};

class ForestTerrain : public FieldType{
    /// @brief get ID of forest terrain
    /// @return Terrain::FOREST
    const TerrainType getTerrainType();
};
class UrbanTerrain : public FieldType{
    /// @brief get ID of urban terrain
    /// @return Terrain::URBAN
    const TerrainType getTerrainType();
};
class PlainTerrain : public FieldType{
    /// @brief get ID of plain terrain
    /// @return Terrain::PLAIN
    const TerrainType getTerrainType();
};


class Field{
    private:
        Position position;
        FieldID fieldID;
    
    protected:
        FieldType fieldType;

    public:
        /**
         * @brief get position of a field
         * @returns position as (q,r,s)
        */
        const Position getPosition();

        /**
         * @returns type of terrain of the field
        */
        virtual const FieldType getTerrainType();
};