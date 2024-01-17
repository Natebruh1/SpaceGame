#include "sprite.h"
sprite::sprite(Shader& shader)
{
    this->shader = shader;
    this->initRenderData();
}

sprite::sprite()
{
    bindShader();
}

sprite::~sprite()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void sprite::render(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void sprite::render()
{
    //Update these to node2D variables
    glm::vec2 pos = getWorldPosition();
    float rotate = getWorldRotation();
    glm::vec2 size = glm::vec2( internalTexture->Width,internalTexture->Height ) * getWorldScale();
    
    pos += currentCamera->position;
    rotate += currentCamera->rotation;
    size *= currentCamera->scale;

    
    glm::vec3 color = glm::vec3(1.f,1.f,1.f);

    //Prepare the correct shader
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(pos, 0.0f));


    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back



    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale



    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    internalTexture->Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void sprite::setTexture(Texture* tRef)
{
    if (internalTexture)
    {
        delete internalTexture;
    }
    
    internalTexture = tRef;
}

void sprite::bindShader(Shader* shader)
{
    this->shader = *shader;
    this->initRenderData();
}

void sprite::bindShader()
{
    Shader shader = (*ResourceManager::GetShader("sprite"));
    this->shader = shader;
    this->initRenderData();
}

void sprite::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}