#include "Game.hpp"
#include "Manager.hpp"
#include "audio/AudioManager.hpp"
#include "input/Input.hpp"

Game* Game::instance = nullptr;

Game::Game() :isRunning(true), idCounter(1) {
	VBE_ASSERT(Game::instance == nullptr, "Two games created");
	Game::instance = this;
	VBE_LOG("* INIT GAME");

	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE, sf::Style::Default, CONTEXT_SETTINGS_OPENGL);
	SCRWIDTH = window.getSize().x;
	SCRHEIGHT = window.getSize().y;
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

void Game::update(float deltaTime) {
	Input::update(isRunning,window);
	ContainerObject::update(deltaTime);
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ContainerObject::draw();
	window.display();
}

GameObject* Game::getObjectByName(std::string name) const {
	VBE_ASSERT(nameMap.find(name) != nameMap.end(),"There is no object named " << name);
	return nameMap.at(name);
}

GameObject* Game::getObjectByID(int id) const {
	VBE_ASSERT(idMap.find(id) != idMap.end(),"There is no object with id " << id);
	return idMap.at(id);
}

// Main game loop
void Game::run() {
	sf::Clock clock;
	while (isRunning) {
		float deltaTime = clock.restart().asSeconds();
		update(deltaTime);
		draw();
	}
	update(0.1f);
}
