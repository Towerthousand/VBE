#include "SceneMain.hpp"
#include "../Game.hpp"
#include "TriangleObject.hpp"
#include "RegularPolygonObject.hpp"

SceneMain::SceneMain(Game &parent) :
	Scene(parent),
	debugCounter(0.0), fpsCount(0) {
	//SCENE INIT
	std::cout << "* Loading new scene: Main" << std::endl;
	if (!loadResources()) {
		std::cout << "Could not load resources for SceneMain" << std::endl;
		parent.isRunning = false;
		return;
	}
	//Center mouse
	InputManager::setMousePos(SCRWIDTH/2,SCRHEIGHT/2,parent.getWindow());
	//add a new triangle
	addObject(new       TriangleObject(this , vec3f( 1.0f, 0.0f,-3.0f), vec3f(1.0f)));
	addObject(new RegularPolygonObject(this, vec3f(-1.0f, 0.0f,-3.0f), vec3f(1.0f), 6));
	std::cout << "* Init done" << std::endl;
}

SceneMain::~SceneMain() {
	//SECENE CLOSE
	std::cout << "* Deleting GameObjects on SceneMain" << std::endl;
	for(std::list<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		delete *it;
}

bool SceneMain::loadResources() {
	//shaders
	ShaderProgram* s = new ShaderProgram();
	if(!s->makeProgram("data/shaders/sample.vert","data/shaders/sample.frag"))
		return false;
	ShaderManager::add("sample",s);

	s = new ShaderProgram();
	if(!s->makeProgram("data/shaders/sample2.vert","data/shaders/sample2.frag"))
		return false;
	ShaderManager::add("sample2",s);
	//textures
	if(!TextureManager::loadTexture("textest","data/tex.png"))
		return false;
	if(!TextureManager::loadTexture("textest2","data/tex2.png"))
		return false;
	//Create meshes
	std::vector<Vertex::Element> elements;
	elements.push_back(Vertex::Element(Vertex::Attribute::Position , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::Color    , Vertex::Element::Float, 3));
	elements.push_back(Vertex::Element(Vertex::Attribute::TexCoord , Vertex::Element::Float, 2));

	struct Vert {
			Vert(vec3f pos, vec3f color, vec2f tex) : pos(pos) , color(color), tex(tex) {}
			vec3f pos,color;
			vec2f tex;
	};

	std::vector<Vert> data;
	data.push_back(Vert(vec3f(-1.0, -1.0,  0.0), vec3f(0.0, 0.0, 1.0), vec2f(0.0,10.0)));
	data.push_back(Vert(vec3f( 1.0, -1.0,  0.0), vec3f(0.0, 1.0, 0.0), vec2f(10.0,10.0)));
	data.push_back(Vert(vec3f(-1.0,  1.0,  0.0), vec3f(1.0, 0.0, 0.0), vec2f(0.0,0.0)));
	data.push_back(Vert(vec3f( 1.0, -1.0,  0.0), vec3f(0.0, 1.0, 0.0), vec2f(10.0,10.0)));
	data.push_back(Vert(vec3f( 1.0,  1.0,  0.0), vec3f(0.0, 0.0, 1.0), vec2f(10.0,0.0)));
	data.push_back(Vert(vec3f(-1.0,  1.0,  0.0), vec3f(1.0, 0.0, 0.0), vec2f(0.0,0.0)));

	Mesh* mesh = new Mesh(Vertex::Format(elements),0,false);
	mesh->setVertexData(&data[0],data.size());
	MeshManager::add("tri",mesh);
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

