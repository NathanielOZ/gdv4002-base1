#include "Engine.h"

// Function prototypes

void myUpdate(GLFWwindow* window, double tDelta);

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	//1024,1024 512,512
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 5.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//
	float pi = 3.14f;

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

	GameObject2D* player1Object = getObject("Player1");

	if (player1Object != nullptr) {
	
		player1Object->position = glm::vec2(-1.0f, 1.0f);
		player1Object->orientation = glm::radians(-30.0f);
		player1Object->size = glm::vec2(0.64f,0.64f);
		player1Object->textureID = loadTexture("Resources\\Textures\\player1_ship.png");

	}

	GameObject2D* player2Object = getObject("Player2");

	if (player2Object != nullptr) {

		player2Object->position = glm::vec2(1.5f, 1.0f);
		player2Object->orientation = glm::radians(45.0f);
		player2Object->textureID = loadTexture("Resources\\Textures\\bumblebee.png");

	}
	
	float anglesPerSecond = glm::radians(45.0f);
	
	float playerVelocity = 2.0f;

	
	setUpdateFunction(myUpdate);

	
	// Enter main loop - this handles update and render calls
	engineMainLoop();	

	

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta) {

	setViewplaneWidth(20.0f); //bigger number zoom out, smaller number zoom in, negative number flip upside down

	float player1RotationSpeed = glm::radians(-90.0f);
	
	GameObject2D* player1Object = getObject("Player1");
	
	player1Object->orientation += player1RotationSpeed * tDelta;
	
	float player2RotationSpeed = glm::radians(90.0f);

	GameObject2D* player2Object = getObject("Player2");

	player2Object->orientation += player2RotationSpeed * tDelta;
	
	
}