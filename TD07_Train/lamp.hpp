#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "glbasimac/glbi_texture.hpp"

using namespace glbasimac;

void initLampadaire();
void initLampadaireLight(GLBI_Engine& myEngine, float posX, float posY, float posZ);
void drawLampadaire(GLBI_Engine& myEngine, float posX, float posY);