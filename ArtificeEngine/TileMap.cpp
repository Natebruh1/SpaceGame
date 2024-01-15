#include "TileMap.h"

TileMap::TileMap() 
{
	bindShader();
}

TileMap::~TileMap()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void TileMap::render(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    //test
    model = glm::mat4(1.0f);
    
    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector2f("mapSize", glm::ivec2(256, 256));

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_POINTS, 0, 6);
    glBindVertexArray(0);
}

void TileMap::render()
{
    if (verticesToPass.size() > 0)
    {
        //Update these to node2D variables
        glm::vec2 pos = getWorldPosition();
        float rotate = getWorldRotation();
        glm::vec2 size = getWorldScale();


        glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);

        // prepare transformations
        this->shader.Use();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(pos, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

        model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale


        //model = glm::mat4(1.0f);
        this->shader.SetMatrix4("model", model);

        // render textured quad
        this->shader.SetVector2i("mapSize", glm::ivec2(16, 16));

        glActiveTexture(GL_TEXTURE0);
        internalTexture->Bind();

        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_POINTS, 0, (verticesToPass.size()/3));
        glBindVertexArray(0);

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cout << "Error Found!" << std::endl;
        }
    }
    
}

void TileMap::setTexture(Texture* tRef)
{
    if (internalTexture)
    {
        delete internalTexture;
    }

    internalTexture = tRef;
}

void TileMap::bindShader(Shader* shader)
{
    this->shader = *shader;
    this->initRenderData();
}
void TileMap::bindShader()
{
    Shader shader = (*ResourceManager::GetShader("TileMap"));
    this->shader = shader;
    this->initRenderData();
}
void TileMap::addVertex(int addVert[3])
{
    for (int i =0;i<3; i++)
    {
        verticesToPass.push_back(addVert[i]);
    }
    initRenderData();
}
void TileMap::addVertex(int* addVert, int size)
{
    for (int i = 0; i < size*3; i++)
    {
        verticesToPass.push_back(addVert[i]);
    }
    initRenderData();
}
void TileMap::addVertex(std::vector<int>* pushV)
{
    for (auto i : *pushV) {
        verticesToPass.push_back(i);
    }
    
    initRenderData();
}
void TileMap::replaceVertex(std::vector<int>* pattern)
{
    std::vector<int> p = *pattern;
    
    int res = 0;
    while (p[0]!=verticesToPass[res] or p[1] != verticesToPass[res+1])
    {
        
        std::cout << res << std::endl;
        res+=3;
        if (res >= static_cast<int>(verticesToPass.size()))
        {
            break;
        }
    }
    if (res >= static_cast<int>(verticesToPass.size()))
    {
        std::cout << "Pattern not Found" << std::endl;
    }
    else
    {
        std::cout << "UPDATING BLOCK" << std::endl;
        verticesToPass[res] = p[0];
        verticesToPass[res+1] = p[1];
        verticesToPass[res + 2] = p[2];
        std::cout <<res<<" : " << verticesToPass[res] << verticesToPass[res + 1] << verticesToPass[res + 2] << std::endl;
    }
    
    initRenderData();
}
void TileMap::initRenderData()
{
    //std::cout << "Updating TileMap" << std::endl;
    // configure VAO/VBO
    unsigned int VBO;
    
    if (verticesToPass.size() > 0)
    {
        std::cout << "First Tile : " << verticesToPass[verticesToPass.front()] << verticesToPass[verticesToPass.front() + 1] << verticesToPass[verticesToPass.front() + 2] << std::endl;
        //std::cout << verticesToPass[2] << std::endl;
        glGenVertexArrays(1, &this->quadVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verticesToPass.size() * sizeof(int), &verticesToPass.front(), GL_STATIC_DRAW);

        glBindVertexArray(this->quadVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribIPointer(0, 3, GL_INT, 3 * sizeof(int), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cout << "Error Found!" << std::endl;
        }
    }
    
    
}

TileMap::TileMap(Shader& shader)
{
	this->shader = shader;
	this->initRenderData();
}
