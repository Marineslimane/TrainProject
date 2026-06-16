#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm> // for std::clamp

#include "poisson_disk_sampling.hpp"

Vec2 imageToGrid(const Vec2 point, const float cellSize, const int w, const int h) // grid coordinates of a point
{
    int gridX {std::clamp(static_cast<int>(point.x / cellSize), 0, w - 1)};
    int gridY {std::clamp(static_cast<int>(point.y / cellSize), 0, h - 1)};

    return {static_cast<float>(gridX), static_cast<float>(gridY)};
}

float distance(const Vec2 point1, const Vec2 point2)
{
    return sqrt((point2.x - point1.x)*(point2.x  - point1.x) + (point2.y - point1.y)*(point2.y - point1.y));
}

Vec2 generateRandomPointAround(Vec2 point, float r)
{
    float angle = ((float)rand() / RAND_MAX) * 2.0f * M_PI;
    float dist  = r + ((float)rand() / RAND_MAX) * r;

    return {point.x + dist * cos(angle), point.y + dist * sin(angle)};
}

bool isValid(const Vec2 candidate, const float cellSize, const float r, const std::vector<Vec2>& positions, const std::vector<std::vector<int>>& grid, const int w, const int h)
{
    if (candidate.x >= 0.f && candidate.x < 1.f && candidate.y >= 0.f && candidate.y < 1.f) // working in the normalized space [0;1]
    {
        Vec2 cellCoord {imageToGrid(candidate, cellSize, w, h)}; // grid coordinates of candidate

        int searchStartX {std::max(0, static_cast<int>(std::floor(cellCoord.x - 2)))};
        int searchEndX {std::min(static_cast<int>(std::floor(cellCoord.x + 2)), w - 1)};
        int searchStartY {std::max(0, static_cast<int>(std::floor(cellCoord.y - 2)))};
        int searchEndY {std::min(static_cast<int>(std::floor(cellCoord.y + 2)), h - 1)};

        for (int x {searchStartX}; x <= searchEndX; x++) 
        {
            for (int y {searchStartY}; y <= searchEndY; y++) 
            {
                int i {grid[y][x]}; // index of the point in the cell grid(y,x)

                if (i != -1) // if there do is a point in that cell
                {
                    if (distance(candidate, positions[i]) < r)
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

std::vector<Vec2> generate2DPositions(PointsGenerationParameters const& params) 
{
    std::vector<Vec2> positions {}; // our result 
    
    // definition of the background grid : 
    float cellSize {params.r/(float)sqrt(2)};
    int w {static_cast<int>(1.0f / cellSize)};
    int h {w}; // working with squared cells
    std::vector<std::vector<int>> grid(h, std::vector<int>(w, -1)); // (nb of rows, (nb of columns, values))
    // -1 in a cell signifies no sample is in it, else, grid[y][x] stores the index of the sample located in that cell

    positions.reserve(params.max_points); // params.max_points is the maximum potential number of points that can be generated, in the end, on the map
    std::vector<int> active_list {}; // stores potential candidates

    // randomly choosing the first point/sample
    Vec2 first_point {static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX)};

    Vec2 gridCoordFirst = imageToGrid(first_point, cellSize, w, h);
    grid[static_cast<int>(gridCoordFirst.y)][static_cast<int>(gridCoordFirst.x)] = 0; // first_point is the center of the spawn of new points so index 0

    active_list.emplace_back(0);
    positions.emplace_back(first_point);

    while (!active_list.empty())
    {
        // choosing a random index from the active list : 
        int random_i {rand() % static_cast<int>(active_list.size())};
        Vec2 current_point {positions[active_list[random_i]]};

        bool accepted {false};

        for (int i {0}; i < params.k ; i++)
        {
            // generating a new point around current_point (within the annulus surrounding the point)
            Vec2 candidate {generateRandomPointAround(current_point, params.r)};

            if (candidate.x < 0.f || candidate.x > 1.f || candidate.y < 0.f || candidate.y > 1.f) // out of bound
            {
                continue;
            }

            if (isValid(candidate, cellSize, params.r, positions, grid, w, h)) // the candidate follows the min distance rule for all of its neighbours in its neighbourhood ie 5*5 squares around
            {
                int candidate_i {static_cast<int>(positions.size())}; // last in positions

                positions.emplace_back(candidate);
                active_list.emplace_back(candidate_i);

                Vec2 gridCoordCand {imageToGrid(candidate, cellSize, w, h)};
                grid[gridCoordCand.y][gridCoordCand.x] = candidate_i;

                accepted = true;
                break; // a working neighbour candidate was found for this current_point
            }
        }

        if (!accepted) // after k tries, no generated candidate around current_point follows the rule of min distance
        {
            active_list[random_i] = active_list.back();
            active_list.pop_back(); // current_point is deleted from the active list
        }
    }

    return positions;
}