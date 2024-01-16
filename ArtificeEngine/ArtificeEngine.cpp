// ArtificeEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "node.h"
#include "sprite.h"
#include "TileMap.h"
#include "terrain.h"

#include "ResourceManager.h"
#include "Shader.h"
#include "globals.h"
#include <vector>
#include <algorithm>

GLFWwindow* window;

terrain* d;
glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
void init();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_callback(GLFWwindow* window, int button, int action, int mods);

void render();
void pollEvents();
void input(GLFWwindow* currentContext);

void initGame();
std::vector<node*>* GetSceneNodes();

int main()
{
    //Initialise
    init();
    
    while (!glfwWindowShouldClose(window))
    {
        input(window);
        render();
        pollEvents();

        //Swap Back Buffers
        glfwSwapBuffers(window);
    }
    //No longer rendering

    glfwTerminate();
    return 0;
    
}




void init()
{
    //Init opengl
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //Create the window
    window = glfwCreateWindow(1280, 720, "Artifice Project", NULL, NULL);
    if (window == NULL)
    {
        //Throw error
        std::cout << "Failed to create window" << std::endl;
        //Terminate glfw
        glfwTerminate();
        

    }

    
    //make this window the current context
    glfwMakeContextCurrent(window);


    //Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, 1280, 720);
    glDisable(GL_DEPTH_TEST);

    //Add callback for resizing window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    //GAME SPECIFIC
    

    //LOAD SHADERS
    //Sprite
    ResourceManager::LoadShader("sprite.vs", "sprite.frag", nullptr, "sprite");
    (*ResourceManager::GetShader("sprite")).Use().SetInteger("image", 0);
    (*ResourceManager::GetShader("sprite")).SetMatrix4("projection", projection);
    //TileMap
    ResourceManager::LoadShader("TileMap.vs", "TileMap.frag", "TileMap.gs", "TileMap");
    (*ResourceManager::GetShader("TileMap")).Use().SetInteger("image", 0);
    (*ResourceManager::GetShader("TileMap")).SetMatrix4("projection", projection);

    

    ResourceManager::LoadTexture("cat.png", true, "cat");
    ResourceManager::LoadTexture("testTiles.png", true, "tiles");


    initGame();
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //Callback for resizing window
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (auto n : *GetSceneNodes())
    {
        n->input(key, scancode, action, mods);
    }
}

void cursor_callback(GLFWwindow* window, int button, int action, int mods)
{
    for (auto n : *GetSceneNodes())
    {
        n->input(button,action,mods);
    }
}

void render()
{
    
    //Objects Draw...
    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    


    // ADD STUFF HERE
    
    
    currentScene->call("render");
}



void pollEvents()
{
    glfwPollEvents();
}



void input(GLFWwindow* currentContext)
{
    //UPDATE MOUSE POSITION
    glfwGetCursorPos(window, &mouseX, &mouseY);


    //Close the Window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        block b = { 1,0,4 };
        d->blockUpdate(glm::ivec2(0, 0), b);
    }
      

    //Pass Input to children

}


void initGame()
{
    //Set the first scene
    /*sprite* s = new sprite();
    s->setTexture(ResourceManager::GetTexture("cat"));
    s->position = glm::vec2(100.0, 100.0);*/


    std::vector<terrain*> terrainMap(16);
    for (int i = 0; i < 16; i++)
    {
        switch (i % 2) {
        case 0:
            terrainMap[i] = new terrain((i / 2)-4, 0);
            break;
        case 1:
            terrainMap[i] = new terrain(((i-1)/ 2)-4, -1);
            break;
        }
        
        if (i > 0)
        {
            terrainMap[0]->add_child(terrainMap[i]);
        }
    }
    ;
    terrainMap[0]->position = glm::vec2(200.0, 200.0);
    currentScene = terrainMap[0];
}

std::vector<node*>* GetSceneNodes()
{
    std::vector<node*>* workingTree = new std::vector<node*>();
    std::vector<node*> searched;
    workingTree->push_back(currentScene);
    while (workingTree->size() != searched.size())
    {
        for (auto n : *workingTree)
        {
            if (std::find(searched.begin(), searched.end(), n) == searched.end())
            {
                std::vector<node*>* search = n->get_children();
                workingTree->insert(workingTree->end(), search->begin(), search->end());
                searched.push_back(n);
            }
            
            
        }
        

    }
    
    return workingTree;
}
