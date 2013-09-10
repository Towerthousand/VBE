#include "Scene.hpp"
#include "Game.hpp"

Scene::Scene(Game &parent) : GameObject(NULL,vec3f(0.0),vec3f(1.0)), parent(parent) {}
Scene::~Scene() {}
void Scene::addObject(GameObject *object) {objects.push_back(object);}
RenderState& Scene::getState() const { return state; }
