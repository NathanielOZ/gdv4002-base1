#pragma once

#include "GameObject2D.h"

class Bullet : public GameObject2D
{
private:
	float mass;
	glm::vec2 velocity;
	glm::vec2 inverseMass;
	

public:
	Bullet(glm::vec2 initPosition,
		float initOrientation,
		glm::vec2 initSize,
		GLuint initTextureID,
		float mass, glm::vec2 velocity);
	
	void update(double tDelta) override;
};