#include "Player.h"
#include "Keys.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Engine.h"
#include <bitset>


extern std::bitset<5> keys;

extern glm::vec2 gravity;

using namespace std;


Player::Player(glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float mass,
	float thrust,
	float cooldown
	/*float boostThrust*/) :
	GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;

	velocity = glm::vec2(0.0f, 0.0f);

	inverseMass = glm::vec2(1.0f / mass);

	this->thrust = thrust;

	this->cooldown = cooldown;

	bulletCounter = cooldown;

	//this->boostThrust = boostThrust;
}
void Player::update(double tDelta)
{

	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	/* Player movement */

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
	
	/*Bullet spawn*/

	bulletNumber = 0;

	string key = string("bullet");

	bulletCounter += (float)tDelta;

	//if (keys.test(Key::SPACE) == true && keys.test(Key::W) == true)
	//{
	//	GLuint bulletTexture = loadTexture("Resources\\Textures\\mcblock01.png");
	//
	//	Bullet* bullet = new Bullet(glm::vec2(position),
	//		orientation,
	//		glm::vec2(0.5f, 0.5f), // Size
	//		bulletTexture,
	//		1.0f,// Mass
	//		glm::vec2(0.0f, 5.0f)); // Velocity and the direction of where the bullet will go 
	//
	//	if (BulletNumber > 0)
	//		key += to_string(BulletNumber);
	//	BulletNumber++;
	//
	//	addObject(key.c_str(), bullet);
	//}
	//
	//else if (keys.test(Key::SPACE) == true && keys.test(Key::S) == true)
	//{
	//	GLuint bulletTexture = loadTexture("Resources\\Textures\\mcblock01.png");
	//	Bullet* bullet = new Bullet(glm::vec2(position),
	//		orientation,
	//		glm::vec2(0.5f, 0.5f), // Size
	//		bulletTexture,
	//		1.0f,// Mass
	//		glm::vec2(0.0f, -5.0f));
	//
	//	if (BulletNumber > 0)
	//		key += to_string(BulletNumber);
	//	BulletNumber++;
	//
	//	addObject(key.c_str(), bullet);
	//}
	//
	//if (keys.test(Key::SPACE) == true && keys.test(Key::D) == true)
	//{
	//	GLuint bulletTexture = loadTexture("Resources\\Textures\\mcblock01.png");
	//	Bullet* bullet = new Bullet(glm::vec2(position),
	//		orientation,
	//		glm::vec2(0.5f, 0.5f), // Size
	//		bulletTexture,
	//		1.0f,// Mass
	//		glm::vec2(5.0f, 0.0f));
	//
	//	if (BulletNumber > 0)
	//		key += to_string(BulletNumber);
	//	BulletNumber++;
	//
	//	addObject(key.c_str(), bullet);
	//}
	//
	//else if (keys.test(Key::SPACE) == true && keys.test(Key::A) == true)
	//{
	//	GLuint bulletTexture = loadTexture("Resources\\Textures\\mcblock01.png");
	//	Bullet* bullet = new Bullet(glm::vec2(position),
	//		orientation,
	//		glm::vec2(0.5f, 0.5f), // Size
	//		bulletTexture,
	//		1.0f,// Mass
	//		glm::vec2(-5.0f, 0.0f));
	//
	//	if (BulletNumber > 0)
	//		key += to_string(BulletNumber);
	//	BulletNumber++;
	//
	//	addObject(key.c_str(), bullet);
	//}

	while (bulletCounter >= cooldown)
	{
		bulletCounter -= cooldown;

		if (keys.test(Key::SPACE) == true && orientation == glm::radians(0.0f))
		{
		
			GLuint bulletTexture = loadTexture("Resources\\Textures\\bullet1.png");
			Bullet* bullet = new Bullet(glm::vec2(position),
				orientation,
				glm::vec2(0.5f, 0.5f), // Size
				bulletTexture,
				1.0f,// Mass
				glm::vec2(5.0f, 0.0f));


			if (bulletNumber > 0)
				key += to_string(bulletNumber);
			bulletNumber++;

			addObject(key.c_str(), bullet);
		
		
		}

		else if (keys.test(Key::SPACE) == true && orientation == glm::radians(180.0f))
		{
			GLuint bulletTexture = loadTexture("Resources\\Textures\\bullet1.png");
			Bullet* bullet = new Bullet(glm::vec2(position),
				orientation,
				glm::vec2(0.5f, 0.5f), // Size
				bulletTexture,
				1.0f,// Mass
				glm::vec2(-5.0f, 0.0f));

			if (bulletNumber > 0)
				key += to_string(bulletNumber);
			bulletNumber++;

			addObject(key.c_str(), bullet);
		}

		if (keys.test(Key::SPACE) == true && orientation == glm::radians(90.0f))
		{
			GLuint bulletTexture = loadTexture("Resources\\Textures\\bullet1.png");
			Bullet* bullet = new Bullet(glm::vec2(position),
				orientation,
				glm::vec2(0.5f, 0.5f), // Size
				bulletTexture,
				1.0f,// Mass
				glm::vec2(0.0f, 5.0f));

			if (bulletNumber > 0)
				key += to_string(bulletNumber);
			bulletNumber++;

			addObject(key.c_str(), bullet);
		}

		if (keys.test(Key::SPACE) == true && orientation == glm::radians(-90.0f))
		{
			GLuint bulletTexture = loadTexture("Resources\\Textures\\bullet1.png");
			Bullet* bullet = new Bullet(glm::vec2(position),
				orientation,
				glm::vec2(0.5f, 0.5f), // Size
				bulletTexture,
				1.0f,// Mass
				glm::vec2(0.0f, -5.0f));

			if (bulletNumber > 0)
				key += to_string(bulletNumber);
			bulletNumber++;

			addObject(key.c_str(), bullet);
		}
	}
	

	/*
	if (keys.test(Key::LEFTSHIFT) == true)
	{
		printf("\nLEFT_SHIFT");
	}
	*/

	F += gravity;
	
	/* Warping Player */

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

	/* Velocity calucation */

	/* calculate acceleration. If F = ma, a = F/m */
	glm::vec2 a = F * inverseMass;

	/* integate to get new velocity */
	velocity = velocity + (a * (float)tDelta);

	/* integate to get new posistion */
	position = position + (velocity * (float)tDelta);
}
