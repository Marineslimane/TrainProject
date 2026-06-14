#pragma once

#include <vector>
#include <fstream> // for json

#include "rails.hpp"
#include "rail_types.hpp" // for RailChoice
#include "kenny.hpp"
#include "train.hpp"
#include "train_station.hpp"

struct RailCellCoord
{
    int x;
    int y;
};

struct JsonData 
{
    std::vector<RailCellCoord> cells; // coordinates of rails
    // coordinates of other elements 
    RailCellCoord kenny;
    RailCellCoord train_station;
    RailCellCoord train;
    int squareSize; // size of a square of grid, by default it's 10
};

JsonData loadCircuit(const std::string& path);

void initCircuit(const std::string& path);

RailChoice getRailType(RailCellCoord pos, RailCellCoord previous, RailCellCoord next);

float curvedAngle(RailChoice type);



void drawCircuit(GLBI_Engine& myEngine, Rail& rails);

void drawElements(GLBI_Engine& myEngine, Rail& rails);