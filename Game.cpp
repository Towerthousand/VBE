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

	glClearColor(0.1,0.2,0.05,1);

	//Load game-wide resources
	if(!loadResources())
			VBE_ASSERT(false,"Could not load resources");
	isRunning = true;

	//GL stuff..: root(NULL)
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);

	VBE_LOG("* INIT GAME SUCCESFUL");
}


Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows
	VBE_ASSERT(Game::instance == this, "Two games created");
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	delete root;
	root = NULL;
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	Textures.clear();
	Meshes.clear();
	AudioManager::clear();
	Programs.clear();
	window.close();
	isRunning = false;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

// Load scene-independent resources here, return false if failed to load
bool Game::loadResources () {
	return true;
}

GameObject* Game::getObjectByName(std::string name) {
	return nameMap.at(name);
}

GameObject* Game::getObjectByID(int id) {
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
}

// Set root for the scenegraph
void Game::setRoot(GameObject *newRoot) {
	if(root != NULL)
		root->removeFromGame();

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
	//int nulls = 0;
	//if(!GameObject::checkTree(Game::root, nulls))
	//	VBE_ASSERT(0,"SCENEGRAPH ERROR!");
}

// Draw scenegraph
void Game::draw() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	root->calcFullTransform(mat4f(1.0f));
	for(std::set<GameObject*,FunctorCompareDraw>::iterator it = drawTasks.begin(); it != drawTasks.end(); ++it)
		(*it)->draw();
	window.display();
}
