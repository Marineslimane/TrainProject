#include "tree.hpp"

const float BROWN_R  {0.45f}, BROWN_G  {0.3f},  BROWN_B  {0.15f};

STP3D::IndexedMesh* treeCyl = nullptr;
STP3D::IndexedMesh* treeSphere = nullptr;
STP3D::IndexedMesh* bushCyl = nullptr;

void initTree()
{
    treeSphere = STP3D::basicSphere(1.0f, 4, 4);
    treeSphere->createVAO();

    treeCyl = STP3D::basicCylinder(3.0f, 0.5f, 6);
    treeCyl->createVAO();
}

void initBush()
{
    bushCyl = STP3D::basicCylinder(3.0f, 0.5f, 6);
    bushCyl->createVAO();
}

void drawTree(GLBI_Engine& myEngine, float x, float y)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(x, y, 0.0f));
    myEngine.mvMatrixStack.addHomothety(5.0f); 
    myEngine.updateMvMatrix();

    // trunk
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0f, 1.0f, 1.0f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(BROWN_R, BROWN_G, BROWN_B);
    treeCyl->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // leaves
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 4.5f));
    myEngine.mvMatrixStack.addHomothety(2.0f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.2f, 0.55f, 0.15f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // LeftLeaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-1.2f, 0.0f, 3.8f));
    myEngine.mvMatrixStack.addHomothety(1.3f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.15f, 0.5f, 0.1f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // RightLeaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(1.2f, 0.0f, 3.8f));
    myEngine.mvMatrixStack.addHomothety(1.3f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.25f, 0.6f, 0.1f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // UpLeaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 6.0f));
    myEngine.mvMatrixStack.addHomothety(1.2f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.2f, 0.6f, 0.12f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawBush(GLBI_Engine& myEngine, float x, float y)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(x, y, 0.0f));
    myEngine.mvMatrixStack.addHomothety(3.0f); 
    myEngine.updateMvMatrix();

    // Leaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(2.0f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.2f, 0.55f, 0.15f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // LeftLeaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-1.7f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(1.3f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.15f, 0.5f, 0.1f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // fruits
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-1.9f, 0.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(0.3f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.9f, 0.2f, 0.1f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(1.4f, 0.4f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(0.3f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.9f, 0.2f, 0.1f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // RightLeaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(1.2f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(1.3f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.25f, 0.6f, 0.1f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // UpLeaf
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(1.2f);
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.2f, 0.6f, 0.12f);
    treeSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}