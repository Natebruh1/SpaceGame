#pragma once
#include "node.h"
#include "FastNoiseLite.h"

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
private:
    // Environment Details
    int worldHeight = 8;
    int worldFlatness = 32;

    //Noises
    FastNoiseLite* HeightNoise = new FastNoiseLite(seed);



    //For Functions
    std::vector<int>* generatedVector;
};

