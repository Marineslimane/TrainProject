#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"

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

//rails
const float sr  {0.3f};
const float rr  {0.4f};
const float POS_X_RAIL1 {3.0f};
const float POS_X_RAIL2 {7.0f}; 

STP3D::IndexedMesh* meshCube = nullptr;
STP3D::IndexedMesh* meshCylinder = nullptr;

void initScene()
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
    myEngine.setFlatColor(0.2, 0.0, 0.0);
    ground.drawShape();

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

