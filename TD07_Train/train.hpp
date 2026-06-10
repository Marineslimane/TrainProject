#pragma once

#include "glbasimac/GLBI_Engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/GLBI_Convex_2D_Shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

void initFace();

void initMouth();

void initEyebrow();

void initWheel();

void initTrain();

void drawMouth(GLBI_Engine& myEngine);

void drawEyebrow(GLBI_Engine& myEngine);

void drawBody(GLBI_Engine& myEngine);

void drawFace(GLBI_Engine& myEngine);

void drawUpperBody(GLBI_Engine& myEngine);

void drawTire(GLBI_Engine& myEngine, float posX, float posY);

void drawTrain(GLBI_Engine& myEngine);

void drawPositionnedTrain(GLBI_Engine& myEngine, float posX, float posY);