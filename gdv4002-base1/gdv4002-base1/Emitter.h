#pragma once

#include "GameObject2D.h"
#include <random>

class Emitter : public GameObject2D
{
private:

	float emitTimeInterval;
	float emitCounter;

	unsigned long long particleNumber;

	GLuint snowflakes[8];

	std::mt19937 gen;

	std::uniform_int_distribution<int> spriteDist;

	std::uniform_real_distribution<float> normDist; // -1 to +1

	std::uniform_real_distribution<float> massDist, scaleDist;

public:

	Emitter(glm::vec2 initPosition,
		glm::vec2 initSize,
		float emitTimeInterval);

	void update(double tDelta) override;
	void render() override;
};