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
    meshCylinder = STP3D::basicCylinder(6.0f, rr, 32);
    meshCylinder->createVAO();
}

void drawRail(float posX)
{
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, 5.0f, 0.6f));
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


    float debut = sr + rr;
    float fin = 10.0f - sr - rr;
    float espacement = (fin - debut) / 4.0f;
    for (int i = 0; i < 5; i++) {
        float posY = debut + i * espacement;
        drawBalast(posY);
    }
}

std::vector<float> bezierCurve(float t)
{
    std::vector<float> point1 {3.0, 0.,0.};
    std::vector<float> point2 {0., 3.0,0.};
    std::vector<float> point3 {3.0/2.f, 3.0/2.f,0.}; // middle of the segment [point1 ; point2]

    float new_x {(1-t)*(1-t)*point1[0] + 2*(1-t)*t*point2[0] + t*t*point3[0]};
    float new_y {(1-t)*(1-t)*point1[1] + 2*(1-t)*t*point2[1] + t*t*point3[1]};

    return {new_x, new_y};
}

void drawCurvedRail()
{
    int nb_precision {10};

    for (int i = 0; i < nb_precision; i++) 
    {
        float t = (float)i / nb_precision;

        std::vector<float> position {bezierCurve(t)};

        float angle {(float)((atan2(position[0], position[1])*180.f)/M_PI)};

        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(position[0], position[1], sr / 2.0f));
    
        myEngine.mvMatrixStack.addRotation(angle, Vector3D(0.0f, 0.0f, 1.0f));
        myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0.6f, 0.6f, 0.6f);
        meshCube->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
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
<<<<<<< HEAD

    // drawing rails
    // right rail
=======
    //Rail placement
>>>>>>> 1cd3039c8a0d535605315032f7d2ebc5240a5528
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.0f));
    myEngine.updateMvMatrix();
    drawRightRail();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // curved rail
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-5.0f, -5.0f, 0.0f));
    myEngine.updateMvMatrix();
    drawCurvedRail();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}