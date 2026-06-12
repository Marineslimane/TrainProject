#pragma once

#include <vector>
#include <fstream> // for json

#include "rails.hpp"
#include "rail_types.hpp" // for RailChoice

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

CircuitData loadCircuit(const std::string& path);

void initCircuit(const std::string& path);

RailChoice getRailType(RailCellCoord pos, RailCellCoord previous, RailCellCoord next);

float curvedAngle(RailChoice type);



void drawCircuit(GLBI_Engine& myEngine, Rail& rails);