#include "train_station.hpp"

const float W {30.0f};
const float D {20.0f};
const float H {20.0f};

//Couleurs
const float WALL_R  {0.502f},  WALL_G  {0.38f}, WALL_B  {0.204f};
const float PLANK_R {0.65f}, PLANK_G {0.51f},  PLANK_B {0.3f};
const float BASE_R{0.329f}, BASE_G{0.294f}, BASE_B{0.243f};

STP3D::IndexedMesh* meshPillar = nullptr;
STP3D::IndexedMesh* meshSphere2 = nullptr;
STP3D::StandardMesh* meshRect = nullptr;
STP3D::IndexedMesh* meshPost = nullptr;
STP3D::IndexedMesh* meshCube2 = nullptr;

void initTrainStation()
{
    meshPillar = STP3D::basicCylinder(H * 0.72f, 1.2f, 16);
    meshPillar->createVAO();
    meshSphere2 = STP3D::basicSphere(1.5f, 8, 8);
    meshSphere2->createVAO();
    meshPost = STP3D::basicCylinder(3.5f, 0.3f, 8);
    meshPost->createVAO();
    meshCube2 = STP3D::basicCube(1.0f);
    meshCube2->createVAO();
}

void drawBox(GLBI_Engine& myEngine, float cx, float cy, float cz,
             float sx, float sy, float sz,
             float r, float g, float b)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(cx, cy, cz));
    myEngine.mvMatrixStack.addHomothety(Vector3D(sx, sy, sz));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(r, g, b);
    meshCube2->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawCylinder(GLBI_Engine& myEngine, float cx, float cy, float cz, float r, float g, float b)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(cx, cy, cz));
    myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(r, g, b);
    meshPillar->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawTrainStation(GLBI_Engine& myEngine, float posX, float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 0.0f));
    myEngine.mvMatrixStack.addRotation(M_PI/6 , Vector3D(0.0f, 0.0f, 1.0f));
    myEngine.mvMatrixStack.addHomothety(10.0f / W); 
    myEngine.updateMvMatrix();

    //quai
    drawBox(myEngine, -3.0f + (W+6)/2.0f, (D+8)/2.0f - 9.0f, 0.0f,W+6, D+8, 2.0f,BASE_R, BASE_G, BASE_B);
    //murs
    drawBox(myEngine, W/2, D/2, H/2, W, D, H, WALL_R, WALL_G, WALL_B);
    //planches
    int nb_planches = 12;
    float planche_h = H / nb_planches;
    for (int i = 0; i < nb_planches; i++) {
        float z = planche_h * i + planche_h / 2.0f;
        drawBox(myEngine, W/2,   -0.1f, z, W+0.2f,   0.3f, planche_h*0.8f, PLANK_R, PLANK_G, PLANK_B);
        drawBox(myEngine, W/2, D+0.1f, z, W+0.2f,   0.3f, planche_h*0.8f, PLANK_R, PLANK_G, PLANK_B);
        drawBox(myEngine, -0.1f,  D/2, z,   0.3f, D+0.2f, planche_h*0.8f, PLANK_R, PLANK_G, PLANK_B);
        drawBox(myEngine, W+0.1f, D/2, z,   0.3f, D+0.2f, planche_h*0.8f, PLANK_R, PLANK_G, PLANK_B);
    }

    //toit
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(3*W/4+1, D/2, H+4));
    myEngine.mvMatrixStack.addRotation(0.5f, Vector3D(0.0f, 1.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(W/2+4, D+4, 0.8f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(PLANK_R, PLANK_G, PLANK_B);
    meshCube2->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(W/4-1, D/2, H+4));
    myEngine.mvMatrixStack.addRotation(-0.5f, Vector3D(0.0f, 1.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(W/2+4, D+4, 0.8f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(PLANK_R, PLANK_G, PLANK_B);
    meshCube2->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    //faitiere
    drawBox(myEngine, W/2, D/2, H+7.5f, 1.0f, D+4, 1.0f,
            PLANK_R*0.8f, PLANK_G*0.8f, PLANK_B*0.8f);

    //sphere
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(W/2, D/2, H+9.0f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(PLANK_R*0.7f, PLANK_G*0.7f, PLANK_B*0.3f);
    meshSphere2->draw();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    //auvent
    drawBox(myEngine, W/2, -3.0f, H*0.75f, W*0.85f, 6.0f, 1.5f, BASE_R, BASE_G, BASE_B);

    //colonnes
    drawCylinder(myEngine, W*0.25f, -4.0f, 0.0f, WALL_R, WALL_G, WALL_B);
    drawCylinder(myEngine, W*0.75f, -4.0f, 0.0f, WALL_R, WALL_G, WALL_B);

    //porte
    drawBox(myEngine, W/2, -0.3f, H*0.3f, W*0.18f, 0.5f, H*0.6f, BASE_R, BASE_G, BASE_B);

    //barriere
    //Barre horizontale
    drawBox(myEngine, W*0.30f, -7.0f, 3.5f, W*0.65f, 0.5f, 0.5f, WALL_R, WALL_G, WALL_B);
    
    //poteaux
    for (int i = 0; i < 8; i++) {
        float px = W*0.05f + i*(W*0.55f/7.0f);
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addTranslation(Vector3D(px, -7.0f, 0.0f));
        myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1.0f, 0.0f, 0.0f));
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(WALL_R, WALL_G, WALL_B);
        meshPost->draw();
        myEngine.mvMatrixStack.popMatrix();
        myEngine.updateMvMatrix();
    }

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}