#include "node2d.h"
#include "camera.h"
glm::vec2 node2d::getWorldPosition()
{
    glm::vec2 total = glm::vec2(0.f, 0.f);
    node* parentTrace = this;
    while (parentTrace!= nullptr) //Whilst there is a parent in the tree
    {
        if (dynamic_cast<node2d*>(parentTrace) != NULL)
        {
            total += dynamic_cast<node2d*>(parentTrace)->position;
        }
        //Go up the tree
        parentTrace = parentTrace->get_parent();
    }
    
    return total;
}

glm::vec2 node2d::getWorldScale()
{
    glm::vec2 total = glm::vec2(1.f, 1.f);
    node* parentTrace = this;
    while (parentTrace->get_parent() != nullptr) //Whilst there is a parent in the tree
    {
        if (dynamic_cast<node2d*>(parentTrace) != NULL)
        {
            total *= dynamic_cast<node2d*>(parentTrace)->scale;
        }
        //Go up the tree
        parentTrace = parentTrace->get_parent();
    }
    
    return total;
}

float node2d::getWorldRotation()
{
    
    float total = 0.0;
    node* parentTrace = this;
    while (parentTrace->get_parent() != nullptr) //Whilst there is a parent in the tree
    {
        if (dynamic_cast<node2d*>(parentTrace) != NULL)
        {
            total += dynamic_cast<node2d*>(parentTrace)->rotation;
        }
        //Go up the tree
        parentTrace = parentTrace->get_parent();
    }
    
    return total;
}
