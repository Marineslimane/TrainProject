#include "train_station.hpp"

const float W {30.0f}; // largeur
const float D {20.0f}; // profondeur  
const float H {20.0f}; // hauteur

// Couleurs
const float WALL_R  {0.5f},  WALL_G  {0.7f},  WALL_B  {0.8f};  // bleu
const float ROOF_R  {0.7f},  ROOF_G  {0.75f}, ROOF_B  {0.4f};  // vert kaki
const float AWNING_R{0.7f},  AWNING_G{0.5f},  AWNING_B{0.7f};  // mauve
const float PILLAR_R{0.6f},  PILLAR_G{0.4f},  PILLAR_B{0.3f};  // marron
const float BASE_R  {0.55f}, BASE_G  {0.75f}, BASE_B  {0.85f}; // bleu clair
const float DOOR_R  {0.3f},  DOOR_G  {0.5f},  DOOR_B  {0.3f};  // vert foncé
const float BENCH_R {0.8f},  BENCH_G {0.8f},  BENCH_B {0.85f}; //gris

void drawBox(float cx, float cy, float cz,
             float sx, float sy, float sz,
             float r,  float g,  float b)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(cx, cy, cz));
    myEngine.mvMatrixStack.addHomothety(Vector3D(sx, sy, sz));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(r, g, b);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();
}

void drawTrainStation(float posX, float posY)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 0.0f));
    myEngine.updateMvMatrix();

    //quai
    drawBox(W/2, D/2, 0.5f, W+4, D+4, 1.0f, BASE_R, BASE_G, BASE_B);

    //murs
    drawBox(W/2, D/2, H/2, W, D, H, WALL_R, WALL_G, WALL_B);

    // Toit 
    // Partie gauch
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(3*W/4, D/2, H + 3.0f));
    myEngine.mvMatrixStack.addRotation(0.5f, Vector3D(0.0f, 1.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(W/2 + 2, D + 2, 0.5f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(ROOF_R, ROOF_G, ROOF_B);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();
    // Partie droite
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(W/4, D/2, H + 3.0f));
    myEngine.mvMatrixStack.addRotation(-0.5f, Vector3D(0.0f, 1.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(W/2 + 2, D + 2, 0.5f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(ROOF_R, ROOF_G, ROOF_B);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();

    //Auvent
    drawBox(W/2, -3.0f, H * 0.7f, W, 6.0f, 1.0f, AWNING_R, AWNING_G, AWNING_B);

    //Colonne gauche
    drawBox(W * 0.25f, -3.0f, H * 0.35f, 1.5f, 1.5f, H * 0.7f, PILLAR_R, PILLAR_G, PILLAR_B);

    //Colonne droite
    drawBox(W * 0.75f, -3.0f, H * 0.35f, 1.5f, 1.5f, H * 0.7f, PILLAR_R, PILLAR_G, PILLAR_B);

    //Porte
    drawBox(W/2, 0.0f, H * 0.3f, W * 0.15f, 0.3f, H * 0.6f,DOOR_R, DOOR_G, DOOR_B);

    //Banc
    drawBox(W * 0.2f, D * 0.8f, 2.0f, W * 0.25f, D * 0.1f, 1.0f, BENCH_R, BENCH_G, BENCH_B);

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}