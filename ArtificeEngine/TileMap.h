#pragma once

#ifndef TILEMAP_RENDERER_H
#define TILEMAP_RENDERER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>
#include "texture.h"
#include "shader.h"
#include "node2d.h"
//
// A rendering node, pass a texture and some vertices and it will render a tilemap.
// To be added is using multiple textures
//

// Class Tree : Node
//				 ||
//              Node2d
//				 ||
//              TileMap

class TileMap :
    public node2d
{
public:
    // Constructor (inits shaders/shapes)
    TileMap(Shader& shader);
    TileMap();
    // Destructor
    ~TileMap();
    // Renders a defined quad textured with given sprite
    void render(Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    void render() override;

    void setTexture(Texture* tRef);

    void bindShader(Shader* shader);
    void bindShader();
    void addVertex(int addVert[3]);
    void addVertex(int* addVert, int size);
    void addVertex(std::vector<int>* pushV);
    void replaceVertex(std::vector<int>* pattern);
private:
    // Render state
    Shader       shader;
    unsigned int quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
    //
    Texture* internalTexture;
    std::vector<int> verticesToPass;
};


#endif