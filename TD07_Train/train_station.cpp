#include "train_station.hpp"

const float W {30.0f};
const float D {20.0f};
const float H {20.0f};

//Couleurs
const float WALL_R  {0.38f},  WALL_G  {0.27f}, WALL_B  {0.08f}; // marron fonce
const float PLANK_R {0.73f}, PLANK_G {0.52f},  PLANK_B {0.21f};  //marron
const float ROOF_R  {0.38f},  ROOF_G  {0.27f}, ROOF_B  {0.08f};  // marron fonce
const float AWNING_R{0.75f}, AWNING_G{0.55f}, AWNING_B{0.65f}; // mauve
const float PILLAR_R{0.65f}, PILLAR_G{0.45f}, PILLAR_B{0.35f}; // marron
const float BASE_R  {0.38f},  BASE_G  {0.27f},  BASE_B  {0.08f}; // bleu-vert clair
const float DOOR_R  {0.6f},  DOOR_G  {0.65f}, DOOR_B  {0.4f};  // vert kaki clair
const float FENCE_R {0.7f},  FENCE_G {0.55f}, FENCE_B {0.65f}; // mauve clair
const float SIGN_R  {0.55f}, SIGN_G  {0.7f},  SIGN_B  {0.75f}; // bleu-vert
const float WIN_R   {0.55f}, WIN_G   {0.65f}, WIN_B   {0.8f}; 

void drawBox(float cx, float cy, float cz, float sx, float sy, float sz, float r,  float g,  float b)
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

    //Quai
    drawBox(W/2, 1.0f, 0.75f, W + 4, D + 5, 1.5f, BASE_R, BASE_G, BASE_B);

    //Murs
    drawBox(W/2, D/2, H/2, W, D, H, WALL_R, WALL_G, WALL_B);

    //Planches
    //Mur avant
    int nb_planches = 10;
    float planche_h = H / nb_planches;
    for (int i = 0; i < nb_planches; i++) {
        float z = planche_h * i + planche_h/2.0f;
        // Planche mur avant
        drawBox(W/2, -0.1f, z, W + 0.2f, 0.3f, planche_h * 0.85f, PLANK_R, PLANK_G, PLANK_B);
        // Planche mur arrière
        drawBox(W/2, D + 0.1f, z, W + 0.2f, 0.3f, planche_h * 0.85f, PLANK_R, PLANK_G, PLANK_B);
        // Planche mur gauche
        drawBox(-0.1f, D/2, z, 0.3f, D + 0.2f, planche_h * 0.85f, PLANK_R, PLANK_G, PLANK_B);
        // Planche mur droit
        drawBox(W + 0.1f, D/2, z, 0.3f, D + 0.2f, planche_h * 0.85f, PLANK_R, PLANK_G, PLANK_B);
    }

    //toit
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(3*W/4 + 1.0f, D/2, H + 4.0f));
    myEngine.mvMatrixStack.addRotation(0.5f, Vector3D(1.0f, 0.0f, 0.0f));
    myEngine.mvMatrixStack.addHomothety(Vector3D(W+6, D + 4, 0.8f));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-0.25f,-0.1f,1.1f));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(ROOF_R, ROOF_G, ROOF_B);
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();

    //planche toit
    drawBox(W/2, D/2, H + 7.5f, 1.0f, D + 4, 1.0f, ROOF_R * 0.8f, ROOF_G * 0.8f, ROOF_B * 0.8f);
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(0.5f, Vector3D(1.0f, 0.0f, 0.0f));
    meshCube->draw();
    myEngine.mvMatrixStack.popMatrix();

    //Auvent
    drawBox(W/2, -5.0f, H * 0.72f, W * 0.8f, 8.0f, 1.2f, AWNING_R, AWNING_G, AWNING_B);

    //pillier
    //Pillier G
    drawBox(W * 0.28f, -5.0f, H * 0.36f, 2.0f, 2.0f, H * 0.72f, PILLAR_R, PILLAR_G, PILLAR_B);
    //Pillier D
    drawBox(W * 0.72f, -5.0f, H * 0.36f, 2.0f, 2.0f, H * 0.72f, PILLAR_R, PILLAR_G, PILLAR_B);

    //Porte
    drawBox(W * 0.55f, -0.2f, H * 0.32f, W * 0.2f, 0.4f, H * 0.62f, DOOR_R, DOOR_G, DOOR_B);

    //Fenetre
    //Cadre
    drawBox(-0.2f, D * 0.4f, H * 0.55f, 0.4f, D * 0.25f, H * 0.2f, SIGN_R, SIGN_G, SIGN_B);

    //Panneau
    //Support
    drawBox(W * 0.25f, -0.3f, H * 0.72f, W * 0.15f, 0.4f, 0.5f, SIGN_R, SIGN_G, SIGN_B);
    //Panneau
    drawBox(W * 0.25f, -0.3f, H * 0.62f, W * 0.12f, 0.4f, H * 0.12f, WIN_R, WIN_G, WIN_B);

    //barriere
    drawBox(W * 0.3f, -6.5f, 4.5f, W * 0.5f, 0.6f, 0.6f, FENCE_R, FENCE_G, FENCE_B);
    //Poteaux barrière
    int nb_poteaux = 8;
    for (int i = 0; i < nb_poteaux; i++) {
        float px = W * 0.05f + i * (W * 0.5f / (nb_poteaux - 1));
        drawBox(px, -6.5f, 2.0f, 0.5f, 0.5f, 4.0f, FENCE_R, FENCE_G, FENCE_B);
    }

    //Chaise gauche
    drawBox(W * 0.33f, -4.5f, 2.5f, W * 0.08f, D * 0.08f, 0.4f, FENCE_R, FENCE_G, FENCE_B);
    drawBox(W * 0.33f, -4.5f, 1.5f, 0.4f, 0.4f, 2.5f, FENCE_R, FENCE_G, FENCE_B);
    //Chaise droite
    drawBox(W * 0.57f, -4.5f, 2.5f,  W * 0.08f, D * 0.08f, 0.4f, FENCE_R, FENCE_G, FENCE_B);
    drawBox(W * 0.57f, -4.5f, 1.5f, 0.4f, 0.4f, 2.5f, FENCE_R, FENCE_G, FENCE_B);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}