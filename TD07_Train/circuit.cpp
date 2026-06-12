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

void drawCircuit(GLBI_Engine& myEngine, Rail& rails)
{
    std::vector<TrackCell> cells {circuit.cells};
    int squareSize {circuit.squareSize};

    for (int i {0}; i < (int)cells.size(); i++) 
    {
        // converting coordinates in 3D world (based on grid)
        float posX = cells[i].x * squareSize;
        float posY = cells[i].y * squareSize;

        rails.drawStraightTrack(myEngine, 1, posX, posY, squareSize);
    }
}

