#include "tools/basic_mesh.hpp"
#include "train.hpp"

STP3D::IndexedMesh* meshSphere;
STP3D::IndexedMesh* meshCylinder;

void initFace()
{
    meshSphere = STP3D::basicSphere(5.4f, 60, 60); // radius, smoothness of vertical lines, smoothness of horizontal lines
    meshSphere->createVAO();

    meshCylinder = STP3D::basicCylinder(30, 5, 60, 1); // height, radius, div_round, div_height
    meshCylinder->createVAO();
}

void drawFace(GLBI_Engine& myEngine)
{
    // base cylinder of face (for neck and overall shape)
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 5.0f, 10.0f));
    // myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.5, 0.5, 0.5);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // base sphere of face (for round appearance of face, especially on the side)
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 8.0f, 10.0f));
    // myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.5, 0.5, 0.5);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // top black cylinder on neck
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 6.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.2, 1.2, 1.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // eyes
    // myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addTranslation(Vector3D(5.0, 5.0f, 10.0f));
    // // myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
    // myEngine.updateMvMatrix();
    // myEngine.setFlatColor(0.5, 0.5, 0.5);
    // meshSphere->draw();
    // myEngine.mvMatrixStack.popMatrix();
    // myEngine.updateMvMatrix();
}