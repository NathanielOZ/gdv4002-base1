#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Emitter.h"
#include "AsteroidEmitter.h"
#include "glPrint.h"
#include <bitset>

//gobal variables

//float enemyPhase[3] = { 1.0f, 0.0f, 2.0f };
//float enemyPhaseVelocity[3] = { glm::radians(90.0f), glm::radians(45.0f), glm::radians(270.0f) };

//float playerPhase[1] = { 0.0f };
//float playerPhaseVelocity[1] = {glm::radians(30.0f)};

std::bitset<5> keys{ 0x0 };

glm::vec2 gravity = glm::vec2(0.0f, -0.005f);
float xGravity = 0.0f;
float yGravity = -0.005f;

GLuint myFontNormal = 0;
GLuint myFontUnderline = 0;


// Function prototypes

//void myUpdate(GLFWwindow* window, double tDelta);
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

//void deleteSnowflakes(GLFWwindow* window, double tDelta);

//void deleteAsteroids(GLFWwindow* window, double tDelta);

void deleteObjects(GLFWwindow* window, double tDelta);


//void myRender(GLFWwindow* window);

//void displayScore(Player* player);

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	//1024,1024 512,512
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 5.0f);

	if (initResult != 0)
	{
		printf("Cannot setup game window\n");
		return initResult; // exit if setup failed
	}

	setViewplaneWidth(10.0f); //bigger number zoom out, smaller number zoom in, negative number flip upside down

	myFontNormal = glBuildFont(L"Consolas", 24);
	myFontUnderline = glBuildFont(L"Aptos", 24, GLFONT_STYLE::BOLD| GLFONT_STYLE::UNDERLINE);


	// Setup rendering properties (enable blending) 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);// Enable alpha blending and set the depth test
	glDepthFunc(GL_ALWAYS);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	
	// Setup game scene objects here
	
	GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png");

	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f,
		glm::vec2(0.5f, 0.5f) /*Size value*/,
		playerTexture, 1.0f /*Mass value*/, 2.0f /*Thrust value*/, 0.5f /*Cooldown value*/ /*5.0f*/ /*BoostThrust value*/);

	addObject("player", mainPlayer);
	
	//Emitter* emitter = new Emitter(
	//	glm::vec2(0.0f, getViewplaneHeight() / 2.0f * 1.2f),
	//	glm::vec2(getViewplaneWidth() / 2.0f, 0.0f),
	//	0.05f);
	//
	//addObject("emitter", emitter);
	
	AsteroidEmitter* asteroidEmitter = new AsteroidEmitter(
		glm::vec2(0.0f, getViewplaneHeight() / 2.0f * 1.2f),
		glm::vec2(getViewplaneWidth() / 2.0f, 1.0f),
		0.6f);
	
	addObject("asteroidEmitter", asteroidEmitter);

	//GLuint enemyTexture = loadTexture("Resources\\Textures\\alien01.png");
	//
	//Enemy* enemy1 = new Enemy(glm::vec2(-1.0f, 0.0f),
	//	0.0f,
	//	glm::vec2(0.5f, 0.5f),
	//	enemyTexture,
	//	0.0f,
	//	glm::radians(45.0f));
	//
	//Enemy* enemy2 = new Enemy(glm::vec2(1.0f, 0.0f),
	//	0.0f,
	//	glm::vec2(1.0f, 1.0f),
	//	enemyTexture,
	//	0.0f,
	//	glm::radians(45.0f));
	//
	//Enemy* enemy3 = new Enemy(glm::vec2(2.0f, 0.0f),
	//	0.0f,
	//	glm::vec2(0.5f, 0.5f),
	//	enemyTexture,
	//	0.0f,
	//	glm::radians(45.0f));


	// Add enemy objects to the engine

	//addObject("enemy1", enemy1);
	//addObject("enemy2", enemy2);
	//addObject("enemy3", enemy3);
	
	//float pi = 3.14f;
	//
	//
	//GameObject2D* addObject(
	//	const char* name, 
	//	glm::vec2 initPosition = glm::vec2(0.0f, 0.0f),
	//	float initOrientation = 0.0f,
	//	glm::vec2 initSize = glm::vec2(1.0f, 1.0f),
	//	const char* texturePath = nullptr,
	//	TextureProperties texProperties = TextureProperties());
	//
	//addObject("player1",
	//	glm::vec2(1.0f, 1.0f),// the postion of the object
	//	/* 45.0f * pi/180.0f */ glm::radians(45.0f), // the rotation of the object
	//	glm::vec2(0.5f,1.0f), // the size of the object
	//	"Resources\\Textures\\mcblock01.png", // texture of the object
	//	TextureProperties::NearestFilterTexture() // "resizing" the image onto the object (to look nicer to look at)
	//	);
	//
	////addObject("Player2",
	//	glm::vec2(0.0f, 0.0f),
	//	glm::radians(45.0f),
	//	glm::vec2(1.0f, 1.0f),
	//	"Resources\\Textures\\mcblock01.png",
	//	TextureProperties::NearestFilterTexture()
	//	);
	//
	//addObject("enemy",
	//	glm::vec2(0.0f, 0.0f),
	//	0.0f, glm::vec2(0.75f, 0.75f),
	//	"Resources\\Textures\\alien01.png");
	//
	//addObject("enemy",
	//	glm::vec2(1.0f, 0.0f),
	//	0.0f, glm::vec2(0.75f, 0.75f),
	//	"Resources\\Textures\\alien01.png");
	//
	//addObject("enemy",
	//	glm::vec2(2.0f, 0.0f), 0.0f,
	//	glm::vec2(0.75f, 0.75f),
	//	"Resources\\Textures\\alien01.png");
	//
	//
	//GameObject2D* player1Object = getObject("player1");
	//
	//if (player1Object != nullptr) {
	//
	//	player1Object->position = glm::vec2(-1.0f, 1.0f);
	//	player1Object->orientation = glm::radians(90.0f);
	//	player1Object->size = glm::vec2(0.64f,0.64f);
	//	player1Object->textureID = loadTexture("Resources\\Textures\\player1_ship.png");
	//
	//}

	//GameObject2D* player2Object = getObject("Player2");
	//
	//if (player2Object != nullptr) {
	//
	//	player2Object->position = glm::vec2(1.5f, 1.0f);
	//	player2Object->orientation = glm::radians(45.0f);
	//	player2Object->textureID = loadTexture("Resources\\Textures\\bumblebee.png");
	//
	//}
	
	//float anglesPerSecond = glm::radians(45.0f);
	//
	//float playerVelocity = 2.0f;

	//set/update funtion before engineMainLoop

	//setUpdateFunction(myUpdate);

	setKeyboardHandler(myKeyboardHandler);

	//setRenderFunction(myRender);

	//setUpdateFunction(deleteSnowflakes, false);
	//setUpdateFunction(deleteAsteroids, false);
	setUpdateFunction(deleteObjects, false);

	//listGameObjectKeys(); // checks the number of objects rendered in the game

	// Enter main loop - this handles update and render calls
	engineMainLoop();	

	

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}


