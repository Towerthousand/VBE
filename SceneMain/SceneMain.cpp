#include "SceneMain.hpp"
#include "Game.hpp"
#include "TriangleObject.hpp"

SceneMain::SceneMain(Game &parent) :
	Scene(parent),
	debugCounter(0.0), fpsCount(0) {
}

SceneMain::~SceneMain() {
}

bool SceneMain::loadResources() {
	//shaders
	ShaderProgram* s = new ShaderProgram();
	if(!s->makeProgram("shaders/sample.vert","shaders/sample.frag"))
		return false;
	shaders["SHADER"] = s;

	parent.font().makeText("FPS","",100,vec2f(10,30),sf::Color::White,sf::Text::Bold,false);

	return true;
}

bool SceneMain::init() {
	std::cout << "* Loading new scene: Main" << std::endl;
	if (!loadResources())
		return false;
	//Center mouse
	sf::Mouse::setPosition(sf::Vector2i(SCRWIDTH/2,SCRHEIGHT/2),parent.getWindow());
	//setup shaders
	getState().initShaderUniforms(getShader("SHADER"));
	//add a new triangle
	addObject(new TriangleObject(this,vec3f(0,0,0),vec3f(1)));
	std::cout << "* Init was succesful" << std::endl;
	return true;
}

void SceneMain::update(float deltaTime) {

	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		parent.font().getText("FPS").setString("FPS: " + toString(fpsCount));
		debugCounter -= 1;
		fpsCount = 0;
	}
	for(std::list<GameObject*>::iterator it = objects.begin();it != objects.end(); ++it) {
		(*it)->update(deltaTime);
	}
	//Erase dead game objects
	for(std::list<GameObject*>::iterator it = objects.begin(); it != objects.end();)
		if (!(*it)->isAlive) {
			std::list<GameObject*>::iterator it2 = it;
			++it2;
			delete *it;
			objects.erase(it);
			it = it2;
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
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	//SFML draws (until window.popGLStates())
	glDisable(GL_CULL_FACE);
	parent.getWindow().pushGLStates();
	parent.getWindow().draw(parent.font().getText("FPS"));
	parent.getWindow().popGLStates();
	glEnable(GL_CULL_FACE);
}

void SceneMain::onKeyPressed(float deltaTime, sf::Keyboard::Key key) {
	switch(key) {
		case sf::Keyboard::Escape:
			parent.close();
			break;
		default:
			break;
	}
}

void SceneMain::onKeyDown(float deltaTime, sf::Keyboard::Key key) {
	switch(key) {
		default:
			break;
	}
}

void SceneMain::onKeyReleased(float deltaTime, sf::Keyboard::Key key) {
	switch(key) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonPressed(float deltaTime, sf::Mouse::Button button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonDown(float deltaTime, sf::Mouse::Button button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonReleased(float deltaTime, sf::Mouse::Button button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseMoved(float deltaTime, int dx, int dy) {
}

void SceneMain::onClose() {
	std::cout << "* Deleting GameObjects on SceneMain" << std::endl;
	for(std::list<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		if(*it != NULL)
			delete *it;
	std::cout << "* Deleting Shader Programs on SceneMain" << std::endl;
	for(std::map<std::string,ShaderProgram*>::iterator it = shaders.begin(); it != shaders.end(); ++it)
		if((*it).second != NULL)
			delete (*it).second;
}

void SceneMain::addObject(GameObject* object) {
	objects.push_back(object);
}

const ShaderProgram &SceneMain::getShader(const std::string& ID) const {
	return *shaders.at(ID);
}
