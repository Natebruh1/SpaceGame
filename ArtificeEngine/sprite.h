#pragma once
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "camera.h"
#include "texture.h"
#include "shader.h"
#include "node2d.h"

//
// A rendering node, pass a texture and it will render a sprite at its default size (multiplied by scale)
// 


// Class Tree : Node
//				 ||
//              Node2d
//				 ||
//              Sprite

class sprite :
    public node2d
{
public:
    // Constructor (inits shaders/shapes)
    sprite(Shader& shader);
    sprite();
    // Destructor
    ~sprite();
    // Renders a defined quad textured with given sprite
    void render(Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    void render() override;

    void setTexture(Texture* tRef);

    void bindShader(Shader* shader);
    void bindShader();
private:
    // Render state
    Shader       shader;
    unsigned int quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
    //
    Texture* internalTexture;
};

#endif