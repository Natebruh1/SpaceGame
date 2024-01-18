#pragma once
#include "node.h"
#include "FastNoiseLite.h"
#include <map>
#include <string>
//Forward Declaration
class terrain;
class dynamic;


struct  ivec2
{
    int x = 0;
    int y = 0;
    bool operator<(const ivec2& o) const
    {
        return o.x < x && o.y < y;
    }
};
class world :
    public node
{
public:
    world();
    ~world();
    int seed = 1;
    int genHeight(int x);
    std::vector<int>* genHeight(int x, std::vector<int>* map);
    std::vector<int>* genHeight(int x, int length);

    std::vector<terrain*>* worldMap;

    void render() override;

    void begin();

    void RegisterDynamic(dynamic* obj);
    void DeregisterDynamic(dynamic* obj);

    std::vector<terrain*> GetCurrentTerrainFromDynamic();
private:
    // Environment Details
    int worldHeight = 8;
    int worldFlatness = 32;

    //Noises
    FastNoiseLite* HeightNoise = new FastNoiseLite(seed);

   
    std::map<std::string, terrain*> worldMapHash;

    //For Functions
    std::vector<int>* generatedVector;

    std::vector<dynamic*> worldDynamics;
};

