#include "character.h"

character::character()
{
	internalSprite = new sprite();
}

void character::update()
{
	velocity += accel;
	
	
	if (colliding(velocity * frameTime))
	{
		position += velocity*frameTime;
	}
	
	
	velocity *= 0.9;
	accel -= glm::vec2(0.f, 10.f * frameTime);
	std::cout << "Down Position : " << position.y << std::endl;
}

bool character::colliding()
{
	for (auto t : currentWorld->CurrentTerrainLoaded)
	{
		for (auto v : *t->getCollisionVertices())
		{
			//NEED TO DO BOTTOM LEFT AND TOP RIGHT
			if (!(position.x > v[0].x && position.x < v[1].x) && !(position.x + hitbox.width > v[0].x && position.x + hitbox.width < v[1].x) &&	   //X
				!(position.y > v[2].y && position.y < v[0].y) && !(position.y + hitbox.height > v[2].y && position.y + hitbox.height < v[0].y))	   //Y
			{
				
			}
			else
			{
				std::cout << "Collision Detected" << std::endl;
				return false;
			}
		}
	}
	std::cout << "Collision not Detected" << std::endl;
	return true;
}

bool character::colliding(glm::vec2 extraVec)
{
	glm::vec2 posMod = position + extraVec;
	for (auto t : currentWorld->CurrentTerrainLoaded)
	{
		for (auto v : *t->getCollisionVertices())
		{
			//NEED TO DO BOTTOM LEFT AND TOP RIGHT
			if (!(posMod.x > v[0].x && posMod.x < v[1].x) && !(posMod.x + hitbox.width > v[0].x && posMod.x + hitbox.width < v[1].x) &&	   //X
				!(posMod.y > v[2].y && posMod.y < v[0].y) && !(posMod.y + hitbox.height > v[2].y && posMod.y + hitbox.height < v[2].y))	   //Y
			{
				
			}
			else
			{
				std::cout << "Collision Detected" << std::endl;
				return false;
			}
		}
	}
	std::cout << "Collision not Detected" << std::endl;
	return true;
}

glm::vec2 character::resolveCollision(rect bounds, std::vector<glm::vec2> staticCollision)
{
	glm::vec2 moveVec;
	float Dist = 9999999999999.f;
	float currDist;
	if (position.x > staticCollision[0].x && position.x<staticCollision[1].x && position.y>staticCollision[2].y && position.y < staticCollision[0].y) //If top left of hitbox is colliding
	{
		glm::vec2 chosenVert;
		for (auto v : staticCollision)
		{
			currDist = Distance(glm::vec2(position.x, position.y), v);
			if (currDist < Dist)
			{
				Dist = currDist;
				chosenVert = v;
			}
		}
		chosenVert = chosenVert - glm::vec2(position.x, position.y);
		if (colliding(chosenVert)) resolveCollision(bounds,staticCollision,currDist*1.1);


	}
	//Repeat for all other corners

	return glm::vec2();
}

glm::vec2 character::resolveCollision(rect bounds, std::vector<glm::vec2> staticCollision, float scale)
{
	return glm::vec2();
}
