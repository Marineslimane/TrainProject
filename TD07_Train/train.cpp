#include "tools/basic_mesh.hpp"
#include "train.hpp"

STP3D::IndexedMesh* meshSphere;
STP3D::IndexedMesh* meshCylinder;

GLBI_Convex_2D_Shape eyebrow{3};

void initFace()
{
    meshSphere = STP3D::basicSphere(5.8f, 60, 60); // radius, smoothness of vertical lines, smoothness of horizontal lines
    meshSphere->createVAO();

    meshCylinder = STP3D::basicCylinder(30, 5, 60, 1); // height, radius, div_round, div_height
    meshCylinder->createVAO();
}

void initEyebrow()
{
    std::vector<float> eyebrowVertices {
        -1.0f,  0.0f,  0.0f,  // bottom-left
         1.0f, -0.3f,  0.0f,  // bottom-right (slightly lower for tilt)
        -0.6f,  0.7f,  0.0f   // top-left point
    };

    eyebrow.initShape(eyebrowVertices);
    eyebrow.changeNature(GL_TRIANGLE_STRIP);
}

void drawEyebrow(GLBI_Engine& myEngine)
{
    myEngine.mvMatrixStack.pushMatrix();
    //myEngine.mvMatrixStack.addRotation(-M_PI/2, Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.0f, 8.5f, 10.0f)); // above left eye
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.2f, 1.2f, 1.2f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    // drawing faces of the rail 
    eyebrow.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawFace(GLBI_Engine& myEngine)
{
    // // base cylinder of face (for neck and overall shape)
    // myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addTranslation(Vector3D(0, 5.0f, 10.0f));
    // myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 0.5, 1.0));
    // myEngine.updateMvMatrix();
    // myEngine.setFlatColor(0.5, 0.5, 0.5);
    // meshCylinder->draw();
    // myEngine.mvMatrixStack.popMatrix();
    // myEngine.updateMvMatrix();

    // base sphere of face (for round appearance of face, especially on the side)
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 7.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 0.5, 1.0));
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
    // WHITE PART (base)
    // left base
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.0, 5.0f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.2, 0.3));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // right base
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.0, 5.0f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.2, 0.3));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // PUPIL
    // right pupil
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 4.0f, 10.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.15, 0.1, 0.15));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // left pupil
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.5, 4.0f, 10.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.15, 0.1, 0.15));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // LIGHT
    // right light in the eye
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 3.5f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.08, 0.04, 0.08));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // left light in the eye
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.5, 3.5f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.08, 0.04, 0.08));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // NOSE
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 4.0f, 9.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.25, 0.25, 0.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.55, 0.55, 0.55);  
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // EYEBROWS
}