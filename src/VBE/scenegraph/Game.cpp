#include <VBE/scenegraph/Game.hpp>
#include <VBE/system/Clock.hpp>
#include <VBE/system/Window.hpp>
#include <VBE/system/Log.hpp>

Game* Game::instance = nullptr;

Game::Game() :isRunning(true), idCounter(1), fixedUpdateRate(0), isFixedUpdateRate(false) {
	VBE_ASSERT(Game::instance == nullptr, "Two games created");
	Game::instance = this;
	isRunning = true;
	VBE_LOG("* INIT GAME");
}

Game::~Game() {
	//Free resources, delete scenegraph nodes and close windows
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	isRunning = false;
	Game::instance = nullptr;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}

void Game::update(float deltaTime) {
	Window::getInstance()->update();
	ContainerObject::update(deltaTime);
}

void Game::draw() {
	ContainerObject::draw();
	Window::getInstance()->swapBuffers();
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
		float time = Clock::getSeconds();
		float accumulated = 0.0f;
		float newTime = 0.0f;
		while (isRunning) {
			if(accumulated < deltaTime) 
				Clock::sleepSeconds(deltaTime-accumulated);//miliseconds to wait
			newTime = Clock::getSeconds();
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
		float time = Clock::getSeconds();
		while (isRunning) {
			float newTime = Clock::getSeconds();
			float deltaTime = newTime-time;
			time = newTime;
			update(deltaTime);
			draw();
		}
	}
}
