#include "draw_scene.hpp"

/// Camera parameters
float angle_theta {90.0};      // Angle between x axis and viewpoint
float angle_phy {80.0};      // Angle between z axis and viewpoint
float dist_zoom {40.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

float square_size {10};
const int N {10}; // size of grid (grid is a square)
std::vector<GLBI_Convex_2D_Shape> grid;

void initScene() // drawing the base of the scene, the grid
{
	std::vector<float> points {0.0, 0.0, 0.0};
    somePoints.initSet(points, 1.0, 1.0, 1.0);

    std::vector<float> baseCarre{
        0.0, 0.0, 0.0,
        10.0, 0.0, 0.0,
        10.0, 10.0, 0.0,
        0.0, 10.0, 0.0};

    ground.initShape(baseCarre);
    ground.changeNature(GL_TRIANGLE_FAN);
}

void drawFrame() {
	// TO DO
}

void drawBase() {
	// TO DO
}

void drawArm() {
	// TO DO
}

void drawPan() {
	// TO DO
}

void drawScene() {
	glPointSize(10.0);

	somePoints.drawSet();

	// drawing the grid : 
	for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            // decalage des cases
            myEngine.mvMatrixStack.addTranslation({(i - (N / 2)) * square_size,
                                                   (j - (N / 2)) * square_size,
                                                   0.0f});
            myEngine.updateMvMatrix();

            // cases qui alternent entre deux verts
            if ((i + j) % 2 == 0)
            {
                myEngine.setFlatColor(0.31f, 0.459f, 0.267f); // vert clair
            }
            else
            {
                myEngine.setFlatColor(0.267, 0.412, 0.227); // vert foncé
            }
            ground.drawShape();

            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
    }

	myEngine.setFlatColor(0.2,0.0,0.0);
	ground.drawShape();
}



