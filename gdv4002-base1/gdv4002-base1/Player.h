#pragma once
#include "GameObject2D.h"


class Player : public GameObject2D 
{
	private:
		float mass;
		glm::vec2 velocity;
		glm::vec2 inverseMass;
		float thrust;
		//float boostThrust;

		float cooldown;
		float bulletCounter;

		unsigned long long bulletNumber;

	public:
		Player(glm::vec2 initPosition,
			float initOrientation,
			glm::vec2 initSize,
			GLuint initTextureID,
			float mass,
			const float thrust,
			float cooldown
			/*const float boostThrust*/);


		void update(double tDelta) override;
};