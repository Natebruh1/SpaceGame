#pragma once
class node;
class node2d;
class world;
class camera;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

//Game Engine
extern node* currentScene;
extern float frameTime;


//OpenGL
extern double mouseX;
extern double mouseY;

//Game
extern world* currentWorld;

extern camera* currentCamera;
extern glm::mat4 projection;

float Distance(glm::vec2 a, glm::vec2 b);