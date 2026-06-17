#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

// init functions
void initFace();

void initMouth();

void initEyebrow();

void initWheel();

void initTrain();

// draw functions
void drawMouth(GLBI_Engine& myEngine);

void drawEyebrow(GLBI_Engine& myEngine);

void drawBody(GLBI_Engine& myEngine);

void drawFace(GLBI_Engine& myEngine);

void drawUpperBody(GLBI_Engine& myEngine);

void drawTire(GLBI_Engine& myEngine, float posX, float posY);

void drawTrain(GLBI_Engine& myEngine);

void drawPositionnedTrain(GLBI_Engine& myEngine, float posX, float posY);