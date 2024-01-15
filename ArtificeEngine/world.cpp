#include "world.h"

world::world()
{
    HeightNoise->SetFrequency(0.015);
}

world::~world()
{
    delete generatedVector;
}

int world::genHeight(int x)
{
    return (int)(HeightNoise->GetNoise((float)x, 0.f))*worldHeight;
}

std::vector<int>* world::genHeight(int x, std::vector<int>* map)
{
    for (int i = 0; i < map->size();i++) // For column in map
    {
        (*map)[i] = (int)(HeightNoise->GetNoise((float)x + i, 0.f)) * worldHeight;
    }
    return map;
}

std::vector<int>* world::genHeight(int x, int length)
{
    delete generatedVector;
    generatedVector = new std::vector<int>(length);
    for (int i = 0; i < length; i++) // For column in map
    {
        (*generatedVector)[i] = (int)(HeightNoise->GetNoise((float)x + i, 0.f)) * worldHeight;
    }
    return generatedVector;
}
