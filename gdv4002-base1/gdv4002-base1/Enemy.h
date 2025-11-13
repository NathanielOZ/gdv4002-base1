#pragma once
#include "GameObject2D.h"
#include <glm/glm.hpp>

class Enemy : public GameObject2D
{
	private:
		float phaseAngle;
		float phaseVelocity;
	public:
		Enemy(glm::vec2 initPotition,
			float initOrientation,
			glm::vec2 initSize,
			GLuint initTextureID,
			float initPhase,
			float initalPhaseVelocity);

		void update(double tDelta) override;
};