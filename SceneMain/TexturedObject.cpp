#include "TexturedObject.hpp"
#include "../Game.hpp"
#include "RegularPolygonObject.hpp"

TexturedObject::TexturedObject(GameObject* parent,  const vec3f &pos, const vec3f &scale) : GameObject(parent,pos,scale) {
	m_tri.m_mesh = MeshManager::get("cube");
	m_tri.m_program = ShaderManager::get("sample");
}

TexturedObject::~TexturedObject() {
}

void TexturedObject::update(float deltaTime) {
	(void) deltaTime;
	updateMatrix();
}

void TexturedObject::updateMatrix() {
	mat4f m(1.0);
	m = glm::translate(m,m_pos);
	m = glm::scale(m,m_scale);
	m_tri.m_modelMatrix = m;
}

void TexturedObject::draw() const {
	RenderState::s_model *= m_tri.m_modelMatrix;
	mat4f transform = RenderState::s_projection*RenderState::s_view*RenderState::s_model;
	m_tri.m_program->uniform("sampler")->set(TextureManager::get("cubetex"));
	m_tri.m_program->uniform("modelViewProjectionMatrix")->set(transform);
	m_tri.draw();
}
