#include "json.hpp"
#include "circuit.hpp"

JsonData world_data;

// train moves parameters
int trainCellIndex {0}; // index of cells in json file
float trainProgress {0.0f}; // 0.0 = just entered cell, 1.0 = moving to next cell
float trainSpeed {0.03f}; // how much trainProgress is increased each step

JsonData loadJson(const std::string& path) // stores data from json file in struct JsonData
{
    std::ifstream f(path);

    // debug
    if (!f.is_open()) 
    {
        std::cerr << "Failed to open: " << path << std::endl;
        return JsonData{};
    }
    
    // read json as string
    std::string content((std::istreambuf_iterator<char>(f)),
                         std::istreambuf_iterator<char>());
    
    try
    {
        nlohmann::json data = nlohmann::json::parse(content);

        JsonData result;
        // fetching simple values : 
        result.squareSize = data["size_grid"];
        result.train = RailCellCoord {data["train"][0], data["train"][1]};
        result.light = RailCellCoord {data["light"][0], data["light"][1]};
        result.kenny = RailCellCoord {data["kenny"][0], data["kenny"][1]};
        result.train_station = RailCellCoord {data["train_station"][0], data["train_station"][1]};
 
        // fetching coordinates of rails :
        for (auto& pos : data["path"]) // all positions where rails should be put 
        {
            result.cells.push_back({pos[0], pos[1]});
        }

        return result;
    } 
    catch (const std::exception& e) // if it didnt work
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return JsonData{};
    }
}

void initCircuit(const std::string& path)
{
    world_data = loadJson(path);
}

void initTrainIndex()
{
    int n = world_data.cells.size();

    for (int i = 0; i < n; i++)
    {
        if (world_data.cells[i].x == world_data.train.x &&
            world_data.cells[i].y == world_data.train.y)
        {
            trainCellIndex = i;
            break;
        }
    }
}

RailChoice getRailType(RailCellCoord pos, RailCellCoord previousious, RailCellCoord next)
{
    int inX  = pos.x - previousious.x;
    int inY  = pos.y - previousious.y;
    int outX = next.x - pos.x;
    int outY = next.y - pos.y;

    if (abs(inX) > 1 || abs(inY) > 1 || abs(outX) > 1 || abs(outY) > 1)
    {
        return RailChoice::straightHoriz;
    }

    // straight rails
    if (inX == outX && inY == outY)
    {
        return (inX != 0) ? RailChoice::straightHoriz : RailChoice::straightVert;
    }
    // curved rails
    if (inX ==  1 && outY ==  1) return RailChoice::curvedTopRight;
    if (inX ==  1 && outY == -1) return RailChoice::curvedBottomRight;
    if (inX == -1 && outY ==  1) return RailChoice::curvedTopLeft;
    if (inX == -1 && outY == -1) return RailChoice::curvedBottomLeft;
    if (inY ==  1 && outX ==  1) return RailChoice::curvedTopRight;
    if (inY ==  1 && outX == -1) return RailChoice::curvedTopLeft;
    if (inY == -1 && outX ==  1) return RailChoice::curvedBottomRight;
    if (inY == -1 && outX == -1) return RailChoice::curvedBottomLeft;

    return RailChoice::straightHoriz; // default
}

float curvedAngle(RailChoice type) // choice of the angle for curved rails
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
        default: 
            return 0.0f;
    }
}

