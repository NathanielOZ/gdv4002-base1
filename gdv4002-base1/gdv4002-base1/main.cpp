#include "Engine.h"
#include "Keys.h"
#include <bitset>

//gobal variables

float enemyPhase[3] = { 1.0f, 0.0f, 2.0f };
float enemyPhaseVelocity[3] = { glm::radians(90.0f), glm::radians(45.0f), glm::radians(270.0f) };

//float playerPhase[1] = { 0.0f };
//float playerPhaseVelocity[1] = {glm::radians(30.0f)};

std::bitset<5> keys{ 0x0 };

// Function prototypes

void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandleer(GLFWwindow* window, int key, int scancode, int action, int mods);


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
	
	addObject("player1",
		glm::vec2(1.0f, 1.0f),// the postion of the object
		/* 45.0f * pi/180.0f */ glm::radians(45.0f), // the rotation of the object
		glm::vec2(0.5f,1.0f), // the size of the object
		"Resources\\Textures\\mcblock01.png", // texture of the object
		TextureProperties::NearestFilterTexture() // "resizing" the image onto the object (to look nicer to look at)
		);

	//addObject("Player2",
	//	glm::vec2(0.0f, 0.0f),
	//	glm::radians(45.0f),
	//	glm::vec2(1.0f, 1.0f),
	//	"Resources\\Textures\\mcblock01.png",
	//	TextureProperties::NearestFilterTexture()
	//	);

	addObject("enemy",
		glm::vec2(0.0f, 0.0f),
		0.0f, glm::vec2(0.75f, 0.75f),
		"Resources\\Textures\\alien01.png");

	addObject("enemy",
		glm::vec2(1.0f, 0.0f),
		0.0f, glm::vec2(0.75f, 0.75f),
		"Resources\\Textures\\alien01.png");

	addObject("enemy",
		glm::vec2(2.0f, 0.0f), 0.0f,
		glm::vec2(0.75f, 0.75f),
		"Resources\\Textures\\alien01.png");


	GameObject2D* player1Object = getObject("player1");

	if (player1Object != nullptr) {
	
		player1Object->position = glm::vec2(-1.0f, 1.0f);
		player1Object->orientation = glm::radians(-30.0f);
		player1Object->size = glm::vec2(0.64f,0.64f);
		player1Object->textureID = loadTexture("Resources\\Textures\\player1_ship.png");

	}

	//GameObject2D* player2Object = getObject("Player2");
	//
	//if (player2Object != nullptr) {
	//
	//	player2Object->position = glm::vec2(1.5f, 1.0f);
	//	player2Object->orientation = glm::radians(45.0f);
	//	player2Object->textureID = loadTexture("Resources\\Textures\\bumblebee.png");
	//
	//}
	
	float anglesPerSecond = glm::radians(45.0f);
	
	float playerVelocity = 2.0f;

	//set/update funtion before engineMainLoop

	setUpdateFunction(myUpdate);

	setKeyboardHandler(myKeyboardHandleer);

	//listGameObjectKeys(); // checks the number of objects rendered in the game

	// Enter main loop - this handles update and render calls
	engineMainLoop();	

	

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta)
{

	setViewplaneWidth(10.0f); //bigger number zoom out, smaller number zoom in, negative number flip upside down

	static float playerSpeed = 1.0f; // distance per second

	GameObject2D* player = getObject("player1");

	if (keys.test(Key::W) == true)
	{
		player->position.y += playerSpeed * (float)tDelta;
	}
	else if (keys.test(Key::S) == true)
	{
		player->position.y -= playerSpeed * (float)tDelta;
	}
	else if (keys.test(Key::D) == true)
	{
		player->position.x += playerSpeed * (float)tDelta;
	}
	else if (keys.test(Key::A) == true)
	{
		player->position.x -= playerSpeed * (float)tDelta;
	}

	//float player1RotationSpeed = glm::radians(-90.0f);
	//
	//GameObject2D* player1Object = getObject("player1");
	//
	//player1Object->orientation += player1RotationSpeed * tDelta;
	
	//float player2RotationSpeed = glm::radians(90.0f);
	//
	//GameObject2D* player2Object = getObject("Player2");
	//
	//player2Object->orientation += player2RotationSpeed * tDelta;
	
	//GameObjectCollection players = getObjectCollection("player1");
	//
	//players.objectArray[0]->position.y = sinf(playerPhase[0]);
	//playerPhase[0] += playerPhaseVelocity[0] * tDelta;


	//enemy array
	GameObjectCollection enemies = getObjectCollection("enemy");

	//enemies.objectArray[0]->position.y = sinf(enemyPhase[0]);// assume phase stored in radians so no conversion needed
	//enemyPhase[0] += enemyPhaseVelocity[0] * tDelta;

	//move all enemies
	for (int i = 0; i < enemies.objectCount; i++) 
	{
		enemies.objectArray[i]->position.y = sinf(enemyPhase[i]);
		enemyPhase[i] += enemyPhaseVelocity[i] * tDelta;
	}

}

void myKeyboardHandleer(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check if a key is pressed
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{

		case GLFW_KEY_ESCAPE:
			// If escape is pressed tell GLFW we want to close the window (and quit)
			glfwSetWindowShouldClose(window, true);
			break;

		case GLFW_KEY_W:
			keys[Key::W] = true;
			break;

		case GLFW_KEY_S:
			keys[Key::S] = true;
			break;

		case GLFW_KEY_D:
			keys[Key::D] = true;
			break;

		case GLFW_KEY_A:
			keys[Key::A] = true;
			break;
		}
	}

	// If not check a key has been released
	else if (action == GLFW_RELEASE) {

		// handle key release events

		switch (key)
		{
		case GLFW_KEY_W:
			keys[Key::W] = false;
			break;

		case GLFW_KEY_S:
			keys[Key::S] = false;
			break;

		case GLFW_KEY_D:
			keys[Key::D] = false;
			break;

		case GLFW_KEY_A:
			keys[Key::A] = false;
			break;
		}
	}
}
