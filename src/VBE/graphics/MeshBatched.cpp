#include <VBE/graphics/MeshBatched.hpp>
#include <algorithm>
#include <VBE/system/Log.hpp>

bool MeshBatched::batching = false;
std::vector<MeshBatched::DrawIndirectCommand> MeshBatched::commands;
std::vector<MeshBatched::MeshBatch*> MeshBatched::batches;

MeshBatched::MeshBatched(const Vertex::Format& format) : MeshBase(format, DYNAMIC) {
	//TODO
}

MeshBatched::~MeshBatched() {
	//TODO
}

MeshBatched::MeshBatched(MeshBatched&& rhs) : MeshBase(Vertex::Format(std::vector<Vertex::Element>())) {
	using std::swap;
	swap(*this, rhs);
}

MeshBatched& MeshBatched::operator=(MeshBatched&& rhs) {
	using std::swap;
	swap(*this, rhs);
	return *this;
}

void MeshBatched::draw(const ShaderProgram* program) {
	draw(program, 0, vertexCount);
}

void MeshBatched::draw(const ShaderProgram* program, unsigned int userData) {
	draw(program, 0, vertexCount, userData);
}

void MeshBatched::draw(const ShaderProgram* program, unsigned int offset, unsigned int length) {
	//TODO
}

void MeshBatched::draw(const ShaderProgram* program, unsigned int offset, unsigned int length, unsigned int userData) {
	//TODO
}

void MeshBatched::setVertexData(const void* vertexData, unsigned int newVertexCount) {
	//TODO
}

void MeshBatched::resetBatch() {
	commands.clear();
}

void MeshBatched::startBatch() {
	VBE_ASSERT(!batching, "Cannot start a new batch without ending the previous one.");
	resetBatch();
	batching = true;
}

void MeshBatched::endBatch() {
	VBE_ASSERT(batching, "Cannot end a batch that wasn't started.");
	batching = false;
	//TODO
}

void swap(MeshBatched& a, MeshBatched& b) {
	//TODO
}

MeshBatched::MeshBatch::MeshBatch(const Vertex::Format& format) : format(format) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer));
}

MeshBatched::MeshBatch::~MeshBatch() {
	GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
}
