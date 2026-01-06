#include "AsteroidEmitter.h"
#include "Engine.h"
#include "Asteroid.h"

using namespace std;

AsteroidEmitter::AsteroidEmitter(glm::vec2 initPosition,
	glm::vec2 initSize,
	float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0)
{
	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;

	asteroidNumber = 0;

	for (int i = 0; i < 1; i++)
	{
		string path = "Resources\\Textures\\alien01.png";
		asteroid[i] = loadTexture(path.c_str());

		if (asteroid[i] > 0)
			cout << "successfully loaded texture" << path << endl;
		else
			cout << "failed to load texture" << path << endl;

		random_device rd; // obtain a seed for random number engine

		gen = mt19937(rd());

		spriteDist = uniform_int_distribution<int>(0, 0);
		normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
		massDist = uniform_real_distribution<float>(0.005f, 0.05f);
		scaleDist = uniform_real_distribution<float>(0.1f, 1.0f);
		xVelosityDist = uniform_real_distribution<float>(-1.0f, 1.0f);
		yVelosityDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	}
}

void AsteroidEmitter::render()
{

}

void AsteroidEmitter::update(double tDelta)
{
	emitCounter += (float)tDelta;

	while (emitCounter >= emitTimeInterval)
	{
		emitCounter -= emitTimeInterval;

		//create Asteroid

		float x = position.x + normDist(gen) * size.x;
		float y = position.y + normDist(gen) * size.y;
		float scale = scaleDist(gen);
		float mass = massDist(gen);
		float rotationSpeed = glm::radians(normDist(gen) * 45.0f);
		int spriteIndex = spriteDist(gen);
		float xVelocity = xVelosityDist(gen);
		float yVelocity = yVelosityDist(gen);

		Asteroid* a1 = new Asteroid(glm::vec2(x, y),
			0.0f,
			glm::vec2(scale, scale),
			asteroid[spriteIndex],
			mass,
			rotationSpeed,
			xVelocity, yVelocity);

		string key = string("asteroid");

		if (asteroidNumber > 0)
			key += to_string(asteroidNumber);

		asteroidNumber++;

		addObject(key.c_str(), a1);
	}
}