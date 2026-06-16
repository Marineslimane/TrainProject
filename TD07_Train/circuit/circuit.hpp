#pragma once

#include <vector>
#include <fstream> // for json

#include "../rails/rails.hpp"
#include "../rails/rail_types.hpp" // for RailChoice
#include "../models/kenny/kenny.hpp"
#include "../models/train/train.hpp"
#include "../models/train_station/train_station.hpp"
#include "../models/lamp/lamp.hpp"

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
    RailCellCoord light;
    int squareSize; // size of a square of grid, by default it's 10
};

JsonData loadCircuit(const std::string& path);

void initCircuit(const std::string& path);

// rails related functions
RailChoice getRailType(RailCellCoord pos, RailCellCoord previous, RailCellCoord next);

float curvedAngle(RailChoice type);

// draw functions
void drawCircuit(GLBI_Engine& myEngine, Rail& rails);

void drawElements(GLBI_Engine& myEngine, Rail& rails);

void trainProgression();

void trainMoves(float& posX, float& posY, float& angle);