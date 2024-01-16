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


world* currentWorld = new world();
camera* currentCamera = new camera();