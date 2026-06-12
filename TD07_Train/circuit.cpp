#include "json.hpp"
#include "circuit.hpp"

CircuitData circuit;

CircuitData loadCircuit(const std::string& path) // stores data from json file in struct CircuitData
{
    std::ifstream f(path);

    // debug
    if (!f.is_open()) 
    {
        std::cerr << "Failed to open: " << path << std::endl;
        return CircuitData{};
    }
    
    // read json as string
    std::string content((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());
    
    try
    {
        nlohmann::json data = nlohmann::json::parse(content);
        CircuitData result;
        result.squareSize = data["size_grid"];

        for (auto& pos : data["path"]) // all positions where rails should be put 
        {
            result.cells.push_back({pos[0], pos[1]});
        }

        return result;
    } 
    catch (const std::exception& e) // if it didnt work
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return CircuitData{};
    }
}

void initCircuit(const std::string& path)
{
    circuit = loadCircuit(path);
}

RailChoice getRailType(RailCellCoord pos, RailCellCoord previous, RailCellCoord next)
{
    int inX  = pos.x - previous.x;
    int inY  = pos.y - previous.y;
    int outX = next.x - pos.x;
    int outY = next.y - pos.y;

    // straight
    if (inX == outX && inY == outY)
        return (inX != 0) ? RailChoice::straightHoriz : RailChoice::straightVert;

    // coming from left (inX=+1), going up (outY=+1) : bottom-left corner
    if (inX ==  1 && outY ==  1) return RailChoice::curvedBottomLeft;
    // coming from left (inX=+1), going down (outY=-1) : top-left corner  
    if (inX ==  1 && outY == -1) return RailChoice::curvedTopLeft;
    // coming from right (inX=-1), going up (outY=+1) : bottom-right corner
    if (inX == -1 && outY ==  1) return RailChoice::curvedBottomRight;
    // coming from right (inX=-1), going down (outY=-1) : top-right corner
    if (inX == -1 && outY == -1) return RailChoice::curvedTopRight;
    // coming from down (inY=+1), going right (outX=+1) : bottom-left corner
    if (inY ==  1 && outX ==  1) return RailChoice::curvedBottomLeft;
    // coming from down (inY=+1), going left (outX=-1) : bottom-right corner
    if (inY ==  1 && outX == -1) return RailChoice::curvedBottomRight;
    // coming from up (inY=-1), going right (outX=+1) : top-left corner
    if (inY == -1 && outX ==  1) return RailChoice::curvedTopLeft;
    // coming from up (inY=-1), going left (outX=-1) : top-right corner
    if (inY == -1 && outX == -1) return RailChoice::curvedTopRight;

    return RailChoice::straightHoriz;
}

float curvedAngle(RailChoice type)
{
    switch (type) 
    {
        case RailChoice::curvedTopRight : 
            return 0.0f; // default
        case RailChoice::curvedTopLeft: 
            return M_PI/2.0f;
        case RailChoice::curvedBottomLeft: 
            return M_PI;
        case RailChoice::curvedBottomRight: 
            return -M_PI/2.0f;
        default: return 0.0f;
    }
}

void drawCircuit(GLBI_Engine& myEngine, Rail& rails)
{
    std::vector<RailCellCoord> cells {circuit.cells};
    int squareSize {circuit.squareSize};
    int n {(int)cells.size()};

    for (int i {0}; i < n; i++) 
    {
        // making sure the circuit closes
        RailCellCoord previous = cells[(i - 1 + n) % n];
        RailCellCoord current = cells[i];
        RailCellCoord next = cells[(i + 1) % n];

        // converting coordinates in 3D world (based on grid)
        float posX = current.x * squareSize;
        float posY = current.y * squareSize;

        // identifying rail type
        RailChoice type = getRailType(current, previous, next);

         // add this:
        std::cout << "cell [" << current.x << "," << current.y << "] "
                << "in=(" << (current.x-previous.x) << "," << (current.y-previous.y) << ") "
                << "out=(" << (next.x-current.x) << "," << (next.y-current.y) << ") "
                << "type=" << (int)type << std::endl;
        // drawing rail
        if (type == RailChoice::straightHoriz || type == RailChoice::straightVert) // straight rail
        {
            float angle {0.0f}; // horizontal case

            if (type == RailChoice::straightVert)
            {
                angle = M_PI / 2.0f; 
            }
            
            myEngine.mvMatrixStack.pushMatrix();
            myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 0.0f));
            myEngine.mvMatrixStack.addRotation(angle, Vector3D(0.0f, 0.0f, 1.0f));
            myEngine.updateMvMatrix();
            rails.drawStraightRails(myEngine);
            myEngine.mvMatrixStack.popMatrix();
            myEngine.updateMvMatrix();
        }
       else // curved rail
        {
            rails.drawPositionnedCurvedRails(myEngine, posX, posY, type, squareSize);
        }
    }
}
