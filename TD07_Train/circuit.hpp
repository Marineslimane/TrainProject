#pragma once

#include <vector>
#include <fstream> // for json

#include "rails.hpp"

struct RailCellCoord
{
    int x;
    int y;
};

struct CircuitData 
{
    std::vector<RailCellCoord> cells;
    int squareSize;
};

enum class RailChoice // all possibilities for rail placement
{
    straightHoriz,
    straightVert,
    curvedTopLeft,
    curvedTopRight,
    curvedBottomLeft,
    curvedBottomRight
};

CircuitData loadCircuit(const std::string& path);

void initCircuit(const std::string& path);

void drawCircuit(GLBI_Engine& myEngine, Rail& rails);