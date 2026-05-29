#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"

/// Camera parameters
float angle_theta {45.0};      // Angle between x axis and viewpoint
float angle_phy {30.0};      // Angle between z axis and viewpoint
float dist_zoom {30.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

const int N {10}; // size of grid (grid is a square)

//rails
const float sr  {0.3f};
const float rr  {0.4f};
const float POS_X_RAIL1 {3.0f};
const float POS_X_RAIL2 {7.0f}; 

STP3D::IndexedMesh* meshCube = nullptr;
STP3D::IndexedMesh* meshCylinder = nullptr;

void initScene() // drawing the base of the scene, the grid
{

	std::vector<float> points {0.0,0.0,0.0}; // origin of the scene
	somePoints.initSet(points,1.0,1.0,1.0); // color of the origin, here : white 

	float half_nb_square {(N/2.f)/10.f};

	// drawing the grid :
	for (int i {1} ; i <= N ; i++) // ligns
	{
		for (int j {0} ; j < N ; j++) // columns
		{
			std::vector<float> square {-(N/2.f) + j*(half_nb_square), (N/2.f) - i*(half_nb_square), 0.0,  // bottom left
								-(N/2.f) + (j+1)*(half_nb_square), (N/2.f) - i*(half_nb_square), 0.0, // bottom right
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

void drawRail(float posX)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.6f, 0.6f, 0.6f);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();
}

void drawBalast(float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.0f, posY, 0.0f));
    myEngine.mvMatrixStack.addRotation(-90.0f, Vector3D(0.0f, 0.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(rr, 6.0f, rr));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.55f, 0.35f, 0.1f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
}

void drawRailDroit()
{
    drawRail(POS_X_RAIL1);
    drawRail(POS_X_RAIL2);

    for (int i = 0; i < 5; i++) {
        drawBalast(sr + i * 2.0f * sr);
    }
}

