#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"
#include "train_station.hpp"
#include "rails.hpp"

/// Camera parameters
float angle_theta {90.0};      // Angle between x axis and viewpoint
float angle_phy {80.0};      // Angle between z axis and viewpoint
float dist_zoom {40.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape square{3}; // for grid squares
Rail rails; // struct Rail for rails objects

// Grid parameters
const float squareSize {10}; // size of each square of the grid
const int N {10}; // size of grid (grid itself is a square)
std::vector<GLBI_Convex_2D_Shape> grid; // grid is an array of squares

// Rail parameters
const float posY {5.0};

void initSquare()
{
    std::vector<float> squareVertices{
        0.0, 0.0, 0.0,
        squareSize, 0.0, 0.0,
        squareSize, squareSize, 0.0,
        0.0, squareSize, 0.0};

    square.initShape(squareVertices);
    square.changeNature(GL_TRIANGLE_FAN);
}

void initScene()
{
	std::vector<float> points {0.0, 0.0, 0.0}; // origin of the scene
    somePoints.initSet(points, 1.0, 1.0, 1.0); // color of the origin point 

    // init objects 
    initSquare(); // square of grid
    // rails
    rails.initStraightRails();
    rails.initCurvedRails();
}

void drawGrid()
{
	for (int i = 0; i < N; i++) // columns
    {
        for (int j = 0; j < N; j++) // ligns
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({(i - (N / 2)) * squareSize,  // for the coordinates, the interval between each top corner of a square is of squareSize 
                                                   (j - (N / 2)) * squareSize, // same for bottom corners
                                                   0.0f}); // grid is drawn inside plane space Oxy
            myEngine.updateMvMatrix();

            // setting different colors to distinguish squares
            if ((i + j) % 2 == 0)
            {
                myEngine.setFlatColor(0.f, 0.f, 0.f); // black
            }
            else
            {
                myEngine.setFlatColor(1.f, 1.f, 1.f); // white
            }

            square.drawShape(); // draws the square 

            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
    }
}

void drawScene() 
{
    glPointSize(10.0);
    somePoints.drawSet(); // draws origin

    drawGrid(); // draws grid

    // draws rails
    rails.drawStraightTrack(myEngine, 5, 0.0f, 0.0f, squareSize); // straight line
    rails.drawPositionnedCurvedRails(myEngine, 0.5, 0.125, squareSize, -M_PI/2);
}