void drawCircuit(GLBI_Engine& myEngine, Rail& rails)
{
    std::vector<RailCellCoord> cells {world_data.cells};
    int squareSize {world_data.squareSize};
    int n {(int)cells.size()};

    for (int i {0}; i < n; i++) 
    {
        // making sure the circuit closes
        RailCellCoord previousious = cells[(i - 1 + n) % n];
        RailCellCoord current = cells[i];
        RailCellCoord next = cells[(i + 1) % n];

        // converting coordinates in 3D world (based on grid)
        float posX = current.x * squareSize;
        float posY = current.y * squareSize;

        // identifying rail type
        RailChoice type = getRailType(current, previousious, next);

        // drawing rail
        if (type == RailChoice::straightHoriz || type == RailChoice::straightVert)
        {
            myEngine.mvMatrixStack.pushMatrix();

            if (type == RailChoice::straightHoriz)
            {
                myEngine.mvMatrixStack.addTranslation(Vector3D(posX + squareSize, posY, 0.0f));
                myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(0.0f, 0.0f, 1.0f));
            }
            else // straightVert
            {
                myEngine.mvMatrixStack.addTranslation(Vector3D(posX, posY, 0.0f));
            }

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

// train following circuit 
void trainProgression() // how the train moves between squares
{
    trainProgress += trainSpeed; // increasing its speed

    if (trainProgress >= 1.0f) // moving to the next cell
    {
        trainProgress = 0; // reseting the progression
        trainCellIndex = (trainCellIndex + 1) % world_data.cells.size(); // modulo for borders
    }
}

void trainMoves(float& posX, float& posY, float& angle)
{
    int n {(int)world_data.cells.size()};
    int squareSize {world_data.squareSize};
    
    RailCellCoord previous {world_data.cells[(trainCellIndex - 1 + n) % n]};
    RailCellCoord current {world_data.cells[trainCellIndex]};
    RailCellCoord next {world_data.cells[(trainCellIndex + 1) % n]};

    // calculating middles of previous;current segment and current;next segment (on x and y) and converting it to world coordinates
    // we add half a squareSize so that the train is centered inside the square since rails are centered inside squares of grid
    float fromX {(previous.x + current.x) / 2.0f * squareSize + squareSize / 2.0f};
    float fromY {(previous.y + current.y) / 2.0f * squareSize + squareSize / 2.0f};
    float toX {(current.x + next.x) / 2.0f * squareSize + squareSize / 2.0f};
    float toY {(current.y + next.y) / 2.0f * squareSize + squareSize / 2.0f};

    // direction of the train
    float dirX {toX - fromX};
    float dirY {toY - fromY};

    // new position of the train with speed
    posX = fromX + trainProgress * dirX;
    posY = fromY + trainProgress * dirY;

    // angle with x axis
    angle = atan2(dirY, dirX) + M_PI/2 ; // y/x + 90 degrees so that its facing the correct way

}

void drawElements(GLBI_Engine& myEngine, Rail& rails)
{
    RailCellCoord kenny {world_data.kenny};
    RailCellCoord train {world_data.train};
    RailCellCoord light {world_data.light};
    RailCellCoord train_station {world_data.train_station};

    float trainX, trainY, angle;
    trainMoves(trainX, trainY, angle);


    // drawing all elements at coordinates indicated in json file
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.updateMvMatrix();
    //myEngine.mvMatrixStack.addTranslation(Vector3D(train.x*world_data.squareSize, train.y*world_data.squareSize, rails.sr+rails.rr));
    myEngine.mvMatrixStack.addTranslation(Vector3D(trainX, trainY, rails.sr+rails.rr));
    myEngine.mvMatrixStack.addRotation(angle, Vector3D(0.0f, 0.0f, 1.0f));
    drawPositionnedTrain(myEngine, 0.0f, 0.0f);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.updateMvMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.4, 0.4, 0.4));
    myEngine.mvMatrixStack.addTranslation(Vector3D(kenny.x*world_data.squareSize, kenny.y*world_data.squareSize, -1.0f)); // moving the axis to the center of the model so we can rotate around the center of the model after
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(0.0, 0.0, 1.0));
    drawKenny(myEngine, 0.0f, 0.0f, 0.0f);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.updateMvMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(train_station.x*world_data.squareSize, train_station.y*world_data.squareSize, 0.0)); // same thing
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(0.0, 0.0, 1.0));
    drawTrainStation(myEngine, 0.0f, 0.0f);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.updateMvMatrix();
    drawStreetlight(myEngine, light.x*world_data.squareSize, light.y*world_data.squareSize);
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}
