#include "tools/basic_mesh.hpp"
#include "train.hpp"

STP3D::IndexedMesh* meshSphere;
STP3D::IndexedMesh* meshCylinder;

void initFace()
{
    meshSphere = STP3D::basicSphere(5.8f, 60, 60); // radius, smoothness of vertical lines, smoothness of horizontal lines
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
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 7.0f, 10.0f));
    // myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.5, 0.5, 0.5);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // top black cylinder on neck
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 6.5f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.2, 1.2, 1.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // EYES
    // left base
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.0, 3.0f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.35, 0.35, 0.35));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right base
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.0, 3.0f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.35, 0.35, 0.35));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right pupil
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 2.0f, 10.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.225, 0.225, 0.225));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // left pupil
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.5, 2.0f, 10.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.225, 0.225, 0.225));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right pupil
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 1.0f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.15, 0.15, 0.15));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.8, 0.8, 0.8);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}