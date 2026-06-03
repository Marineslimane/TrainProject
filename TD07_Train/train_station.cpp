#include "train_station.hpp"

const float trainStation_WIDTH  {30.0f};
const float trainStation_DEPTH  {20.0f};
const float trainStation_HEIGHT {20.0f};

STP3D::IndexedMesh* meshCube2;

//couleur
const float WALL_R {0.9f}, WALL_G {0.85f}, WALL_B {0.7f};

void drawTrainStation(float posX, float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX + trainStation_WIDTH/2.0f, posY + trainStation_DEPTH/2.0f, trainStation_HEIGHT/2.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(trainStation_WIDTH, trainStation_DEPTH, trainStation_HEIGHT));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(WALL_R, WALL_G, WALL_B);
    meshCube2->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}