#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "glbasimac/glbi_texture.hpp"
using namespace glbasimac;

/* Camera parameters and functions */
static const float Z_NEAR {0.1f};
static const float Z_FAR {500.f};
extern float angle_theta;      // Angle between x axis and viewpoint
extern float angle_phy  ;      // Angle between z axis and viewpoint
extern float dist_zoom  ;      // Distance between origin and viewpoint
extern STP3D::IndexedMesh* meshCube;
extern STP3D::IndexedMesh* meshCylinder;

extern float cam_x, cam_y, cam_z;
extern float cam_angle;
extern bool lightingEnabled;
extern float cam_pitch;

/* OpenGL Engine */
extern GLBI_Engine myEngine;
extern STP3D::StandardMesh* groundMesh;
// init functions
void initSquare();

void initScene();

// draw functions
void drawGrid();

void drawScene();
