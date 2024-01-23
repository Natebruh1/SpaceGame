#include "globals.h"
#include "node.h"
#include "node2d.h"
#include "terrain.h"
#include "camera.h"
#include "world.h"



node* currentScene = nullptr;
float frameTime = 0.f;

double mouseX=0.0;
double mouseY=0.0;


world* currentWorld = nullptr;
camera* currentCamera = new camera();

glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

float Distance(glm::vec2 a, glm::vec2 b)
{
    float ret;
    ret = ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
    return ret;
}
