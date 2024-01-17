#include "camera.h"

camera::camera()
{
	ActionMap[GLFW_KEY_W] = &node::move;
	ActionMap[GLFW_KEY_S] = &node::move;
	ActionMap[GLFW_KEY_A] = &node::move;
	ActionMap[GLFW_KEY_D] = &node::move;
}

camera::~camera()
{
}

void camera::move(int key, int action)
{
	if (action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_A)
		{
			position += glm::vec2(3200.f, 0.f) * frameTime;
		}
		if (key == GLFW_KEY_D)
		{
			position -= glm::vec2(3200.f, 0.f) * frameTime;
		}
		if (key == GLFW_KEY_W)
		{
			position += glm::vec2(0.f, 3200.f) * frameTime;
		}
		if (key == GLFW_KEY_S)
		{
			position -= glm::vec2(0.f, 3200.f) * frameTime;
		}
	}
	
}

