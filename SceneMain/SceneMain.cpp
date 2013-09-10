#include "SceneMain.hpp"
#include "../Game.hpp"
#include "TriangleObject.hpp"
#include "RegularPolygonObject.hpp"

SceneMain::SceneMain(Game &parent) :
	Scene(parent), shaderExample(NULL),
	debugCounter(0.0), fpsCount(0) {
	//SCENE INIT
	std::cout << "* Loading new scene: Main" << std::endl;
	if (!loadResources()) {
		std::cout << "Could not load resources for SceneMain" << std::endl;
		parent.isRunning = false;
	}
	//Center mouse
	InputManager::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,parent.getWindow());
	//add a new triangle
	addObject(new       TriangleObject(this,shaderExample , vec3f( 1.0f, 0.0f,-3.0f), vec3f(1.0f)));
	addObject(new RegularPolygonObject(this,shaderExample2, vec3f(-1.0f, 0.0f,-3.0f), vec3f(1.0f), 6));
	std::cout << "* Init done" << std::endl;
}

SceneMain::~SceneMain() {
	//SECENE CLOSE
	std::cout << "* Deleting GameObjects on SceneMain" << std::endl;
	for(std::list<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		delete *it;
	if(shaderExample != NULL)
		delete shaderExample;
	if(shaderExample2 != NULL)
		delete shaderExample2;
}

bool SceneMain::loadResources() {
	//shaders
	ShaderProgram* s = new ShaderProgram();
	if(!s->makeProgram("data/shaders/sample.vert","data/shaders/sample.frag"))
		return false;
	shaderExample = s;

	ShaderProgram* s2 = new ShaderProgram();
	if(!s2->makeProgram("data/shaders/sample2.vert","data/shaders/sample2.frag"))
		return false;
	shaderExample2 = s2;
	//textures
	if(!TextureManager::loadTexture("textest","data/tex.png"))
		return false;
	if(!TextureManager::loadTexture("textest2","data/tex2.png"))
		return false;
	return true;
}

void SceneMain::update(float deltaTime) {

	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		std::cout << "FPS: " << fpsCount << ". Amount of GameObjects: " << objects.size() << std::endl;
		debugCounter -= 1;
		fpsCount = 0;
	}
	for(std::list<GameObject*>::iterator it = objects.begin();it != objects.end(); ++it) {
		(*it)->update(deltaTime);
	}
	//Erase dead game objects
	for(std::list<GameObject*>::iterator it = objects.begin(); it != objects.end();)
		if (!(*it)->isAlive) {
			delete *it;
			it = objects.erase(it);;
		}
		else
			++it;
}

void SceneMain::draw() const {
	//calculate perspective matrix
	getState().projection = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT),ZNEAR,ZFAR);
	//Move matrix to position (according to player)
	getState().view = mat4f(1.0);
	//models
	for(std::list<GameObject*>::const_iterator it = objects.begin();it != objects.end(); ++it)
		(*it)->draw();
}

