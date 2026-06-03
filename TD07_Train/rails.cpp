#include "tools/basic_mesh.hpp"
#include "rails.hpp"

constexpr float Rail::rr;

void Rail::initCurvedRails()
{
    int nbTriangles {10}; // number of triangles used to draw rails

    // great rail
    std::vector<float> greatTopFaceVertices {};
    std::vector<float> greatBottomFaceVertices {};
    std::vector<float> greatLeftFaceVertices {};
    std::vector<float> greatRightFaceVertices {};

    float greatRadius {7.0};
    float smallRadius {(float)(7.0 - sr)};

    for (int i {0} ; i < nbTriangles ; i++)
    {
        float angle {i*(((float)M_PI/2)/nbTriangles)};

        // nb : no need to rotate triangles since TRIANGLE_STRIP automatically joins vertices
        // triangles along greatRadius
        greatTopFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatTopFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatTopFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius
        greatTopFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatTopFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatTopFaceVertices.push_back(rr+sr); // z coordinate

        // triangles along greatRadius
        greatBottomFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatBottomFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatBottomFaceVertices.push_back(rr); // z coordinate
        // triangles along smallRadius
        greatBottomFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatBottomFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatBottomFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius
        greatLeftFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatLeftFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatLeftFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius
        greatLeftFaceVertices.push_back(smallRadius*cos(angle)); // x coordinate
        greatLeftFaceVertices.push_back(smallRadius*sin(angle)); // y coordinate
        greatLeftFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius
        greatRightFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatRightFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatRightFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius
        greatRightFaceVertices.push_back(greatRadius*cos(angle)); // x coordinate
        greatRightFaceVertices.push_back(greatRadius*sin(angle)); // y coordinate
        greatRightFaceVertices.push_back(rr); // z coordinate
    }

    greatTopFace.initShape(greatTopFaceVertices);
    greatTopFace.changeNature(GL_TRIANGLE_STRIP);
    greatBottomFace.initShape(greatBottomFaceVertices);
    greatBottomFace.changeNature(GL_TRIANGLE_STRIP);
    greatLeftFace.initShape(greatLeftFaceVertices);
    greatLeftFace.changeNature(GL_TRIANGLE_STRIP);
    greatRightFace.initShape(greatRightFaceVertices);
    greatRightFace.changeNature(GL_TRIANGLE_STRIP);

    // small rail
    // nb : using same number of triangles for great and small rail

    std::vector<float> smallTopFaceVertices {};
    std::vector<float> smallBottomFaceVertices {};
    std::vector<float> smallLeftFaceVertices {};
    std::vector<float> smallRightFaceVertices {};

    float greatRadius2 {3.0};
    float smallRadius2 {3.0 - sr};

    for (int i {0} ; i < nbTriangles ; i++)
    {
        float angle {i*(((float)M_PI/2)/nbTriangles)};

        // nb : no need to rotate triangles since TRIANGLE_STRIP automatically joins vertices
        // triangles along greatRadius2
        smallTopFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallTopFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallTopFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius2
        smallTopFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallTopFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallTopFaceVertices.push_back(rr+sr); // z coordinate

        // triangles along greatRadius2
        smallBottomFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallBottomFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallBottomFaceVertices.push_back(rr); // z coordinate
        // triangles along smallRadius2
        smallBottomFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallBottomFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallBottomFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius2
        smallLeftFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallLeftFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallLeftFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius2
        smallLeftFaceVertices.push_back(smallRadius2*cos(angle)); // x coordinate
        smallLeftFaceVertices.push_back(smallRadius2*sin(angle)); // y coordinate
        smallLeftFaceVertices.push_back(rr); // z coordinate

        // triangles along greatRadius2
        smallRightFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallRightFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallRightFaceVertices.push_back(rr+sr); // z coordinate
        // triangles along smallRadius2
        smallRightFaceVertices.push_back(greatRadius2*cos(angle)); // x coordinate
        smallRightFaceVertices.push_back(greatRadius2*sin(angle)); // y coordinate
        smallRightFaceVertices.push_back(rr); // z coordinate
    }

    smallTopFace.initShape(smallTopFaceVertices);
    smallTopFace.changeNature(GL_TRIANGLE_STRIP);
    smallBottomFace.initShape(smallBottomFaceVertices);
    smallBottomFace.changeNature(GL_TRIANGLE_STRIP);
    smallLeftFace.initShape(smallLeftFaceVertices);
    smallLeftFace.changeNature(GL_TRIANGLE_STRIP);
    smallRightFace.initShape(smallRightFaceVertices);
    smallRightFace.changeNature(GL_TRIANGLE_STRIP);
}

void Rail::initStraightRails()
{
    meshCube = STP3D::basicCube(1.0f);
    meshCube->createVAO();
    meshCylinder = STP3D::basicCylinder(6.0f, rr, 32);
    meshCylinder->createVAO();
}

void Rail::drawStraightRail(GLBI_Engine& myEngine, float posX)
{
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, 5.0f, rr+sr));
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, 10.0f, sr));

    myEngine.updateMvMatrix();
    myEngine.setFlatColor(RAIL_R, RAIL_G, RAIL_B);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void Rail::drawBalast(GLBI_Engine& myEngine, const float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    
    myEngine.mvMatrixStack.addTranslation(Vector3D(8.0f, posY, rr));
    myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(0.0f, 0.0f, 1.0f));
    
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(BALAST_R, BALAST_G, BALAST_B);
    meshCylinder->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void Rail::drawStraightRails(GLBI_Engine& myEngine)
{
    drawStraightRail(myEngine, POS_X_RAIL1);
    drawStraightRail(myEngine, POS_X_RAIL2);

    float start = sr + rr;
    float end = 10.0f - sr - rr;
    float gap = (end - start) / 4.0f; // test
    for (int i = 0; i < 5; i++) { 
        float posY = start + i * gap;
        drawBalast(myEngine, posY);
    }
}

void Rail::drawCurvedRails(GLBI_Engine& myEngine)
{
    // great part
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addHomothety(Vector3D(1.5f, 1.5f, 1.5f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(RAIL_R, RAIL_G, RAIL_B);
    // drawing faces of the rail 
    greatTopFace.drawShape();
    greatBottomFace.drawShape();
    greatLeftFace.drawShape();
    greatRightFace.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // small part
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addHomothety(Vector3D(1.5f, 1.5f, 1.5f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(RAIL_R, RAIL_G, RAIL_B);
    // drawing faces of the rail 
    smallTopFace.drawShape();
    smallBottomFace.drawShape();
    smallLeftFace.drawShape();
    smallRightFace.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // // ballasts
    // myEngine.mvMatrixStack.pushMatrix();
    // myEngine.updateMvMatrix();
    // drawBalast(myEngine, posY);
    // myEngine.mvMatrixStack.popMatrix();
}

void Rail::drawStraightTrack(GLBI_Engine& myEngine, int nbRails, float startX, float startY, float squareSize)
{   
    for (int i = 0; i < nbRails; i++)
    {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(startX, startY + i * squareSize, 0.0f));
        myEngine.updateMvMatrix();
        drawStraightRails(myEngine);
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
    }
}