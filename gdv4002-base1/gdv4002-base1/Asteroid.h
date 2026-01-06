#pragma once

#include "GameObject2D.h"


class Asteroid : public GameObject2D
{
private:
	
	float mass;
	glm::vec2 velocity;
	float angleChangePerSecond;
	float xVelocity;
	float yVelocity;
	float maxVelocity;
	float minVelocity;

public:
	Asteroid(glm::vec2 initPosition,
		float initOrientation,
		glm::vec2 initSize,
		GLuint initTextureID,
		float mass,
		float angleChangePerSecond,
		float xVelocity,
		float yVelocity);

	void update(double tDelta) override;

};