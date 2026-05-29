#include "draw_scene.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

const int N; // size of grid (grid is a square)

void initScene() // drawing the base of the scene, the grid
{

	std::vector<float> points {0.0,0.0,0.0}; // origin of the scene
	somePoints.initSet(points,1.0,1.0,1.0); // color of the origin, here : white 

	float half_nb_square {(N/2.f)/10.f};

	// drawing the grid :
	for (int i {1} ; i <= N ; i++) // ligns
	{
		for (int j {1} ; j <= N ; j++) // columns
		{
			std::vector<float> square {-(N/2.f) + i*(half_nb_square), -(N/2.f)*i, 0.0,  // bottom left
								(N/2.f)*i, -(N/2.f)*i, 0.0, // bottom right
								(N/2.f)*i, (N/2.f)*i, 0.0, // top right
								(N/2.f)*i, -(N/2.f)*i, 0.0, // top left
			};

			ground.initShape(square);
		}
	}
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

	myEngine.setFlatColor(0.2,0.0,0.0);
	ground.drawShape();
}



