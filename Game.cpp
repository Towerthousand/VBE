#include "Game.hpp"

Game::Game() : root(NULL){
	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Default,CONTEXT_SETTINGS_OPENGL);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	WINDOWFOCUS = true;
	glClearColor(0.0/255.0,0.0/255.0,0.0/255.0,1);
}

Game::~Game() {
	if(root != NULL)
		delete root;
	std::cout << "* EXITING GAME" << std::endl;
	window.close();
}

// Init non-resource, general game stuff here.
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

// Set root for the scenegraph
void Game::setRoot(GameObject *newRoot) {
	if(root != NULL) delete root;
	root = newRoot;
}

// Update scenegraph
void Game::update(float deltaTime) {
	InputManager::update(isRunning,window);
	if(root != NULL)
		root->update(deltaTime);
}

// Draw scenegraph
void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(root != NULL)
		root->draw();
	window.display();
}
