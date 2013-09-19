#include "Game.hpp"

bool Game::isRunning = false;
int Game::drawLayer = 0;
sf::RenderWindow Game::window;
GameObject* Game::root = NULL;
std::priority_queue<std::pair<int,Game::DrawTask>,std::vector<std::pair<int,Game::DrawTask>>,Game::FunctorCompare> Game::priorityDraws;

Game::Game(){
}

Game::~Game() {
}

// Init non-resource, general game stuff here.
bool Game::init() {
	std::cout << "* INIT GAME" << std::endl;

	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Default,CONTEXT_SETTINGS_OPENGL);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	glClearColor(0.0/255.0,0.0/255.0,0.0/255.0,1);

	//Load game-wide resources
	if (!loadResources())
		return false;
	isRunning = true;

	//GL stuff..: root(NULL)
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

// Postpone a part of the scenegraph for late drawing
void Game::addDrawTask(RenderState::RenderInstance state, GameObject* object) {
	DrawTask task(state,object);
	priorityDraws.push(std::pair<int,DrawTask>(object->drawPriority,task));
}

// Update scenegraph
void Game::update(float deltaTime) {
	InputManager::update(isRunning,window);
	if(root != NULL)
		root->doUpdate(deltaTime);
}

// Draw scenegraph
void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawLayer = 0;
	RenderState::reset();
	if(root != NULL) //first pass (drawPriority of 0)
		root->doDraw();
	while(!priorityDraws.empty()) { //other drawPriorities
		++drawLayer;
		while(!priorityDraws.empty() && priorityDraws.top().first == drawLayer) {
			DrawTask task = priorityDraws.top().second;
			RenderState::setState(task.state);
			task.object->doDraw();
			priorityDraws.pop();
		}
	}
	window.display();
}

//Free resources, delete scenegraph nodes and close windows
void Game::close() {
	isRunning = false;
	if(root != NULL)
		delete root;
	std::cout << "* EXITING GAME" << std::endl;
	window.close();
}
