#include "Game.hpp"
#include "../utils/Manager.hpp"
#include "../environment/Environment.hpp"

Game* Game::instance = nullptr;

Game::Game() :isRunning(true), idCounter(1), fixedFramerate(0), isFixedFramerate(false) {
	VBE_ASSERT(Game::instance == nullptr, "Two games created");
	Game::instance = this;
	VBE_LOG("* INIT GAME");
	isRunning = true;
}

Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	Textures2D.clear();
	Meshes.clear();
	Programs.clear();
	isRunning = false;
	Game::instance = nullptr;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

void Game::update(float deltaTime) {
	Environment::update();
	ContainerObject::update(deltaTime);
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ContainerObject::draw();
	Environment::getScreen()->swapBuffers();
}

GameObject* Game::getObjectByName(std::string name) const {
	VBE_ASSERT(nameMap.find(name) != nameMap.end(), "There is no object named " << name);
	return nameMap.at(name);
}

GameObject* Game::getObjectByID(int id) const {
	VBE_ASSERT(idMap.find(id) != idMap.end(), "There is no object with id " << id);
	return idMap.at(id);
}

void Game::setFixedFramerate(int fixedFramerate) {
	this->fixedFramerate = fixedFramerate;
	this->isFixedFramerate = true;
}

void Game::setDynamicFramerate() {
	isFixedFramerate = false;
}

// Main game loop
void Game::run() {


	if(isFixedFramerate) {
//		window.setFramerateLimit(fixedFramerate);
		float deltaTime = 1.0f/float(fixedFramerate);
		while (isRunning) {
			update(deltaTime);
			draw();
		}
	}
	else {
		float time = Environment::getClock();

		while (isRunning) {
			float newTime = Environment::getClock();
			float deltaTime = newTime-time;
			time = newTime;

			update(deltaTime);
			draw();
		}
	}
}
