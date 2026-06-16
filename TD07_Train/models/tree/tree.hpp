#pragma once

#include "glbasimac/GLBI_Engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/GLBI_Convex_2D_Shape.hpp"
#include "tools/basic_mesh.hpp"

using namespace glbasimac;

void initTree();

void initBush();

void drawTree(GLBI_Engine& myEngine, float posX, float posY);

void drawBush(GLBI_Engine& myEngine, float posX, float posY);