//void myUpdate(GLFWwindow* window, double tDelta)
//{
//
//	setViewplaneWidth(10.0f); //bigger number zoom out, smaller number zoom in, negative number flip upside down
//
//	static float playerSpeed = 1.0f; // distance per second
//
//	GameObject2D* player = getObject("player1");
//
//	if (keys.test(Key::W) == true)
//	{
//		player->position.y += playerSpeed * (float)tDelta;
//	}
//	else if (keys.test(Key::S) == true)
//	{
//		player->position.y -= playerSpeed * (float)tDelta;
//	}
//	else if (keys.test(Key::D) == true)
//	{
//		player->position.x += playerSpeed * (float)tDelta;
//	}
//	else if (keys.test(Key::A) == true)
//	{
//		player->position.x -= playerSpeed * (float)tDelta;
//	}
//
//	//float player1RotationSpeed = glm::radians(-90.0f);
//	//
//	//GameObject2D* player1Object = getObject("player1");
//	//
//	//player1Object->orientation += player1RotationSpeed * tDelta;
//	
//	//float player2RotationSpeed = glm::radians(90.0f);
//	//
//	//GameObject2D* player2Object = getObject("Player2");
//	//
//	//player2Object->orientation += player2RotationSpeed * tDelta;
//	
//	//GameObjectCollection players = getObjectCollection("player1");
//	//
//	//players.objectArray[0]->position.y = sinf(playerPhase[0]);
//	//playerPhase[0] += playerPhaseVelocity[0] * tDelta;
//
//
//	//enemy array
//	GameObjectCollection enemies = getObjectCollection("enemy");
//
//	//enemies.objectArray[0]->position.y = sinf(enemyPhase[0]);// assume phase stored in radians so no conversion needed
//	//enemyPhase[0] += enemyPhaseVelocity[0] * tDelta;
//
//	//move all enemies
//	for (int i = 0; i < enemies.objectCount; i++) 
//	{
//		enemies.objectArray[i]->position.y = sinf(enemyPhase[i]);
//		enemyPhase[i] += enemyPhaseVelocity[i] * tDelta;
//	}
//
//}

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
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

		case GLFW_KEY_LEFT_SHIFT:
			keys[Key::LEFTSHIFT] = true;
			break;

		case GLFW_KEY_SPACE:
			keys[Key::SPACE] = true;
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

		case GLFW_KEY_LEFT_SHIFT:
			keys[Key::LEFTSHIFT] = false;
			break;

		case GLFW_KEY_SPACE:
			keys[Key::SPACE] = false;
			break;
		}
	}
}

