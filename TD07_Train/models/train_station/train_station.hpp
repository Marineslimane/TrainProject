#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

void drawTrainStation(GLBI_Engine& myEngine, float posX, float posY);

void drawBox(GLBI_Engine& myEngine, float cx, float cy, float cz, float sx, float sy, float sz, float r, float g, float b);

void initTrainStation(); 