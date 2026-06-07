#include "kenny.hpp"

//Couleurs
const float ORANGE_R {1.0f},  ORANGE_G {0.45f}, ORANGE_B {0.0f};
const float BROWN_R  {0.45f}, BROWN_G  {0.3f},  BROWN_B  {0.15f};
const float BEIGE_R  {0.9f},  BEIGE_G  {0.8f},  BEIGE_B  {0.65f};
const float WHITE_R  {1.0f},  WHITE_G  {1.0f},  WHITE_B  {1.0f};
const float BLACK_R  {0.05f}, BLACK_G  {0.05f}, BLACK_B  {0.05f};


STP3D::IndexedMesh* kennyHead = nullptr;
STP3D::IndexedMesh* kennyEye = nullptr;
STP3D::IndexedMesh* kennySphere = nullptr;
STP3D::IndexedMesh* kennyCyl = nullptr;
STP3D::IndexedMesh* kennyArmCyl = nullptr;

void initKenny()
{
    kennyHead = STP3D::basicSphere(5.0f, 32, 16);
    kennyHead->createVAO();

    kennyEye = STP3D::basicSphere(1.0f, 32, 12);
    kennyEye->createVAO();

    kennySphere = STP3D::basicSphere(1.0f, 32, 8);
    kennySphere->createVAO();

    kennyCyl = STP3D::basicCylinder(8.0f, 4.0f, 16);
    kennyCyl->createVAO();

    kennyArmCyl = STP3D::basicCylinder(5.0f, 1.2f, 12);
    kennyArmCyl->createVAO();
}

void drawSphere(STP3D::IndexedMesh* mesh, GLBI_Engine& eng, float x, float y, float z, float sx, float sy, float sz, float r, float g, float b)
{
    eng.mvMatrixStack.pushMatrix();
    eng.mvMatrixStack.addTranslation(Vector3D(x, y, z));
    eng.mvMatrixStack.addHomothety(Vector3D(sx, sy, sz));
    eng.updateMvMatrix();
    eng.setFlatColor(r, g, b);
    mesh->draw();
    eng.mvMatrixStack.popMatrix();
    eng.updateMvMatrix();
}

void drawKenny(float posX, float posY, float posZ)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, posZ));
    myEngine.mvMatrixStack.addHomothety(0.5f);
    myEngine.updateMvMatrix();

    //pieds
    drawSphere(kennySphere, myEngine, -2.0f, 0.0f, 2.2f, 3.5f, 3.0f, 1.0f, BLACK_R, BLACK_G, BLACK_B);
    drawSphere(kennySphere, myEngine,  2.0f, 0.0f, 2.2f, 3.5f, 3.0f, 1.0f, BLACK_R, BLACK_G, BLACK_B);

    //corps
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 2.75));
    myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(ORANGE_R, ORANGE_G, ORANGE_B);
    kennyCyl->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    //bras gauche
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-3.0f, 0.0f, 10.0f));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addRotation(0.4f, Vector3D(0.0f, 0.0f, 1.0f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(ORANGE_R, ORANGE_G, ORANGE_B);
    kennyArmCyl->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    //bras droit
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(3.0f, 0.0f, 10.0f));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addRotation(-0.4f, Vector3D(0.0f, 0.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1, 1, 1));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(ORANGE_R, ORANGE_G, ORANGE_B);
    kennyArmCyl->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    //mains
    drawSphere(kennySphere, myEngine, -4.75f, 0.0f, 5.5f, 1.5f, 1.5f, 1.5f, BROWN_R, BROWN_G, BROWN_B);
    drawSphere(kennySphere, myEngine,  4.75f, 0.0f, 5.5f, 1.5f, 1.5f, 1.5f, BROWN_R, BROWN_G, BROWN_B);

    //tete
    drawSphere(kennyHead, myEngine, 0.0f, 0.0f, 15.0f, 1.15f, 1.15f, 1.15f, ORANGE_R, ORANGE_G, ORANGE_B);

    //capuche
    drawSphere(kennySphere, myEngine, 0.0f, -3.5f, 15.0f, 5.0f, 1.8f, 5.0f, BROWN_R, BROWN_G, BROWN_B);

    //visage
    drawSphere(kennySphere, myEngine, 0.0f, -4.5f, 15.0f, 3.5f, 2.0f, 3.5f, BEIGE_R, BEIGE_G, BEIGE_B);

    //yeux
    drawSphere(kennyEye, myEngine, -1.5f, -6.0f, 16.0f, 2.0f, 0.5f, 2.0f, WHITE_R, WHITE_G, WHITE_B);
    drawSphere(kennyEye, myEngine,  1.5f, -6.0f, 16.0f, 2.0f, 0.5f, 2.0f, WHITE_R, WHITE_G, WHITE_B);

    //pupilles
    drawSphere(kennySphere, myEngine, -1.5f, -6.3f, 16.2f, 0.3f, 0.3f, 0.3f, BLACK_R, BLACK_G, BLACK_B);
    drawSphere(kennySphere, myEngine,  1.5f, -6.3f, 16.2f, 0.3f, 0.3f, 0.3f, BLACK_R, BLACK_G, BLACK_B);

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}