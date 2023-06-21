/**
 * @file field.h
 * @brief File with field classes.
 * @details Field is characterized with position (q,r, -q-r) and terrain type (forest, urban etc.)
 */
#pragma once
#include <utility>
#include <set>
/// @brief  type for identifiers of terrain
typedef int TerrainType;

/// @brief unique identifier of a field
typedef int FieldID;

/// @brief namespace consisting of terrain types IDs
namespace Terrain
{
    constexpr TerrainType NONE = 0;
    constexpr TerrainType PLAIN = 1;
    constexpr TerrainType URBAN = 2;
    constexpr TerrainType FOREST = 3;
    
    constexpr double TERRAIN_BONUS[] = {-1, 1.0, 0.6, 0.4};
    const char* const LITERAL[] = {"NONE", "PLAIN", "URBAN", "FOREST"};
}

/**
 * @brief Class to store position of a field.
 * @details Coordinate systems which is going to be used for this hexagonal simulation is
 * q, r for two axes and s for the third (however, s is "artificial" since s = -q - r)
 */
class Position
{
public:
    int q, r;

    /// @brief calculate third s coordinate
    /// @return s, which equals -q - r
    int s();
    Position();
    Position(const int &_q, const int &_r);
    // Position();
    bool operator==(const Position &anotherPosition) const;
    // void operator=(const Position &anotherPosition);
    bool operator<(const Position &anotherPosition) const; //temporary solution to satisfy set requirements
    public:
        std::set<Position> getPotentialAdjacentPositions() const;
        int distanceTo(const Position &anotherPosition) const;
};

class Field
{
private:
    Position position;
    FieldID fieldID;

protected:
    TerrainType fieldType;

    /// @brief get terrain bonus
    /// greater the bonus, easier it is to attack and harder to defend 
    double getBonus() const;

    

public:
    Field(const FieldID &fieldID, const int &q, const int &r, const TerrainType &terrainType);
    Field();
    /**
     * @brief get position of a field
     * @returns position as (q,r,s)
     */
    const Position getPosition() const;

    /**
     * @returns type of terrain of the field
     */
    TerrainType getTerrainType() const;
    
    FieldID getFieldID() const;
    
    
};