#include "world.h"

world::world()
{
    HeightNoise->SetFrequency(0.015);
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
