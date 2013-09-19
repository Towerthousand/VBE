#include "SceneMain.hpp"
#include "../Game.hpp"
#include "TexturedObject.hpp"
#include "RegularPolygonObject.hpp"

SceneMain::SceneMain() :
	GameObject(NULL,vec3f(0.0),vec3f(1.0)),
	debugCounter(0.0), fpsCount(0) {
	this->setName("SCENE");
	//SCENE INIT
	std::cout << "* Loading new scene: Main" << std::endl;
	if (!loadResources()) {
		std::cout << "Could not load resources for SceneMain" << std::endl;
		Game::s_isRunning = false;
		return;
	}
	//Center mouse
	InputManager::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,Game::getWindow());
	//add a new triangle
	RegularPolygonObject* poly = new RegularPolygonObject(this, vec3f(-1.0f, 0.0f,-3.0f), vec3f(1.0f), 6);
	addObject(poly);
	TexturedObject* house = new TexturedObject(poly,vec3f(0,-10,0),vec3f(0.5));
	poly->setDrawPriority(0);
	poly->addObject(house);
	addObject(new TexturedObject(this, vec3f( 1.0f, 0.0f,-3.0f), vec3f(0.5f)));

	std::cout << "* Init done" << std::endl;
}

SceneMain::~SceneMain() {
	std::cout << "* Deleting resources on Main scene" << std::endl;
	TextureManager::clear();
	MeshManager::clear();
	ShaderManager::clear();
	std::cout << "* Exiting Main scene" << std::endl;
}

bool SceneMain::loadResources() {
	//shaders
	if(!ShaderManager::load("sample","data/shaders/sample.vert","data/shaders/sample.frag"))
		return false;
	if(!ShaderManager::load("sample2","data/shaders/sample2.vert","data/shaders/sample2.frag"))
		return false;
	//textures
	if(!TextureManager::load("cubetex","data/10x10tex.png",2))
		return false;
	//Create meshes
	MeshManager::add("cube",new Mesh("data/10x10.obj"));
	return true;
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		std::cout << "FPS: " << fpsCount << ". Amount of GameObjects: " << GameObject::getObjectCount() << std::endl;
		debugCounter -= 1;
		fpsCount = 0;
	}
}

void SceneMain::draw() const {
	//calculate perspective matrix
	RenderState::s_projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	//Move matrix to position (according to player)
	RenderState::s_view = glm::translate(mat4f(1.0),vec3f(0,0,-10));
}

