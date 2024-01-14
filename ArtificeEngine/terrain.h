#pragma once
#include "node2d.h"

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
        ret->push_back(rand()%3);
        return ret;
    }
};



class terrain :
    public node2d
{
public:
    terrain();
    ~terrain();
    block** blocks;
    void render() override;
    
    void chunkUpdate();
    void blockUpdate(glm::ivec2 coords, block b);
private:
    TileMap* map;
    glm::ivec2 chunkID;
};

