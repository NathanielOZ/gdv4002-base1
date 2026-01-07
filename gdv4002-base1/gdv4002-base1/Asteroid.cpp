#include "Asteroid.h"
#include "Engine.h"


extern float xGravity;
extern float yGravity;

Asteroid::Asteroid(glm::vec2 initPotition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float mass,
	float angleChangePerSecond,
	float xVelocity,
	float yVelocity) : GameObject2D(initPotition, initOrientation, initSize, initTextureID/* velocity*/)
{
	this->mass = mass;
	//this->velocity = velocity;
	this->xVelocity = xVelocity;
	this->yVelocity = yVelocity;

	maxVelocity = 2.0f;
	minVelocity = -2.0f;

	
	this->angleChangePerSecond = angleChangePerSecond;
}

void Asteroid::update(double tDelta)
{
	float XG = xGravity;// X Sum forces
	float YG = yGravity;// Y Sum forces
	
	 
	
	float yAccel = YG * (1.0f / mass);// Calculate Y acceleration
	float xAccel = XG * (1.0f / mass);// Calculate X acceleration

	 

	xVelocity = xVelocity + xAccel * (float)tDelta;// update X velocity
	yVelocity = yVelocity + yAccel * (float)tDelta;// update Y velocity

	/* Velocity clamp */

	if (xVelocity > maxVelocity)// check if X velocity is higher than maxVelocity
		xVelocity = maxVelocity;// if X velocity goes higher than maxVelocity change x velocity to maxVelocity
	
	else if (xVelocity < minVelocity)
		xVelocity = minVelocity;
	
	if (yVelocity > maxVelocity)
		yVelocity = maxVelocity;
	
	else if (yVelocity < minVelocity)
		yVelocity = minVelocity;
	
	
	velocity = glm::vec2(xVelocity, yVelocity);// combinding the x and y velocity into one

	position = position + velocity * (float)tDelta; // update position
	
	orientation += angleChangePerSecond * (float)tDelta; // Non-physics bit for rotation

	if (position.y < -getViewplaneHeight() / 1.5f)
	{
		position.y = getViewplaneHeight() / 2.0f;
	}
	if (position.y > getViewplaneHeight() / 1.5f)
	{
		position.y = -getViewplaneHeight() / 2.0f;
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