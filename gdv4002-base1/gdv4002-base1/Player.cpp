#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include <bitset>

extern std::bitset<5> keys;

extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float mass,
	float thrust) :
	GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f);

	inverseMass = glm::vec2(1.0f / mass);

	this->thrust = thrust;
}
void Player::update(double tDelta)
{
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	// accumulate forces
	if (keys.test(Key::W) == true)
	{
		F += glm::vec2(0.0f, thrust);
	}
	else if (keys.test(Key::S) == true)
	{
		F += glm::vec2(0.0f, -thrust);
	}
	if (keys.test(Key::D) == true)
	{
		F += glm::vec2(thrust, 0.0f);
	}
	else if (keys.test(Key::A) == true)
	{
		F += glm::vec2(-thrust, 0.0f);
	}

	F += gravity;

	if (position.y < -getViewplaneHeight() / 2.0f)
	{
		F += glm::vec2(0.0f, 200.0f);
	}
	if (position.y > getViewplaneHeight() / 2.0f)
	{
		F += glm::vec2(0.0f, -200.0f);
	}
	if (position.x < -getViewplaneWidth() / 2.0f)
	{
		F += glm::vec2(200.0f, 0.0f);
	}
	if (position.x > getViewplaneWidth() / 2.0f)
	{
		F += glm::vec2(-200.0f, 0.0f);
	}
	/* calculate acceleration. If F = ma, a =F/m */
	glm::vec2 a = F * inverseMass;

	/* integate to get new velocity */
	velocity = velocity + (a * (float)tDelta);

	/* integate to get new posistion */
	position = position + (velocity * (float)tDelta);
}
