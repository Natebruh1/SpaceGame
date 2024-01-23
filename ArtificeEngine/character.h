#pragma once
#include "dynamic.h"
#include "world.h"
#include "terrain.h"
#include "sprite.h"
struct rect
{
    float width = 0.0;
    float height = 0.0;
};


class character :
    public dynamic
{
public:
    character();
    virtual void update() override;
    bool colliding();
    bool colliding(glm::vec2 extraVec);
    glm::vec2 resolveCollision(rect bounds,std::vector<glm::vec2> staticCollision);
    glm::vec2 resolveCollision(rect bounds, std::vector<glm::vec2> staticCollision, float scale);
private:
    glm::vec2 velocity = glm::vec2(0.f, 0.f);
    glm::vec2 accel = glm::vec2(0.f, 0.f);
    float speed;

    rect hitbox = {32.f,64.f};

    sprite* internalSprite;
};

