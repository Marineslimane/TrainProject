#pragma once

#include <vector>
#include <fstream> // for json

#include "rails.hpp"

struct TrackCell
{
    int x;
    int y;
};

struct CircuitData 
{
    std::vector<TrackCell> cells;
    int squareSize;
};

CircuitData loadCircuit(const std::string& path);

void initCircuit(const std::string& path);

void drawCircuit(GLBI_Engine& myEngine, Rail& rails);