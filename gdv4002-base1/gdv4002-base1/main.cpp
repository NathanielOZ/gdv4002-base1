#include "Engine.h"

// Function prototypes

void myUpdate(GLFWwindow* window, double tDelta);

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//
	float pi = 3.14f;

	float anglesPerSecond = glm::radians(45.0f);

	float playerVelocity = 2.0f;

	GameObject2D* addObject(
		const char* name, 
		glm::vec2 initPosition = glm::vec2(0.0f, 0.0f),
		float initOrientation = 0.0f,
		glm::vec2 initSize = glm::vec2(1.0f, 1.0f),
		const char* texturePath = nullptr,
		TextureProperties texProperties = TextureProperties());
	
	addObject("Player1",
		glm::vec2(1.0f, 1.0f),// the postion of the object
		/* 45.0f * pi/180.0f */ glm::radians(45.0f), // the rotation of the object
		glm::vec2(0.5f,1.0f), // the size of the object
		"Resources\\Textures\\mcblock01.png", // texture of the object
		TextureProperties::NearestFilterTexture() // "resizing" the image onto the object (to look nicer to look at)
		);

	addObject("Player2",
		glm::vec2(0.0f, 0.0f),
		glm::radians(45.0f),
		glm::vec2(1.0f, 1.0f),
		"Resources\\Textures\\mcblock01.png",
		TextureProperties::NearestFilterTexture()
		);

	GameObject2D* Player1Object = getObject("Player1");

	if (Player1Object != nullptr) {
	
		Player1Object->position = glm::vec2(-1.0f, 1.0f);
		Player1Object->orientation = glm::radians(-30.0f);
		Player1Object->size = glm::vec2(0.32f,0.32f);
		Player1Object->textureID = loadTexture("Resources\\Textures\\player1_ship.png");

	}

	GameObject2D* Player2Object = getObject("Player2");

	if (Player2Object != nullptr) {

		Player2Object->position = glm::vec2(1.5f, 1.0f);
		Player2Object->orientation = glm::radians(45.0f);
		Player2Object->textureID = loadTexture("Resources\\Textures\\bumblebee.png");

	}

	// Enter main loop - this handles update and render calls
	engineMainLoop();	

	setUpdateFunction(myUpdate);

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta) {

	float player1RotationSpeed = glm::radians(90.0f);

	GameObject2D* Player1 = getObject("Player1");

	Player1->orientation += player1RotationSpeed * tDelta;

}