//void deleteSnowflakes(GLFWwindow* window, double tDelta)
//{
//	GameObjectCollection snowflakes = getObjectCollection("snowflake");
//
//	for (int i = 0; i < snowflakes.objectCount; i++)
//	{
//		if (snowflakes.objectArray[i]->position.y < -(getViewplaneHeight() / 2.0f))
//			deleteObject(snowflakes.objectArray[i]);
//
//	}
//}

//void deleteAsteroids(GLFWwindow* window, double tDelta)
//{
//	GameObjectCollection asteroids = getObjectCollection("asteroid");
//
//	for (int i = 0; i < asteroids.objectCount; i++)
//	{
//		if (asteroids.objectArray[i]->position.y < -getViewplaneHeight())
//			deleteObject(asteroids.objectArray[i]);
//
//	}
//
//}

//void myRender(GLFWwindow* window)
//{
//	glSetCurrentFont(myFontUnderline);
//	
//	glColor3f(1.0f, 1.0f, 1.0f);
//
//	glRasterPos2f(1.0f, 0.0f);
//
//	glPrint("Hello, World");
//}

//void displayScore(Player* player)
//{
//}

void deleteObjects(GLFWwindow* window, double tDelta)
{
	GameObjectCollection bullet = getObjectCollection("bullet");
	
	for (int i = 0; i < bullet.objectCount; i++)
	{
		if (bullet.objectArray[i]->position.y < -getViewplaneHeight() || bullet.objectArray[i]->position.y > getViewplaneHeight() || bullet.objectArray[i]->position.x < -getViewplaneWidth() || bullet.objectArray[i]->position.x > getViewplaneWidth())
		{
			deleteObject(bullet.objectArray[i]);
			printf("bullet delete\n");
		}
	}

	//GameObjectCollection asteroids = getObjectCollection("asteroid");
	//
	//for (int i = 0; i < asteroids.objectCount; i++)
	//{
	//	if (asteroids.objectArray[i]->position.y < -getViewplaneHeight())
	//		deleteObject(asteroids.objectArray[i]);
	//
	//}
}