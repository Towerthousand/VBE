#include "Game.hpp"
#include "../utils/Manager.hpp"
#include "../environment/Environment.hpp"

Game* Game::instance = nullptr;

Game::Game() :isRunning(true), idCounter(1), fixedUpdateRate(0), isFixedUpdateRate(false) {
	VBE_ASSERT(Game::instance == nullptr, "Two games created");
	Environment::startUp();
	Game::instance = this;
	isRunning = true;
	VBE_LOG("* INIT GAME");
}

Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	Textures2D.clear();
	Meshes.clear();
	Programs.clear();
	isRunning = false;
	Game::instance = nullptr;
	Environment::shutDown();
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

void Game::update(float deltaTime) {
	Environment::update();
	ContainerObject::update(deltaTime);
}

void Game::draw() {
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

void Game::setFixedUpdateRate(int fixedFramerate) {
	this->fixedUpdateRate = fixedFramerate;
	this->isFixedUpdateRate = true;
}

void Game::setDynamicFramerate() {
	isFixedUpdateRate = false;
}

// Main game loop
void Game::run() {
	if(isFixedUpdateRate) {
		float deltaTime = 1.0f/float(fixedUpdateRate);
		float time = Environment::getClock();
		float accumulated = 0.0f;
		float newTime = 0.0f;
		while (isRunning) {
			if(accumulated < deltaTime) 
				SDL_Delay((deltaTime-accumulated)*1000);//miliseconds to wait
			newTime = Environment::getClock();
			accumulated = newTime-time;
			time = newTime;
			while(accumulated >= deltaTime) {
				update(deltaTime);
				accumulated -= deltaTime;
			}
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
