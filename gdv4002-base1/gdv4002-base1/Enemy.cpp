#include "Enemy.h"

Enemy::Enemy(glm::vec2 initPotition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initPhase,
	float initalPhaseVelocity)
	: GameObject2D(initPotition, initOrientation, initSize, initTextureID)
{
	phaseAngle = initPhase;
	phaseVelocity = initalPhaseVelocity;
}

void Enemy::update(double tDelta)
{
	/*Set position based on phaseAngle*/
	position.y = sinf(phaseAngle);

	/*Update phaseAngle based on velocity * time elapsed*/
	phaseAngle += phaseVelocity * tDelta;

}