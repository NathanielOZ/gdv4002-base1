#include "Player.h"
#include "Keys.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Engine.h"
#include <bitset>


extern std::bitset<5> keys;

extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float mass,
	float thrust
	/*float boostThrust*/) :
	GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f);

	inverseMass = glm::vec2(1.0f / mass);

	this->thrust = thrust;

	//this->boostThrust = boostThrust;
}
void Player::update(double tDelta)
{
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	// accumulate forces
	if (keys.test(Key::W) == true)
	{
		F += glm::vec2(0.0f, thrust);
		orientation = glm::radians(90.0f);
	}
	else if (keys.test(Key::S) == true)
	{
		F += glm::vec2(0.0f, -thrust);
		orientation = glm::radians(-90.0f);
	}
	if (keys.test(Key::D) == true)
	{
		F += glm::vec2(thrust, 0.0f);
		orientation = glm::radians(0.0f);
	}
	else if (keys.test(Key::A) == true)
	{
		F += glm::vec2(-thrust, 0.0f);
		orientation = glm::radians(180.0f);
	}
	
	if (keys.test(Key::SPACE) == true)
	{
		GLuint bulletTexture = loadTexture("Resources\\Textures\\mcblock01.png");
		Bullet* bullet = new Bullet(glm::vec2(position),
			orientation,
			glm::vec2(0.5f, 0.5f), // Size
			bulletTexture,
			1.0f,// Mass
			glm::vec2(velocity * 2.0f));
		addObject("bullet", bullet);
	}
	
	/*
	if (keys.test(Key::LEFTSHIFT) == true)
	{
		printf("\nLEFT_SHIFT");
	}
	*/

	F += gravity;
	
	if (position.y < -getViewplaneHeight() / 1.8f)
	{
		//F += glm::vec2(0.0f, 200.0f);

		position.y = getViewplaneHeight() / 1.9f;
	}
	if (position.y > getViewplaneHeight() / 1.8f)
	{
		//F += glm::vec2(0.0f, -200.0f);

		position.y = -getViewplaneHeight() / 1.9f;
	}
	if (position.x < -getViewplaneWidth() / 1.5f)
	{
		position.x = getViewplaneWidth() / 1.5f;
	}
	if (position.x > getViewplaneWidth() / 1.5f)
	{
		position.x = -getViewplaneWidth() / 1.5f;
	}

	/* calculate acceleration. If F = ma, a = F/m */
	glm::vec2 a = F * inverseMass;

	/* integate to get new velocity */
	velocity = velocity + (a * (float)tDelta);

	/* integate to get new posistion */
	position = position + (velocity * (float)tDelta);
}
