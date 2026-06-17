#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

void initTree();

void initBush();

void drawTree(GLBI_Engine& myEngine, float posX, float posY);

void drawBush(GLBI_Engine& myEngine, float posX, float posY);