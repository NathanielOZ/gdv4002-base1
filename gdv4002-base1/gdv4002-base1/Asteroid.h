#pragma once

#include "GameObject2D.h"

class Asteroid : public GameObject2D
{
private:
	unsigned long long asteroidNumber;
public:
	Asteroid(glm::vec2 initPotition,
		float initOrientation,
		glm::vec2 initSize,
		GLuint initTextureID);

	void update(double tDelta) override;

};