#include "Asteroid.h"
#include "Engine.h"
extern glm::vec2 gravity;

Asteroid::Asteroid(glm::vec2 initPotition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID) : GameObject2D(initPotition, initOrientation, initSize, initTextureID)
{

}

void Asteroid::update(double tDelta)
{
	

	if (position.y < -getViewplaneHeight() / 2.1f)
	{
		position.y = getViewplaneHeight() / 2.1f;
	}
	if (position.y > getViewplaneHeight() / 2.1f)
	{
		position.y = -getViewplaneHeight() / 2.1f;
	}
	if (position.x < -getViewplaneWidth() / 1.5f)
	{
		position.x = getViewplaneWidth() / 1.5f;
	}
	if (position.x > getViewplaneWidth() / 1.5f)
	{
		position.x = -getViewplaneWidth() / 1.5f;
	}
}