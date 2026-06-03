#include "tools/basic_mesh.hpp"
#include "train.hpp"

IndexedMesh* meshSphere;

void initFace()
{
    meshSphere = STP3D::basicSphere(6.0f, 30, 30);
    meshSphere->createVAO();
}

void drawFace(GLBI_Engine& myEngine)
{
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 5.0f, 0));
    // myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));

    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}