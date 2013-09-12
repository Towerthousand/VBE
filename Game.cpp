#include "Game.hpp"

Game::Game() : currentScene(NULL), nextScene(NULL) {
	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Default,CONTEXT_SETTINGS_OPENGL);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	WINDOWFOCUS = true;
	glClearColor(0.0/255.0,0.0/255.0,0.0/255.0,1);
}

Game::~Game() {
	if (currentScene != NULL) {
		delete currentScene;
		currentScene = NULL;
	}
	std::cout << "* EXITING GAME" << std::endl;
	window.close();
}

// Init non-resource, general game frame stuff here.
bool Game::init() {
	std::cout << "* INIT GAME" << std::endl;

	//Load game-wide resources
	if (!loadResources())
		return false;
	isRunning = true;

	//GL stuff..
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);

	//initialise game-wide logic and objects
	std::cout << "* INIT GAME SUCCESFUL" << std::endl;
	return true;
}

// Load scene-independent resources here, return false if failed to load
bool Game::loadResources () {
	return true;
}

// Main game loop
void Game::run() {
	sf::Clock clock;
	while (isRunning) {
		float deltaTime = clock.restart().asSeconds();
		update(deltaTime);
		draw();
	}
}

// 1: Change scene if necessary
// 2: Update game-wide logic
// 3: Process input
// 4: Update scene
void Game::update(float deltaTime) {

	//Change scene, initialize it and close if it fails to initialize
	if (nextScene != NULL) {
		if (currentScene != NULL)
			delete currentScene;
		currentScene = nextScene;
		nextScene = NULL;
	}

	//Check window events. Events handled by main game object (scene-independent):
	// - Closing window
	// - Resizing window & viewport
	// - Updating window focus
	InputManager::update(isRunning,window);
	//Scene logic updating
	if (currentScene != NULL)
		currentScene->update(deltaTime);
}

// Draw scene
void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (currentScene != NULL)
		currentScene->draw();
	window.display();
}

// Change scene so that on next this->update(), this->currentScene will be replaced
void Game::setScene (Scene * scene) {
	if(nextScene != NULL)
		delete nextScene;
	nextScene = scene;
}
