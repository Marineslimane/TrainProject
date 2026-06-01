#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"
#include "train_station.hpp"

void drawRail(float posX);
void drawBalast(float posY);
void drawRightRail();
void drawCurvedRail();
void drawStraightTrack(int nb_rails, float startX, float startY);

/// Camera parameters
float angle_theta {90.0};      // Angle between x axis and viewpoint
float angle_phy {80.0};      // Angle between z axis and viewpoint
float dist_zoom {40.0};      // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape square{3}; // for grid squares
// curved rails shapes 
// for great rail
GLBI_Convex_2D_Shape greatTopFace{3}; // top face of great curved rail
GLBI_Convex_2D_Shape greatBottomFace{3}; // bottom face of great curved rail
GLBI_Convex_2D_Shape greatLeftFace{3}; // left face of great curved rail
GLBI_Convex_2D_Shape greatRightFace{3}; // right face of great curved rail
// for small rail
GLBI_Convex_2D_Shape smallTopFace{3}; // top face of small curved rail
GLBI_Convex_2D_Shape smallBottomFace{3}; // bottom face of small curved rail
GLBI_Convex_2D_Shape smallLeftFace{3}; // left face of small curved rail
GLBI_Convex_2D_Shape smallRightFace{3}; // right face of small curved rail

// Grid parameters
const float squareSize {10}; // size of each square of the grid
const int N {10}; // size of grid (grid itself is a square)
std::vector<GLBI_Convex_2D_Shape> grid; // grid is an array of squares

// Rail parameters 
const float sr  {0.3f};
const float rr {0.2f};
const float POS_X_RAIL1 {3.0f};
const float POS_X_RAIL2 {7.0f}; 

STP3D::IndexedMesh* meshCube = nullptr;
STP3D::IndexedMesh* meshCylinder = nullptr;

void initCurvedRails()
{
    int nbTriangles {10}; // number of triangles used to draw rails

    // great rail
    std::vector<float> greatTopFaceVertices {};
    std::vector<float> greatBottomFaceVertices {};
    std::vector<float> greatLeftFaceVertices {};
    std::vector<float> greatRightFaceVertices {};

    float greatRadius {7.0};
    float smallRadius {7.0 - sr};

    for (int i {0} ; i < nbTriangles ; i++)
    {
        float angle {i*(((float)M_PI/2)/nbTriangles)};

        // nb : no need to rotate triangles since TRIANGLE_STRIP automatically joins vertices
        // triangles along greatRadius
        greatTopFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatTopFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatTopFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius
        greatTopFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatTopFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatTopFaceVertices.push_back(rr+sr); // z coordinate

        // triangles along greatRadius
        greatBottomFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatBottomFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatBottomFaceVertices.push_back(rr); // z coordinate
        // triangles along smallRadius
        greatBottomFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatBottomFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatBottomFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius
        greatLeftFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatLeftFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatLeftFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius
        greatLeftFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatLeftFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatLeftFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius
        greatRightFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatRightFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatRightFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius
        greatRightFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatRightFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatRightFaceVertices.push_back(rr); // z coordinate
    }

    greatTopFace.initShape(greatTopFaceVertices);
    greatTopFace.changeNature(GL_TRIANGLE_STRIP);
    greatBottomFace.initShape(greatBottomFaceVertices);
    greatBottomFace.changeNature(GL_TRIANGLE_STRIP);
    greatLeftFace.initShape(greatLeftFaceVertices);
    greatLeftFace.changeNature(GL_TRIANGLE_STRIP);
    greatRightFace.initShape(greatRightFaceVertices);
    greatRightFace.changeNature(GL_TRIANGLE_STRIP);

    // small rail
    // nb : using same number of triangles for great and small rail

    std::vector<float> smallTopFaceVertices {};
    std::vector<float> smallBottomFaceVertices {};
    std::vector<float> smallLeftFaceVertices {};
    std::vector<float> smallRightFaceVertices {};

    float greatRadius2 {3.0};
    float smallRadius2 {3.0 - sr};

    for (int i {0} ; i < nbTriangles ; i++)
    {
        float angle {i*(((float)M_PI/2)/nbTriangles)};

        // nb : no need to rotate triangles since TRIANGLE_STRIP automatically joins vertices
        // triangles along greatRadius2
        smallTopFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallTopFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallTopFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius2
        smallTopFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallTopFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallTopFaceVertices.push_back(rr+sr); // z coordinate

        // triangles along greatRadius2
        smallBottomFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallBottomFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallBottomFaceVertices.push_back(rr); // z coordinate
        // triangles along smallRadius2
        smallBottomFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallBottomFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallBottomFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius2
        smallLeftFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallLeftFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallLeftFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius2
        smallLeftFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallLeftFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallLeftFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius2
        smallRightFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallRightFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallRightFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius2
        smallRightFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallRightFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallRightFaceVertices.push_back(rr); // z coordinate
    }

    smallTopFace.initShape(smallTopFaceVertices);
    smallTopFace.changeNature(GL_TRIANGLE_STRIP);
    smallBottomFace.initShape(smallBottomFaceVertices);
    smallBottomFace.changeNature(GL_TRIANGLE_STRIP);
    smallLeftFace.initShape(smallLeftFaceVertices);
    smallLeftFace.changeNature(GL_TRIANGLE_STRIP);
    smallRightFace.initShape(smallRightFaceVertices);
    smallRightFace.changeNature(GL_TRIANGLE_STRIP);
}

void initStraightRails()
{
    meshCube = STP3D::basicCube(1.0f);
    meshCube->createVAO();
    meshCylinder = STP3D::basicCylinder(6.0f, rr, 32);
    meshCylinder->createVAO();
}

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
    initStraightRails();
    initCurvedRails();
}

void drawStraightRail(float posX)
{
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, 5.0f, rr+sr));
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

void drawStraightRails()
{
    drawStraightRail(POS_X_RAIL1);
    drawStraightRail(POS_X_RAIL2);

    float start = sr + rr;
    float end = 10.0f - sr - rr;
    float gap = (end - start) / 4.0f; // test
    for (int i = 0; i < 5; i++) { 
        float posY = start + i * gap;
        drawBalast(posY);
    }
}

void drawCurvedRail()
{
    // great part
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addHomothety(Vector3D(1.5f, 1.5f, 1.5f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.6f, 0.6f, 0.6f);
    // drawing faces of the rail 
    greatTopFace.drawShape();
    greatBottomFace.drawShape();
    greatLeftFace.drawShape();
    greatRightFace.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // small part
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addHomothety(Vector3D(1.5f, 1.5f, 1.5f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.6f, 0.6f, 0.6f);
    // drawing faces of the rail 
    smallTopFace.drawShape();
    smallBottomFace.drawShape();
    smallLeftFace.drawShape();
    smallRightFace.drawShape();
    myEngine.mvMatrixStack.popMatrix();

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

void drawStraightTrack(int nbRails, float startX, float startY)
{   
    for (int i = 0; i < nbRails; i++)
    {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(startX, startY + i * squareSize, 0.0f));
        myEngine.updateMvMatrix();
        drawStraightRails();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
    }
}

void drawScene() {
    glPointSize(10.0);
    somePoints.drawSet(); // draws origin

    drawGrid(); // draws grid

    // draws rails
    drawStraightTrack(5, 0.0f, 0.0f); // straight line
    drawCurvedRail();
}