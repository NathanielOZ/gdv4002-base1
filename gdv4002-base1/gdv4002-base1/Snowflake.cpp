#include "Snowflake.h"

extern glm::vec2 gravity;

Snowflake::Snowflake(glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float mass,
	float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);

	this->angleChangePerSecond = angleChangePerSecond;
}

void Snowflake::update(double tDelta)
{
	glm::vec2 F = gravity; // Sum forces - only add gravity for now

	glm::vec2 accel = F * (1.0f / mass); // Calculate acceleration

	velocity = velocity + accel * (float)tDelta; // update velocity

	position = position + velocity * (float)tDelta; // update position

	orientation += angleChangePerSecond * (float)tDelta; // Non-physics bit for rotation
}