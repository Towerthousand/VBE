#include "Game.hpp"

bool Game::isRunning = false;

sf::RenderWindow Game::window;
GameObject* Game::root = NULL;
std::set<GameObject*,Game::FunctorCompare> Game::drawTasks;

Game::Game(){
}

Game::~Game() {
}

// Init non-resource, general game stuff here.
bool Game::init() {
	VBE_LOG("* INIT GAME");

	window.create(sf::VideoMode(SCRWIDTH,SCRHEIGHT,32), WINDOW_TITLE ,sf::Style::Default,CONTEXT_SETTINGS_OPENGL);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(false);

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
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);

	VBE_LOG("* INIT GAME SUCCESFUL");
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
	close();
}

// Set root for the scenegraph
void Game::setRoot(GameObject *newRoot) {
	if(root != NULL) delete root;
	root = newRoot;
}

// Update scenegraph
void Game::update(float deltaTime) {
	InputManager::update(isRunning,window);
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	root->doUpdate(deltaTime);
	//int nulls = 0;
	//if(!GameObject::checkTree(Game::root, nulls))
	//	VBE_ASSERT(0,"SCENEGRAPH ERROR!");
}

// Draw scenegraph
void Game::draw() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	root->calcFullTransform(mat4f(1.0f));
	for(std::set<GameObject*,FunctorCompare>::iterator it = drawTasks.begin(); it != drawTasks.end(); ++it)
		(*it)->draw();
	window.display();
}

//Free resources, delete scenegraph nodes and close windows
void Game::close() {
	VBE_ASSERT(root != NULL, "Null scenegraph root");
	delete root;
	root = NULL;
	VBE_LOG("* EXITING GAME: CLEARING RESOURCES" );
	TextureManager::clear();
	MeshManager::clear();
	AudioManager::clear();
	ShaderManager::clear();
	window.close();
	isRunning = false;
	VBE_LOG("* EXIT GAME SUCCESFUL" );
}
