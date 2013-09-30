#include "SceneMain.hpp"
#include "../Game.hpp"
#include "TexturedObject.hpp"
#include "RegularPolygonObject.hpp"
#include "PerspectiveCamera.hpp"

SceneMain::SceneMain() : debugCounter(0.0), fpsCount(0) {
	this->setName("SCENE");
	//SCENE INIT
	if (!loadResources()) {
		VBE_LOG("Could not load resources for SceneMain" );
		Game::isRunning = false;
		return;
	}
	//Center mouse
	InputManager::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,Game::getWindow());

	PerspectiveCamera* cam = new PerspectiveCamera(vec3f(0,0,-10));
	RegularPolygonObject* poly = new RegularPolygonObject(vec3f(-1.0f, 0.0f,-3.0f), vec3f(1.0f), 6);
	cam->addObject(poly);
	TexturedObject* house = new TexturedObject(vec3f(0,-10,0),vec3f(0.5f));
	TexturedObject* house2 = new TexturedObject(vec3f( 1.0f, 0.0f,-3.0f), vec3f(0.5f));
	poly->addObject(house);
	cam->addObject(house2);
	addObject(cam);
	house->setDrawPriority(0);
	house2->setDrawPriority(1);
}

SceneMain::~SceneMain() {
	TextureManager::clear();
	MeshManager::clear();
	ShaderManager::clear();
	AudioManager::clear();
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
	struct rgba {
			rgba() : r(255), g(255), b(255), a(255) {}
			~rgba() {}
			unsigned char r,g,b,a;
	};

	std::vector<rgba> pixels(4,rgba());
	pixels[0].g = pixels[0].b = pixels[3].g = pixels[3].b = 0;
	if(!TextureManager::loadRaw("lol",&pixels[0],2,2,5))
		return false;
	//Create meshes
	MeshManager::add("cube",new Mesh("data/10x10.obj"));
	return true;
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		VBE_LOG("FPS: " << fpsCount << ". Amount of GameObjects: " << GameObject::getObjectCount() );
		debugCounter--;
		fpsCount = 0;
	}
}


