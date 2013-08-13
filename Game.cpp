#include "Game.hpp"

Game::Game() : currentScene(NULL), nextScene(NULL) {
	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Default,CONTEXT_SETTINGS_OPENGL);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);
	WINDOWFOCUS = true;
	glClearColor(0.0/255.0,0.0/255.0,0.0/255.0,1);
}

Game::~Game() {
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
	glEnable(GL_RESCALE_NORMAL);

	//initialise game-wide logic and objects
	std::cout << "* INIT GAME SUCCESFUL" << std::endl;
	return true;
}

// Load scene-independent resources here, return false if failed to load
bool Game::loadResources () {
	if (!fontManager.globalFont.loadFromFile("resources/helvetica.ttf"))
		return false;
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
		if (!currentScene->init()) {
			close();
		}
	}

	//Check window events. Events handled by main game object (scene-independent):
	// - Closing window
	// - Resizing window & viewport
	// - Updating window focus
	inputManager.update();
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				close();
				break;
			case sf::Event::Resized:
				inputManager.resizeWindow(event.size.height,event.size.width,
										  renderState.projection);
				break;
			case sf::Event::GainedFocus:
				inputManager.gainFocus();
				break;
			case sf::Event::LostFocus:
				inputManager.loseFocus();
				break;
			case sf::Event::MouseButtonPressed:
				inputManager.pressMouse(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				inputManager.releaseMouse(event.mouseButton.button);
				break;
			case sf::Event::MouseMoved:
				inputManager.moveMouse(event.mouseMove.x,event.mouseMove.y);
				break;
			case sf::Event::KeyPressed:
				inputManager.pressKey(event.key.code);
				break;
			case sf::Event::KeyReleased:
				inputManager.releaseKey(event.key.code);
				break;
			default:
				break;
		}
	}
	//pass the key input to the scene
	for (std::set<sf::Keyboard::Key>::iterator it=inputManager.keysPressed.begin(); it!=inputManager.keysPressed.end(); ++it) {
			onKeyPressed(deltaTime,*it);
	}
	for (std::set<sf::Keyboard::Key>::iterator it=inputManager.keysDown.begin(); it!=inputManager.keysDown.end(); ++it) {
			onKeyDown(deltaTime,*it);
	}
	for (std::set<sf::Keyboard::Key>::iterator it=inputManager.keysReleased.begin(); it!=inputManager.keysReleased.end(); ++it) {
			onKeyReleased(deltaTime,*it);
	}
	//pass the mouse input to the scene
	if(inputManager.mouseDisplacement != vec2i(0,0))
		onMouseMoved(deltaTime,inputManager.mouseDisplacement.x,inputManager.mouseDisplacement.y);
	for (std::set<sf::Mouse::Button>::iterator it=inputManager.mouseButtonsPressed.begin();
		 it!=inputManager.mouseButtonsPressed.end(); ++it) {
			onMouseButtonPressed(deltaTime,*it);
	}
	for (std::set<sf::Mouse::Button>::iterator it=inputManager.mouseButtonsDown.begin();
		 it!=inputManager.mouseButtonsDown.end(); ++it) {
			onMouseButtonDown(deltaTime,*it);
	}
	for (std::set<sf::Mouse::Button>::iterator it=inputManager.mouseButtonsReleased.begin();
		 it!=inputManager.mouseButtonsReleased.end(); ++it) {
			onMouseButtonReleased(deltaTime,*it);
	}

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

void Game::onKeyPressed(float deltaTime, const sf::Keyboard::Key &key) {
	if (currentScene != NULL)
		currentScene->onKeyPressed(deltaTime, key);
}

void Game::onKeyDown(float deltaTime, const sf::Keyboard::Key &key) {
	if (currentScene != NULL)
		currentScene->onKeyDown(deltaTime, key);
}

void Game::onKeyReleased(float deltaTime, const sf::Keyboard::Key &key) {
	if (currentScene != NULL)
		currentScene->onKeyReleased(deltaTime, key);
}

void Game::onMouseButtonPressed(float deltaTime, const sf::Mouse::Button &button) {
	if (currentScene != NULL)
		currentScene->onMouseButtonPressed(deltaTime, button);
}

void Game::onMouseButtonDown(float deltaTime, const sf::Mouse::Button &button) {
	if (currentScene != NULL)
		currentScene->onMouseButtonDown(deltaTime, button);
}

void Game::onMouseButtonReleased(float deltaTime, const sf::Mouse::Button &button) {
	if (currentScene != NULL)
		currentScene->onMouseButtonReleased(deltaTime, button);
}

void Game::onMouseMoved(float deltaTime, int dx, int dy) {
	if (currentScene != NULL)
		currentScene->onMouseMoved(deltaTime,dx,dy);
}

// Whenever you want to end the game, you must call this function, not the Scene's onClose(); method
// End game-wide stuff here
void Game::close() {
	if (currentScene != NULL) {
		currentScene->onClose();
		delete currentScene;
		currentScene = NULL;
	}
	std::cout << "* EXITING GAME" << std::endl;
	window.close();
	isRunning = false;
}

// Change scene so that on next this->update(), this->currentScene will be replaced
void Game::setScene (Scene * scene) {
	if(nextScene != NULL)
		delete nextScene;
	nextScene = scene;
}
