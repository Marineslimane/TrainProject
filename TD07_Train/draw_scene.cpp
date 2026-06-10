#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"
#include "train_station.hpp"
#include "rails.hpp"
#include "train.hpp"
#include "kenny.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"
#include "circuit.hpp"

/// Camera parameters
float cam_x {0.0f};
float cam_y {-20.0f};
float cam_z {5.0f};
float cam_angle {90.0f};
float cam_pitch {0.0f};
bool lightingEnabled {true};
GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
Rail rails; // struct Rail for rails objects

// Grid parameters
const float squareSize {10}; // size of each square of the grid
const int N {40}; // size of grid (grid itself is a square)

STP3D::StandardMesh* groundMesh = nullptr; 
STP3D::IndexedMesh* meshCube = nullptr;
STP3D::IndexedMesh* meshCylinder2= nullptr;
STP3D::StandardMesh* meshCone = nullptr;

GLBI_Texture grassTexture;

// Rail parameters
const float posY {5.0};

void enableLighting() {
    if (lightingEnabled) myEngine.switchToPhongShading();
}

void disableLighting() {
    if (lightingEnabled) myEngine.switchToFlatShading();
}
void initScene()
{
    std::vector<float> points {0.0, 0.0, 0.0};
    somePoints.initSet(points, 1.0, 1.0, 1.0);
 
    //meshs
    groundMesh = STP3D::basicRect(squareSize, squareSize);
    groundMesh->createVAO();
 
    meshCube = STP3D::basicCube(1.0f);
    meshCube->createVAO();
 
    meshCylinder2 = STP3D::basicCylinder(1.0f, 1.0f);
    meshCylinder2->createVAO();
 
    meshCone = STP3D::basicCone(1.0f, 1.0f);
    meshCone->createVAO();
 
    rails.initStraightRails();
    rails.initCurvedRails();
    initTrainStation();
    initKenny();
    initFace();
    initEyebrow();
    initMouth();
 
    grassTexture.createTexture();
    int gw, gh, gn;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* grassPixels = stbi_load("../assets/textures/herbe.png", &gw, &gh, &gn, 0);
    if (grassPixels == nullptr) {
        std::cerr << "Erreur texture herbe" << std::endl;
    } else {
        grassTexture.attachTexture();
        grassTexture.loadImage(gw, gh, gn, grassPixels);
        grassTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        grassTexture.setParameters(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        grassTexture.setParameters(GL_TEXTURE_WRAP_S, GL_REPEAT);
        grassTexture.setParameters(GL_TEXTURE_WRAP_T, GL_REPEAT);
        grassTexture.detachTexture();
        stbi_image_free(grassPixels);
        std::cerr << "Texture herbe OK" << std::endl;
    }
    
    //light
    if (lightingEnabled) myEngine.switchToPhongShading();
    myEngine.setLightPosition({2.0f, -3.0f, 5.0f, 0.0f}, 0);
    myEngine.setLightIntensity({1.2f, 1.1f, 0.9f}, 0);
    myEngine.addALight({-1.0f, 1.0f, 3.0f, 0.0f}, {0.3f, 0.4f, 0.5f});
    myEngine.setShininess(5.0f);
    myEngine.setSpecularColor({0.3f, 0.3f, 0.3f}); 
    myEngine.setAttenuationFactor({1.0f, 0.01f, 0.001f});
    if (lightingEnabled) myEngine.switchToFlatShading();
    // train
    initTrain();
    // train station
    initTrainStation();
    // json
    initCircuit();
}
void drawGrid()
{

    if (lightingEnabled) myEngine.switchToPhongShading();
    myEngine.activateTexturing(true);
    grassTexture.attachTexture();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation({
                (float)(i - (N/2)) * squareSize + squareSize/2.0f,
                (float)(j - (N/2)) * squareSize + squareSize/2.0f,
                -0.5f});
            myEngine.mvMatrixStack.addHomothety(Vector3D(squareSize, squareSize, 0.5f));
            myEngine.updateMvMatrix();
            meshCube->draw();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
    }

    grassTexture.detachTexture();
    myEngine.activateTexturing(false);
}
void drawScene() 
{
    glPointSize(10.0);
    somePoints.drawSet();
    enableLighting();
    drawGrid();
    
    // draws objects
    drawKenny(10.0f, 0.0f, 0.0f);
    drawTrainStation(myEngine, -20.0, 10.0);
    // rails.drawStraightTrack(myEngine, 5, 0.0f, 0.0f, squareSize); // straight line
    // rails.drawPositionnedCurvedRails(myEngine, 0.5, 0.125, squareSize, -M_PI/2);
    drawCircuit(myEngine, rails);
    // draws train
    drawPositionnedTrain(myEngine, 25.0, 20.0);
    // trainstation
    drawTrainStation(myEngine, 60.0, 10.0);
}
