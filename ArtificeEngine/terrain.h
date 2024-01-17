#pragma once
#include "node2d.h"
#include "world.h"
#include "globals.h"

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "ResourceManager.h"
#include <stdlib.h> 
#include "TileMap.h"
const int CHUNK_SIZE = 64;
struct block
{
    int x=0;
    int y=0;
    int tile = 0;
    std::vector<int>* returnVertex()
    {
        std::vector<int>* ret = new std::vector<int>();
        ret->push_back(x);
        ret->push_back(y);
        ret->push_back(tile);
        return ret;
    }
};



class terrain :
    public node2d
{
public:
    terrain();
    terrain(int x, int y);
    terrain(glm::ivec2 coords);

    void genTerrain();

    ~terrain();
    block** blocks;
    
    std::vector<std::vector<glm::vec2>>* getCollisionVertices();
    glm::vec2 getPosition();
    
    void chunkUpdate();
    void blockUpdate(glm::ivec2 coords, block b);
    TileMap* map;
private:
    
    glm::ivec2 chunkID=glm::ivec2(0,0);
};

