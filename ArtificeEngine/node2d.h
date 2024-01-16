#pragma once
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "node.h"
//
// Node2d, able to rotate, scale and reposition.
//

// Class Tree : Node
//				 ||
//              Node2d
//               ^^



class node2d :
    public node
{
public:
    glm::vec2 position = glm::vec2(0.f, 0.f);
    glm::vec2 scale = glm::vec2(1.f, 1.f);
    float rotation = 0.0;

    glm::vec2 getWorldPosition();
    glm::vec2 getWorldScale();
    float getWorldRotation();

public:
    node2d() {}
    virtual ~node2d() {};
};

