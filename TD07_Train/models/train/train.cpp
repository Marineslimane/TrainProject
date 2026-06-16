#include "tools/basic_mesh.hpp"
#include "train.hpp"
#include "draw_scene.hpp"
STP3D::IndexedMesh* meshSphere;
STP3D::IndexedMesh* meshCylinder;
STP3D::IndexedMesh* meshCube3=nullptr;
STP3D::StandardMesh* meshRect2 = nullptr;

GLBI_Convex_2D_Shape eyebrow{3};
GLBI_Convex_2D_Shape mouth{3};

// colors
float lightGrey {0.85};
float darkGrey {0.8};
float blue {0.8};
float red {0.8};

void initFace()
{
    meshSphere = STP3D::basicSphere(5.8f, 60, 60); // radius, smoothness of vertical lines, smoothness of horizontal lines
    meshSphere->createVAO();

    meshCylinder = STP3D::basicCylinder(30, 5, 60, 1); // height, radius, div_round, div_height
    meshCylinder->createVAO();

    meshCube3 = STP3D::basicCube(1.0f);
    meshCube3->createVAO();
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
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 4.5f, 6.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(2.5, 3.0, 1.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(1.0, 1.0, 1.0);  
    mouth.drawShape();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // shadow
    myEngine.mvMatrixStack.pushMatrix();
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
    if (lightingEnabled) myEngine.switchToPhongShading();
    // left
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.25f, 4.5f, 13.25f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 1.0, 0.75));
    myEngine.mvMatrixStack.addRotation(-M_PI/12, Vector3D(0.0, 1.0, 0.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.0, 0.0, 0.0);
    myEngine.setNormalForConvex2DShape(Vector3D(0.0f, -1.0f, 0.0f));
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
    myEngine.setNormalForConvex2DShape(Vector3D(0.0f, -1.0f, 0.0f));
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

    // other elements
    // eyebrows
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.updateMvMatrix();   
    drawEyebrow(myEngine);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // mouth
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.updateMvMatrix();   
    drawMouth(myEngine);
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

void drawTire(GLBI_Engine& myEngine, float posX, float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(0.0, 0.0, 1.0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 4.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.82, 0.082, 0.82));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawWheels(GLBI_Engine& myEngine, float posX, float posY)
{
    int nb_rims {16}; // number of rectangles inside rims of wheels

    for (int i {0} ; i < 3 ; i++)
    {
        // left side wheels
        drawWheel(myEngine, posX + i*12.5, posY);
        drawTire(myEngine, posX + i*12.5, posY);
        // right side wheels
        drawWheel(myEngine, posX + i*12.5, -posY-2.5);
        drawTire(myEngine, posX + i*12.5,  -posY-2.5);

        // inside of wheels 
        // left side rim
        // sphere in center 
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(posY+1.5, posX+ i*12.5, 4.0f)); // sphere is not rotated compared to cylinder
        myEngine.mvMatrixStack.addHomothety(Vector3D(0.05, 0.25, 0.25)); // flattened on x
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0.f, 0.f, blue);
        meshSphere->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
        // line inside
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(posY+1.5, posX+ i*12.5, 4.0f)); // sphere is not rotated compared to cylinder
        myEngine.mvMatrixStack.addHomothety(Vector3D(0.06, 0.2, 0.2)); // flattened on x
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0.f, 0.f, blue+1);
        meshSphere->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
        // rectangles inside
        for (int j {0}; j < nb_rims; j++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(0.0, 0.0, 1.0));
            myEngine.mvMatrixStack.addTranslation(Vector3D(posX+ i*12.5, posY+1.5, 4.0f)); // same position as wheel
            myEngine.mvMatrixStack.addRotation((2*M_PI/nb_rims)*j, Vector3D(0.0, 1.0, 0.0)); // rotation around center of wheel
            myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 2.5f));
            myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(1.0, 0.0, 0.0)); // aligning them w the wheel
            myEngine.mvMatrixStack.addHomothety(Vector3D(0.08f, 3.0f, 0.25f));
            myEngine.updateMvMatrix();
            myEngine.setFlatColor(0.0, 0.0, blue);
            meshCube3->draw();
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }

        // right side rim
        // sphere in center 
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(-(posY+1.5), posX+ i*12.5, 4.0f)); // sphere is not rotated compared to cylinder
        myEngine.mvMatrixStack.addHomothety(Vector3D(0.05, 0.25, 0.25)); // flattened on x
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0.f, 0.f, blue);
        meshSphere->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
        // line inside
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(-(posY+1.5), posX+ i*12.5, 4.0f)); // sphere is not rotated compared to cylinder
        myEngine.mvMatrixStack.addHomothety(Vector3D(0.06, 0.2, 0.2)); // flattened on x
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0.f, 0.f, blue+1);
        meshSphere->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
        // rectangles inside
        for (int j {0}; j < nb_rims; j++)
        {
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(0.0, 0.0, 1.0));
            myEngine.mvMatrixStack.addTranslation(Vector3D(posX+ i*12.5, -(posY+1.5), 4.0f)); // same position as wheel
            myEngine.mvMatrixStack.addRotation((2*M_PI/nb_rims)*j, Vector3D(0.0, 1.0, 0.0)); // rotation around center of wheel
            myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, 0.0f, 2.5f));
            myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(1.0, 0.0, 0.0)); // aligning them w the wheel
            myEngine.mvMatrixStack.addHomothety(Vector3D(0.08f, 3.0f, 0.25f));
            myEngine.updateMvMatrix();
            myEngine.setFlatColor(0.0, 0.0, blue);
            meshCube3->draw();
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

    // red stripes
    int nb_stripes {6};

    for (int i {} ; i < nb_stripes ; i++)
    {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(0, 19+i*4, 9.3f));
        myEngine.mvMatrixStack.addHomothety(Vector3D(1.0, 0.1, 1.2));
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(red, 0.f, 0.f);
        meshSphere->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
    }

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

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 25.0, 20.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.2, 0.355, 0.3));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawBodyBox(GLBI_Engine& myEngine)
{
    // blue box
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 33.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.0, 18.0, 10.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // red line inside
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 33.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.1, 17.0, 8.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 33.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.2, 16.2, 7.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // small blue box
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 22.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.0, 8.0, 5.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // red line inside 
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 22.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.1, 7.0, 4.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 22.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.2, 6.2, 3.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 26.0f, 10.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.2, 6.2, 3.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // blue box middle part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 42.5f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(12.0, 3.0, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // cabin
    // right pillars
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(4, 39.4f, 16.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.5, 0.8, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(4, 39.5f+2.08, 16.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.5, 0.8, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(4, 39.5f+8, 16.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.5, 0.8, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // left pillars
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-4, 39.4f, 16.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.5, 0.8, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-4, 39.5f+2.08, 16.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.5, 0.8, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-4, 39.5f+8, 16.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(1.5, 0.8, 7.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue+1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // roof
    // left part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-5.5, 39.5f+4, 19.f));
    myEngine.mvMatrixStack.addRotation(-M_PI/6, Vector3D(0.0, 1.0, 0.0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(10.0, 10.0, 0.5));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(5.5, 39.5f+4, 19.f));
    myEngine.mvMatrixStack.addRotation(M_PI/6, Vector3D(0.0, 1.0, 0.0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(10.0, 10.0, 0.5));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // middle part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 39.5f+4, 21.5f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(4.0, 10.0, 0.5));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // blue box 3
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 48.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.0, 8.0, 10.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // red line blue box 3
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 48.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.1, 7.0, 8.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 48.0f, 8.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(15.2, 6.2, 7.2));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, blue);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // black box
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 25.0f, 4.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(12.0, 25.0, 8.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // black box 2
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 30.0f, 2.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(12.0, 44.0, 3.0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // black box 3
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 30.0f, 0.5));
    myEngine.mvMatrixStack.addHomothety(Vector3D(12.0, 40.0, 3.5));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // red box
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 32.5f, 3.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(20, 40.0, 1.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // inclined red part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 10.5f, 2.0f));
    myEngine.mvMatrixStack.addRotation(M_PI/8, Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(20, 5, 1.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // rest of red part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 7.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(20, 4.5, 1.25));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // behind red part
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 51.85, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(20, 1.25, 3.75));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // front red cylinders
    // right
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(5, 2.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.1, 0.1, 0.1));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(5, 1.9f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.095, 0.095, 0.095));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // left
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-5, 2.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.1, 0.1, 0.1));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(red, 0.f, 0.f);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-5, 1.9f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.095, 0.095, 0.095));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.f, 0.f, 0.f);
    meshSphere->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    // bars on wheels
    // left
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(10, 30.0f, -2.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.5, 27.0, 0.7));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // inside part left
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(10, 30.0f, -2.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.51, 26.6, 0.64));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey-0.1, darkGrey-0.1, darkGrey-0.1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // right
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-10, 30.0f, -2.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.5, 27.0, 0.7));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey, darkGrey, darkGrey);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // inside part right
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-10, 30.0f, -2.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.51, 26.6, 0.64));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(darkGrey-0.1, darkGrey-0.1, darkGrey-0.1);
    meshCube3->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawUpperBody(GLBI_Engine& myEngine) // draws everything but wheels
{
    // raising cylinder body parts : 
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 0.0f, 0.8));
    myEngine.updateMvMatrix();
    drawFace(myEngine);
    drawBody(myEngine);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
    // rest of body : 
    drawBodyBox(myEngine);
}

void drawTrain(GLBI_Engine& myEngine)
{
    // rescaling entire train to fit one square of grid
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.3, 0.3));
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 0.0, 5.0)); // moving it upwards
    myEngine.updateMvMatrix();
    drawUpperBody(myEngine); // everything but wheels
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0, 0.0, 0.2)); // moving it upwards
    myEngine.updateMvMatrix();
    drawWheels(myEngine, 17.0, 7.0); // wheels
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawPositionnedTrain(GLBI_Engine& myEngine, float posX, float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX-5.0, posY, 0.0f));
    myEngine.updateMvMatrix();

    drawTrain(myEngine);

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}