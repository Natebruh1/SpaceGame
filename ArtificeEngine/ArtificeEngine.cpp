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
GLFWwindow* window;
node* currentScene;
glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
void init();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void render();
void pollEvents();
void input(GLFWwindow* currentContext);

void initGame();

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
    //Close the Window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //Pass Input to children
}


void initGame()
{
    //Set the first scene
    sprite* s = new sprite();
    s->setTexture(ResourceManager::GetTexture("cat"));
    s->position = glm::vec2(100.0, 100.0);


    terrain* d = new terrain();
    
    currentScene = d;
    d->position = glm::vec2(100.0, 100.0);
    d->add_child(s);
    
    
}