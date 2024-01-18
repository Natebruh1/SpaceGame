#include "world.h"
#include "terrain.h"
#include "node2d.h"
#include "dynamic.h"

world::world()
{
    HeightNoise->SetFrequency(2);
    //HeightNoise->SetFractalGain(.5f);
    HeightNoise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    
}

world::~world()
{
    delete generatedVector;
}

int world::genHeight(int x)
{
    float val = (HeightNoise->GetNoise((float)(x)/(float)(worldFlatness*8), 2.f)) * worldHeight * 8;
    return (int)val;
}

std::vector<int>* world::genHeight(int x, std::vector<int>* map)
{
    for (int i = 0; i < map->size();i++) // For column in map
    {
        (*map)[i] = (int)(HeightNoise->GetNoise( ((float)(x) / (float)(worldFlatness*8)) + i, 0.f)) * worldHeight*8;
    }
    return map;
}

std::vector<int>* world::genHeight(int x, int length)
{
    delete generatedVector;
    generatedVector = new std::vector<int>(length);
    for (int i = 0; i < length; i++) // For column in map
    {
        (*generatedVector)[i] = (int)(HeightNoise->GetNoise( ((float)(x) / (float)(worldFlatness*8)) + i, 0.f)) * worldHeight*8;
    }
    return generatedVector;
}

void world::render()
{
    for (auto t : GetCurrentTerrainFromDynamic())
    {
        t->map->render();
    }
}

void world::begin()
{
    glm::ivec2* iv = new glm::ivec2(0,0);
    worldMap = new std::vector<terrain*>();
    for (int i = -2; i < 2; i++)
    {
        for (int j = -3; j < 1; j++)
        {
            terrain* newTerr = new terrain(i, j);
            worldMap->push_back(newTerr);
            std::string iv = std::to_string(i)+std::to_string(j);
            worldMapHash[iv] = newTerr;

        }
    }
}

void world::RegisterDynamic(dynamic* obj)
{
    if (std::find(worldDynamics.begin(), worldDynamics.end(), obj) == worldDynamics.end())
    {
        worldDynamics.push_back(obj);
    }
}

void world::DeregisterDynamic(dynamic* obj)
{
    auto it = std::find(worldDynamics.begin(), worldDynamics.end(), obj);
    if (it != worldDynamics.end())
    {
        worldDynamics.erase(it);
    }
}

std::vector<terrain*> world::GetCurrentTerrainFromDynamic()
{
    std::vector<terrain*> toRet;
    std::string iv;
    std::vector< glm::ivec2> chunksChecked;
    for (auto d : worldDynamics)
    {
        glm::vec2 currentPos=d->getWorldPosition();
        glm::ivec2 chunk = (glm::ivec2)glm::vec2(-currentPos.x / (64.f*16.f),currentPos.y / (64.f*16.f));
        //std::cout << chunk.x << " / " << chunk.y << std::endl;
        // 
        // 
        //NEED TO ADD CHECK FOR IF CURRENT CHUNK HAS BEEN DONE. IF IT HAS BEEN DONE THEN WE CAN SKIP THE BELOW FOR LOOP

        //IE IF 100 DYNAMICS ARE IN THE SAME CHUNK THEN IT ONLY DOES IT ONCE.
        if (std::find(chunksChecked.begin(), chunksChecked.end(), chunk) == chunksChecked.end())
        {


            for (int i = -2; i < 3; i++)
            {
                for (int j = -1; j < 1; j++)
                {
                    iv = std::to_string((chunk.x + glm::ivec2(i, j).x)) + std::to_string((chunk.y + glm::ivec2(i, j).y));

                    if (worldMapHash[iv] != nullptr) //If we've generated the terrain
                    {
                        if (std::find(toRet.begin(), toRet.end(), worldMapHash[iv]) == toRet.end()) // Make sure we aren't adding this to the return if its not already there
                        {
                            toRet.push_back(worldMapHash[iv]);  //Add it to the returns
                        }

                    }
                    else                                                          //Its nullptr
                    {
                        terrain* newTerr = new terrain(chunk + glm::ivec2(i, j)); //Create it
                        worldMap->push_back(newTerr);                             //Add it to the worldMap
                        worldMapHash[iv] = newTerr;         //Add it to the worldMapHash

                        toRet.push_back(worldMapHash[iv]);  //Add it to the returns
                    }

                }
            }
            chunksChecked.push_back(chunk);
        }
    }
    

    return toRet;
}
