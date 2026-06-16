#include "draw_scene.hpp"
#include "tools/basic_mesh.hpp"
// models :
#include "models/train_station/train_station.hpp"
#include "rails/rails.hpp"
#include "models/train/train.hpp"
#include "models/kenny/kenny.hpp"
#include "models/tree/tree.hpp"
#include "models/lamp/lamp.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

#include "circuit/circuit.hpp"

// Camera parameters
float cam_x {0.0f};
float cam_y {-20.0f};
float cam_z {5.0f};
float cam_angle {90.0f};
float cam_pitch {0.0f};
bool lightingEnabled {true};
bool nightMode {false};
GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
Rail rails; // struct Rail for rails objects
extern JsonData world_data; // all data contained in json file

// Grid parameters
const float squareSize {10}; // size of each square of the grid
const int N {20}; // size of grid (grid itself is a square)

STP3D::StandardMesh* groundMesh = nullptr; 
STP3D::IndexedMesh* meshCube = nullptr;
STP3D::IndexedMesh* meshCylinder2= nullptr;
STP3D::StandardMesh* meshCone = nullptr;

GLBI_Texture grassTexture;

// lamp light coordinates
float lightPosX {25.0f};
float lightPosY {20.0f};

// light functions
void enableLighting() 
{
    if (lightingEnabled) myEngine.switchToPhongShading();
}

void disableLighting() 
{
    if (lightingEnabled) myEngine.switchToFlatShading();
}

void initScene(const std::string& jsonPath)
{
    std::vector<float> points {0.0, 0.0, 0.0};
    somePoints.initSet(points, 1.0, 1.0, 1.0);
 
    // meshes
    groundMesh = STP3D::basicRect(squareSize, squareSize);
    groundMesh->createVAO();
 
    meshCube = STP3D::basicCube(1.0f);
    meshCube->createVAO();
 
    meshCylinder2 = STP3D::basicCylinder(1.0f, 1.0f);
    meshCylinder2->createVAO();
 
    meshCone = STP3D::basicCone(1.0f, 1.0f);
    meshCone->createVAO();
 
    // MODELS INIT
    // rails
    rails.initStraightRails();  
    rails.initCurvedRails();
    // others
    initTrainStation();
    initKenny();
    initTree();
    initStreetlight();
    initBush();
    // train
    initTrain();
    initFace();
    initEyebrow();
    initMouth();
    // train station
    initTrainStation();
    // json init
    initCircuit(jsonPath);
 
    // textures
    grassTexture.createTexture();
    int gw, gh, gn;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* grassPixels = stbi_load("../assets/textures/herbe.png", &gw, &gh, &gn, 0);

    if (grassPixels == nullptr)
    {
        std::cerr << "Grass texture failed" << std::endl;
    } 
    else 
    {
        grassTexture.attachTexture();
        grassTexture.loadImage(gw, gh, gn, grassPixels);
        grassTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        grassTexture.setParameters(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        grassTexture.setParameters(GL_TEXTURE_WRAP_S, GL_REPEAT);
        grassTexture.setParameters(GL_TEXTURE_WRAP_T, GL_REPEAT);
        grassTexture.detachTexture();
        stbi_image_free(grassPixels);

        std::cerr << "Grass texture worked" << std::endl;
    }
    
    // LIGHTS
    myEngine.switchToPhongShading();

    // light init
    myEngine.setLightPosition({5.0f, -5.0f, 8.0f, 0.0f}, 0); //sun
    myEngine.setLightIntensity({1.4f, 1.2f, 0.9f}, 0);
    myEngine.addALight({lightPosX, lightPosY + 0.6f, 2.1f, 1.0f}, {0.0f, 0.0f, 0.0f}); // lamp light
    myEngine.addALight({0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f});

    // fixed parameters :
    myEngine.setShininess(8.0f);
    myEngine.setSpecularColor({0.2f, 0.2f, 0.15f});
    myEngine.setAttenuationFactor({1.0f, 0.05f, 0.01f});

    myEngine.switchToFlatShading();
}

void drawGrid()
{
    // light and texture 
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

    // coordinates of train
    float trainPosX = world_data.train.x * world_data.squareSize;
    float trainPosY = world_data.train.y * world_data.squareSize;
    // coordinates of light
    float lightWorldX = world_data.light.x * world_data.squareSize;
    float lightWorldY = world_data.light.y * world_data.squareSize;

    if (lightingEnabled)
    {
        myEngine.switchToPhongShading();
        
        if (nightMode)
        {
            //night
            myEngine.setLightPosition({0.0f, 0.0f, 100.0f, 0.0f}, 0);
            myEngine.setLightIntensity({0.2f, 0.2f, 0.1f}, 0);

            // train light
            myEngine.setLightPosition({trainPosX-5, trainPosY + 0.6f, 2.1f, 1.0f}, 1);
            myEngine.setLightIntensity({2.3f, 2.3f, 1.6f}, 1);

            myEngine.setLightPosition({lightWorldX, lightWorldY, 14.5f, 1.0f}, 2);
            myEngine.setLightIntensity({3.5f, 3.2f, 2.0f}, 2);
        }
        else
        {
            //day
            myEngine.setLightPosition({5.0f, -5.0f, 8.0f, 0.0f}, 0);
            myEngine.setLightIntensity({1.4f, 1.2f, 0.9f}, 0);

            // train light
            myEngine.setLightPosition({trainPosX, trainPosY + 0.6f, 2.1f, 1.0f}, 1);
            myEngine.setLightIntensity({0.2f, 0.2f, 0.1f}, 1);

            myEngine.setLightPosition({lightWorldX, lightWorldY, 14.5f, 1.0f}, 2);
            myEngine.setLightIntensity({0.0f, 0.0f, 0.0f}, 2);  
        }
        myEngine.switchToFlatShading();
    }

    drawGrid();

    // trees and bushes
    srand(12);
        for (int i = 0; i < 15; i++)
        {
            float x = (rand() % 190) - 95.0f;
            float y = (rand() % 190) - 95.0f;
        if (x > -25 && x < 45 && y > -10 && y < 45) { i--; continue; }
            drawTree(myEngine, x, y);
        }
    srand(14);
        for (int i = 0; i < 9; i++)
        {
            float x = (rand() % 190) - 95.0f;
            float y = (rand() % 190) - 95.0f;
        if (x > -25 && x < 45 && y > -10 && y < 45) { i--; continue; }
            drawBush(myEngine, x, y);
        }
        
    // draw objects
    drawCircuit(myEngine, rails);
    trainProgression();
    drawElements(myEngine, rails);
}
