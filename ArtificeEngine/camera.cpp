#include "camera.h"

camera::camera()
{
}

camera::~camera()
{
}

void camera::input(int key, int scancode, int action, int mods)
{
	switch (key) {
		//Spectator Camera Controls
	case GLFW_KEY_W:
		if (action == GLFW_REPEAT || GLFW_PRESS) position.y += 3200.f*frameTime;
		break;
	case GLFW_KEY_S:
		if (action == GLFW_REPEAT || GLFW_PRESS) position.y -= 3200.f * frameTime;
		break;
	case GLFW_KEY_A:
		if (action == GLFW_REPEAT || GLFW_PRESS) position.x += 3200.f * frameTime;
		break;
	case GLFW_KEY_D:
		if (action == GLFW_REPEAT || GLFW_PRESS) position.x -= 3200.f * frameTime;
		break;
	}
}
