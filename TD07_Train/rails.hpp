#pragma once

#include "glbasimac/GLBI_Engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/GLBI_Convex_2D_Shape.hpp"
#include "tools/basic_mesh.hpp"

#include "circuit.hpp" // for RailChoice

using namespace glbasimac;

struct Rail
{
    // parameters
    static constexpr float sr {0.6f};
    static constexpr float rr {0.4f};
    static constexpr float POS_X_RAIL1 {3.0f};
    static constexpr float POS_X_RAIL2 {7.0f};

    // colors
    static constexpr float RAIL_R {0.6f}, RAIL_G {0.6f}, RAIL_B {0.6f};
    static constexpr float BALAST_R {0.55f}, BALAST_G {0.35f}, BALAST_B {0.1f};

    // meshes
    STP3D::IndexedMesh* meshCube {nullptr};
    STP3D::IndexedMesh* meshCylinder {nullptr};

    // curved rail shapes
    GLBI_Convex_2D_Shape greatTopFace{3};
    GLBI_Convex_2D_Shape greatBottomFace{3};
    GLBI_Convex_2D_Shape greatLeftFace{3};
    GLBI_Convex_2D_Shape greatRightFace{3};
    GLBI_Convex_2D_Shape smallTopFace{3};
    GLBI_Convex_2D_Shape smallBottomFace{3};
    GLBI_Convex_2D_Shape smallLeftFace{3};
    GLBI_Convex_2D_Shape smallRightFace{3};

    // methods
    // init 
    void initStraightRails();
    void initCurvedRails();
    // draw
    void drawStraightRail(GLBI_Engine& myEngine, float posX); // draws one rail
    void drawBalast(GLBI_Engine& myEngine, float posY);
    void drawStraightRails(GLBI_Engine& myEngine); // draws both rails
    void drawStraightTrack(GLBI_Engine& myEngine, int nbRails, float startX, float startY, float squareSize);
    void drawCurvedRails(GLBI_Engine& myEngine);
    void Rail::drawPositionnedCurvedRails(GLBI_Engine& myEngine, float posX, float posY, RailChoice type, float squareSize);
};
