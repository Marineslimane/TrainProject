#include "tools/basic_mesh.hpp"
#include "train.hpp"

STP3D::IndexedMesh* meshSphere;
STP3D::IndexedMesh* meshCylinder;
STP3D::IndexedMesh* meshCube=nullptr;
STP3D::StandardMesh* meshRect2 = nullptr;

GLBI_Convex_2D_Shape eyebrow{3};
GLBI_Convex_2D_Shape mouth{3};

// colors :
float lightGrey {0.85};
float darkGrey {0.8};
float blue {0.8};

void initFace()
{
    meshSphere = STP3D::basicSphere(5.8f, 60, 60); // radius, smoothness of vertical lines, smoothness of horizontal lines
    meshSphere->createVAO();

    meshCylinder = STP3D::basicCylinder(30, 5, 60, 1); // height, radius, div_round, div_height
    meshCylinder->createVAO();

    meshCube = STP3D::basicCube(1.0f);
    meshCube->createVAO();
}

void initEyebrow()
{
    std::vector<float> eyebrowVertices {
        -1.0f,  0.0f,  0.0f,  // bottom-left
         1.0f, 0.0f,  0.0f,  // bottom-right
        0.0f,  0.0f,  1.0f   // top
    };

    eyebrow.initShape(eyebrowVertices);
    eyebrow.changeNature(GL_TRIANGLE_STRIP);
}

void initMouth()
{
    std::vector<float> mouthVertices {
        -1.0f,  0.0f,  1.0f,  // bottom-left
         1.0f, 0.0f,  1.0f,  // bottom-right
        0.0f,  0.0f,  0.0f   // top
    };

    mouth.initShape(mouthVertices);
    mouth.changeNature(GL_TRIANGLE_STRIP);
}

void initWheel()
{
    meshRect2 = STP3D::basicRect(5.8f, 5.0); // x, z
    meshRect2 ->createVAO();
}

void initTrain()
{
    initFace();
    initEyebrow();
    initMouth();
    initWheel();
}

void drawMouth(GLBI_Engine& myEngine)
{
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 4.5f, 6.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(2.5, 3.0, 1.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);  
    mouth.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // shadow
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 4.7f, 5.7f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(2.5, 3.0, 1.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);  
    mouth.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawEyebrow(GLBI_Engine& myEngine)
{
    // left
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.25f, 4.5f, 13.25f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 1.0, 0.75));
    myEngine.mvMatrixStack.addRotation(-M_PI/12, Vector3D(0.0, 1.0, 0.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    eyebrow.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.25f, 4.5f, 13.25f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 1.0, 0.75));
    myEngine.mvMatrixStack.addRotation(M_PI/12, Vector3D(0.0, 1.0, 0.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    eyebrow.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawFace(GLBI_Engine& myEngine)
{
    // base sphere of face (for round appearance of face, especially on the side)
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 7.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 0.5, 1.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(lightGrey, lightGrey, lightGrey);   
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // top black cylinder on neck
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 6.5f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.2, 0.4, 1.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // tailpipe
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 15.0f, -15.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.2, 0.4));
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
    // left base shadow
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.0, 5.2f, 11.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.2, 0.3));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
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
    // right base shadow
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.0, 5.2f, 11.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.2, 0.3));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // PUPIL
    // right pupil
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 4.0f, 10.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.125, 0.1, 0.125));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // left pupil
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.5, 4.0f, 10.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.125, 0.1, 0.125));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // LIGHT
    // right light in the eye
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(-M_PI/72, Vector3D(0.0, 0.001, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 3.5f, 10.95f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.05, 0.04, 0.05));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // left light in the eye
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.5, 3.5f, 11.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.05, 0.04, 0.05));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // NOSE
    // base (round part)
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 3.9f, 9.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.225, 0.25, 0.18));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(lightGrey, lightGrey, lightGrey);  
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // upper part 
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 3.9f, 9.8f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.18, 0.25, 0.18));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(lightGrey, lightGrey, lightGrey);  
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // shadow
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(-M_PI/120, Vector3D(0.0, 0.1, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 4.0f, 9.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.25, 0.25, 0.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);  
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // CHEEKS
    // left base
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.0, 5.0f, 9.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.4, 0.28, 0.27));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(lightGrey,lightGrey, lightGrey);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // left shadow
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.0, 5.3f, 8.7f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.4, 0.28, 0.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // right base
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.0, 5.0f, 9.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.4, 0.28, 0.27));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(lightGrey,lightGrey, lightGrey);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right shadow
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.0, 5.3f, 8.7f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.4, 0.28, 0.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

}

void drawWheel(GLBI_Engine& myEngine, float posX, float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(0.0, 0.0, 1.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 4.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.8, 0.08, 0.8));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawWheels(GLBI_Engine& myEngine, float posX, float posY)
{
    for (int i {0} ; i < 3 ; i++)
    {
        drawWheel(myEngine, posX + i*10.0, posY); // left side wheel
        drawWheel(myEngine, posX + i*10.0, -posY-2.5); // right side wheel

        // inside of wheels 
        // left side wheel
        for (int j {0}; j < 8; j++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 4.0f));       // centre exact de la roue
            myEngine.mvMatrixStack.addRotation((2*M_PI/8)*j, Vector3D(0.0, 1.0, 0.0)); // cercle complet autour de Y
            myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 2.5f));         // décalage radial (ajuste selon rayon roue)
            myEngine.mvMatrixStack.addHomothety(Vector3D(0.05f, 0.8f, 0.15f));
            myEngine.updateMvMatrix();
            myEngine.setFlatColor(0.9f, 0.9f, 0.9f);
            meshCube->draw();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }

        // right side wheel
        for (int j {0}; j < 8; j++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation(Vector3D(posX, -posY - 2.5f, 4.0f));
            myEngine.mvMatrixStack.addRotation((2*M_PI/8)*j, Vector3D(0.0, 1.0, 0.0));
            myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 2.5f));
            myEngine.mvMatrixStack.addHomothety(Vector3D(0.05f, 0.8f, 0.15f));
            myEngine.updateMvMatrix();
            myEngine.setFlatColor(0.9f, 0.9f, 0.9f);
            meshCube->draw();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
    }
}

void drawBody(GLBI_Engine& myEngine)
{
    // blue cylinder
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 15.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.1, 0.8, 1.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // blue thingy that ressembles a tailpipe
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 15.0f, -25.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.2, 0.4));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // rest of the body
    // blue box
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 30.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.0, 20.0, 10.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

}

void drawUpperBody(GLBI_Engine& myEngine) // draws everything but the face
{
    drawFace(myEngine);
    drawEyebrow(myEngine);
    drawMouth(myEngine);
    drawBody(myEngine);
}

void drawTrain(GLBI_Engine& myEngine)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 0.0, 5.0)); // moving it upwards
    myEngine.updateMvMatrix();
    drawUpperBody(myEngine); // everything but wheels
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    drawWheels(myEngine, 17.0, 7.0);
}