#include "Bullet.h"

extern glm::vec2 gravity;

Bullet::Bullet(glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float mass, glm::vec2 velocity) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;

	this->velocity = velocity;

	inverseMass = glm::vec2(1.0f / mass);
}

void Bullet::update(double tDelta)
{
	//this was taken from the player class
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	F += gravity;

	/* calculate acceleration. If F = ma, a = F/m */
	glm::vec2 a = F * inverseMass;

	/* integate to get new velocity */
	velocity = velocity + (a * (float)tDelta);

	/* integate to get new posistion */
	position = position + (velocity * (float)tDelta);

}