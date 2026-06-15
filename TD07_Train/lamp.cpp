#include "lamp.hpp"
 

const float METAL_R {0.08f}, METAL_G {0.08f}, METAL_B {0.08f};
const float LIGHT_R {0.95f}, LIGHT_G {0.9f},  LIGHT_B {0.55f};
 
STP3D::IndexedMesh* lampGround = nullptr;
STP3D::IndexedMesh* lampBase = nullptr;
STP3D::IndexedMesh* lampMat = nullptr;
STP3D::IndexedMesh* lampLight = nullptr;
 
void initLampadaire()
{

    lampGround = STP3D::basicSphere(1.0f, 16, 8);
    lampGround->createVAO();
 
    lampBase = STP3D::basicSphere(1.0f, 16, 8);
    lampBase->createVAO();

    lampMat = STP3D::basicCylinder(8.0f, 0.25f, 16);
    lampMat->createVAO();
 
    lampLight = STP3D::basicSphere(2.0f, 16, 12);
    lampLight->createVAO();
}
void initLampadaireLight(GLBI_Engine& myEngine, float posX, float posY, float posZ)
{
   
    myEngine.addALight(
        {posX, posY, posZ + 9.0f, 1.0f}, 
        {LIGHT_R, LIGHT_G, LIGHT_B} 
    );
}
void drawLampadaire(GLBI_Engine& myEngine, float x, float y)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(x, y, 0.0f));
 
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.3f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0f, 1.0f, 0.3f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(METAL_R, METAL_G, METAL_B);
    lampGround->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
 

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.9f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.7f, 0.7f, 0.6f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(METAL_R, METAL_G, METAL_B);
    lampBase->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
 

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 1.2f));
    myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(METAL_R, METAL_G, METAL_B);
    lampMat->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
 
    //light
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 9.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.45f, 0.45f, 0.45f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(LIGHT_R, LIGHT_G, LIGHT_B);
    lampLight->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
 
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}