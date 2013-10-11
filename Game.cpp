#include "Game.hpp"
#include "Manager.hpp"

Game* Game::instance = NULL;

Game::Game() :isRunning(true), root(NULL), idCounter(1) {
	VBE_ASSERT(Game::instance == NULL, "Two games created");
	Game::instance = this;
	VBE_LOG("* INIT GAME");

	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Default,CONTEXT_SETTINGS_OPENGL);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);

	isRunning = true;

	VBE_LOG("* INIT GAME SUCCESFUL");
}

Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	Textures.clear();
	Meshes.clear();
	AudioManager::clear();
	Programs.clear();
	window.close();
	isRunning = false;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

GameObject* Game::getObjectByName(std::string name) const {
	return nameMap.at(name);
}

GameObject* Game::getObjectByID(int id) const {
	return idMap.at(id);
}

// Main game loop
void Game::run() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	sf::Clock clock;
	while (isRunning) {
		float deltaTime = clock.restart().asSeconds();
		update(deltaTime);
		draw();
	}
	float deltaTime = clock.restart().asSeconds();
	update(deltaTime);
	draw();
}

// Set root for the scenegraph
void Game::setRoot(GameObject *newRoot) {
	VBE_ASSERT(root == NULL, "Root has already been set!");
	root = newRoot;
	root->addToGame();
}

// Update scenegraph
void Game::update(float deltaTime) {
	Input::update(isRunning,window);
	VBE_ASSERT(root != NULL, "Null scenegraph root");

	while(!objectTasksToRemove.empty()) {
		GameObject* obj = objectTasksToRemove.front();
		updateTasks.erase(obj);
		drawTasks.erase(obj);
		objectTasksToRemove.pop();
		if(!obj->isAlive) delete obj;
	}

	while(!objectTasksToAdd.empty()) {
		GameObject* obj = objectTasksToAdd.front();
		updateTasks.insert(obj);
		drawTasks.insert(obj);
		objectTasksToAdd.pop();
	}

	for(std::set<GameObject*,FunctorCompareUpdate>::iterator it = updateTasks.begin(); it != updateTasks.end(); ++it)
		(*it)->update(deltaTime);
}

// Draw scenegraph
void Game::draw() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	root->propragateTransforms();
	for(std::set<GameObject*,FunctorCompareDraw>::iterator it = drawTasks.begin(); it != drawTasks.end(); ++it)
		(*it)->draw();
	window.display();
}
