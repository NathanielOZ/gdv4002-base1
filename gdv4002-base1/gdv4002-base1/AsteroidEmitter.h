#pragma once

#include "GameObject2D.h"
#include <random>

class AsteroidEmitter : public GameObject2D
{
private:

	float emitTimeInterval;
	float emitCounter;

	unsigned long long asteroidNumber;

	GLuint asteroid[3];

	// Random number generator
	std::mt19937 gen;

	//Random number distributions
	std::uniform_int_distribution<int> spriteDist; // random integer for particle sprite selection
	std::uniform_real_distribution<float> normDist; /*-1 tp 1*/ 
	std::uniform_real_distribution<float> massDist, scaleDist, xVelosityDist, yVelosityDist;

public:

	AsteroidEmitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval);

	void update(double tDelta) override;
	void render() override;

};
