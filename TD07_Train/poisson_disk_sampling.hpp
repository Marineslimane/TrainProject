#pragma once

#include <vector>

struct Vec2 
{ 
    float x;
    float y; 
};

struct PointsGenerationParameters 
{
    // parameters for points generation
    float r {0.15}; // Poisson disk radius, represents the minimal distance between 2 points (2 samples)
    int k {30}; // maximum number of attempts before a candidate is rejected in the Poisson algorithm
    int max_points {150}; // maximum number of points that can be generated in the end on the map
    int max_trees {20};
    int max_bushes {15};
};

Vec2 imageToGrid(const Vec2 point, const float cellSize, const int w, const int h);

float distance(const Vec2 point1, const Vec2 point2);

Vec2 generateRandomPointAround(Vec2 point, float r);

bool isValid(const Vec2 candidate, const float cellSize, const float r, const std::vector<Vec2>& positions, const std::vector<std::vector<int>>& grid, const int w, const int h);

std::vector<Vec2> generate2DPositions(PointsGenerationParameters const& params);

