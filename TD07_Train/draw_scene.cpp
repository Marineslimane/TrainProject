#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"

/// Camera parameters
float angle_theta {90.0};      // Angle between x axis and viewpoint
float angle_phy {80.0};      // Angle between z axis and viewpoint
float dist_zoom {40.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};


// Grid parameters
const float square_size {10}; // size of each square of the grid
const int N {10}; // size of grid (grid itself is a square)
std::vector<GLBI_Convex_2D_Shape> grid; // grid is an array of squares

// Rail parameters 
const float sr  {0.3f};
const float rr {0.2f};
const float POS_X_RAIL1 {3.0f};
const float POS_X_RAIL2 {7.0f}; 

STP3D::IndexedMesh* meshCube = nullptr;
STP3D::IndexedMesh* meshCylinder = nullptr;

void initScene()
{
	std::vector<float> points {0.0, 0.0, 0.0}; // origin of the scene
    somePoints.initSet(points, 1.0, 1.0, 1.0); // color of the origin point 

    std::vector<float> baseCarre{
        0.0, 0.0, 0.0,
        square_size, 0.0, 0.0,
        square_size, square_size, 0.0,
        0.0, square_size, 0.0};

    ground.initShape(baseCarre);
    ground.changeNature(GL_TRIANGLE_FAN);
    meshCube = STP3D::basicCube(1.0f);
    meshCube->createVAO();
    meshCylinder = STP3D::basicCylinder(6.0f, rr, 32); // hauteur=6, rayon=rr
    meshCylinder->createVAO();
}

void drawRail(float posX)
{
    myEngine.mvMatrixStack.pushMatrix();
    // Le cube basicCube(1) est centré à l'origine, taille 1x1x1
    // On translate au centre du rail : milieu en y = 5, hauteur z = sr/2
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, 5.0f, sr / 2.0f));
    // Scale : sr en x, 10 en y (longueur du rail), sr en z (hauteur)
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.6f, 0.6f, 0.6f);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawBalast(float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    
    myEngine.mvMatrixStack.addTranslation(Vector3D(8.0f, posY, rr));
    myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(0.0f, 0.0f, 1.0f));
    
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.55f, 0.35f, 0.1f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}
void drawRightRail()
{
    drawRail(POS_X_RAIL1);
    drawRail(POS_X_RAIL2);

    float espacement = (10.0f - 5.0f * 2.0f * rr) / 4.0f;
    for (int i = 0; i < 5; i++) {
        float posY = rr + i * (2.0f * rr + espacement);
        drawBalast(posY);
    }
}

void drawScene() {
    glPointSize(10.0);
    somePoints.drawSet(); // draws origin

	// drawing the grid 
	for (int i = 0; i < N; i++) // columns
    {
        for (int j = 0; j < N; j++) // ligns
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({(i - (N / 2)) * square_size,  // for the coordinates, the interval between each top corner of a square is of square_size 
                                                   (j - (N / 2)) * square_size, // same for bottom corners
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

            ground.drawShape(); // draws the square 

            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
    }
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-5.0f, -5.0f, 0.0f));
    myEngine.updateMvMatrix();
    drawRightRail();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}