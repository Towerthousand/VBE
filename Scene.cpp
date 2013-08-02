#include "Scene.hpp"
#include "Game.hpp"

Scene::Scene(Game &parent) : parent(parent) {}
Scene::~Scene() {}
RenderState& Scene::getState() const { return parent.state(); }
InputManager& Scene::getInputs() const { return parent.input(); }
TextureManager& Scene::getTextures() const { return parent.textures(); }
FontManager& Scene::getFonts() const { return parent.font(); }
AudioManager& Scene::getAudios() const { return parent.audio(); }
