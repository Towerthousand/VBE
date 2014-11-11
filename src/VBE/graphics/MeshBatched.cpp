#include <VBE/graphics/MeshBatched.hpp>
#include <algorithm>
#include <VBE/system/Log.hpp>
#include "ShaderBinding.hpp"

bool MeshBatched::batching = false;
ShaderProgram* MeshBatched::batchingProgram = nullptr;
std::vector<MeshBatched::DrawIndirectCommand> MeshBatched::commands;
std::set<MeshBatched::Buffer*> MeshBatched::batches;

MeshBatched::MeshBatched(const Vertex::Format& format) : MeshBase(format, STREAM) {
	Buffer* b = getBuffer();
	if(b == nullptr) {
		b = new Buffer(format);
		batches.insert(b);
	}
	b->addMesh(this);
}

MeshBatched::~MeshBatched() {
	Buffer* b = getBuffer();
	b->deleteMesh(this);
	if(b->getMeshCount() == 0) {
		batches.erase(b);
		delete b;
	}
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
	VBE_ASSERT(program != nullptr, "program cannot be null");
	VBE_ASSERT(program->getHandle() != 0, "program cannot be null");
	VBE_ASSERT(length != 0, "length must not be zero");
	VBE_ASSERT(offset < getVertexCount(), "offset must be smaller than vertex count");
	VBE_ASSERT(offset + length <= getVertexCount(), "offset plus length must be smaller or equal to vertex count");

	Buffer* b = getBuffer();
	b->setupBinding(program);

	GL_ASSERT(glDrawArrays(getPrimitiveType(), b->getMeshOffset(this), length));
}

void MeshBatched::draw(const ShaderProgram* program, unsigned int offset, unsigned int length, unsigned int userData) {
	//TODO
}

void MeshBatched::setVertexData(const void* vertexData, unsigned int newVertexCount) {
	Buffer* b = getBuffer();
	vertexCount = newVertexCount;
	b->submitData(this, vertexData, newVertexCount);
}

void MeshBatched::resetBatch() {
	commands.clear();
}

void MeshBatched::startBatch() {
	VBE_ASSERT(!batching, "Cannot start a new batch without ending the previous one.");
	resetBatch();
	batching = true;
	//TODO
}

void MeshBatched::endBatch() {
	VBE_ASSERT(batching, "Cannot end a batch that wasn't started.");
	batching = false;
	//TODO
}

MeshBatched::Buffer* MeshBatched::getBuffer() const {
	for(Buffer* b : batches)
		if(b->bufferFormat == getVertexFormat())
			return b;
	return nullptr;
}

void swap(MeshBatched& a, MeshBatched& b) {
	using std::swap;
	swap(static_cast<MeshBase&>(a), static_cast<MeshBase&>(b));
}

MeshBatched::Buffer::Buffer(const Vertex::Format& format)
	: bufferFormat(format),
	  vertexBuffer(0),
	  totalBufferSize(1 << 10) {
	GL_ASSERT(glGenBuffers(1, &vertexBuffer));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, totalBufferSize*bufferFormat.vertexSize(), 0, MeshBase::STREAM));
	freeInterval(Interval(0, 1 << 10));
}

MeshBatched::Buffer::~Buffer() {
	GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
}

void MeshBatched::Buffer::addMesh(MeshBatched* mesh) {
	usedIntervals.insert(std::pair<MeshBatched*, Interval>(mesh, Interval(0,0)));
}

void MeshBatched::Buffer::deleteMesh(MeshBatched* mesh) {
	freeInterval(usedIntervals.at(mesh));
	usedIntervals.erase(mesh);
}

void MeshBatched::Buffer::submitData(MeshBatched* mesh, const void* data, unsigned int vCount) {
	Interval& i = usedIntervals.at(mesh);
	freeInterval(i);
	i = Interval(0,0);
	i = allocateInterval(vCount);
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GL_ASSERT(glBufferSubData(GL_ARRAY_BUFFER, i.start*bufferFormat.vertexSize(), vCount*bufferFormat.vertexSize(), data));
}

unsigned int MeshBatched::Buffer::getMeshCount() {
	return usedIntervals.size();
}

unsigned long MeshBatched::Buffer::getMeshOffset(MeshBatched* mesh) {
	return usedIntervals.at(mesh).start;
}

void MeshBatched::Buffer::setupBinding(const ShaderProgram* program) {
	// Get the binding from the cache. If it does not exist, create it.
	GLuint handle = program->getHandle();
	if(bindings.find(handle) == bindings.end())
		bindings.insert(std::pair<GLuint, const ShaderBinding*>(handle, new ShaderBinding(program, this)));
	const ShaderBinding* binding = bindings.at(handle);

	// Bind the program and the binding
	program->use();
	ShaderBinding::bind(binding);
}

void MeshBatched::Buffer::bindBuffers() const {
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
}

void MeshBatched::Buffer::freeInterval(Interval i) {
	VBE_ASSERT(i.start + i.count <= totalBufferSize, "Free out of bounds GPU memory");
	if(i.count == 0) return;
	bool merged = false;
	//merge with previous one if possible
	std::set<Interval>::iterator lower = std::lower_bound(freeIntervals.begin(), freeIntervals.end(), i);
	if(lower != freeIntervals.end() && lower != freeIntervals.begin()) {
		--lower;
		Interval previous = *lower;
		if(previous.start + previous.count == i.start) {
			freeIntervals.erase(previous);
			previous.count += i.count;
			freeIntervals.insert(previous);
			i = previous;
			merged = true;
		}
	}
	//merge with next one if possible
	std::set<Interval>::iterator upper = std::upper_bound(freeIntervals.begin(), freeIntervals.end(), i);
	if(upper != freeIntervals.end()) {
		Interval next = *upper;
		if(next.start == i.start + i.count) {
			freeIntervals.erase(next);
			freeIntervals.erase(i);
			i.count += next.count;
			freeIntervals.insert(i);
			merged = true;
		}
	}
	//else, push it standalone
	if(!merged) freeIntervals.insert(i);
}

MeshBatched::Buffer::Interval MeshBatched::Buffer::allocateInterval(unsigned int vCount) {
	Interval ret(0, vCount);
	Interval toReplace(0,0);
	bool spaceAvailable = false;
	for(const Interval& i : freeIntervals) {
		if(i.count >= vCount) {
			toReplace = i;
			spaceAvailable = true;
			break;
		}
	}
	if(spaceAvailable) {
		ret.start = toReplace.start;
		freeIntervals.erase(toReplace);
		if(toReplace.count > vCount)
			freeIntervals.insert(Interval(toReplace.start + vCount, toReplace.count - vCount));
	}
	else {
		//buffer must be resized
		ret.start = totalBufferSize;
		int resizePower;
		for(resizePower = 1; vCount > (pow(2, resizePower)-1)*totalBufferSize; ++resizePower);
		resizeBuffer(pow(2,resizePower)*totalBufferSize);
		ret = allocateInterval(vCount); //...meh
	}
	return ret;
}

void MeshBatched::Buffer::resizeBuffer(unsigned int newSize) {
	VBE_ASSERT(newSize > totalBufferSize, "Cannot resize to a smaller size");
	//copy contents into new buffer
	GLuint newVBO = 0;
	GL_ASSERT(glGenBuffers(1, &newVBO));
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, newVBO));
	GL_ASSERT(glBufferData(GL_ARRAY_BUFFER, newSize*bufferFormat.vertexSize(), 0, MeshBase::STREAM));
	GL_ASSERT(glBindBuffer(GL_COPY_READ_BUFFER, vertexBuffer));
	GL_ASSERT(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_ARRAY_BUFFER, 0, 0, bufferFormat.vertexSize()*totalBufferSize));
	GL_ASSERT(glInvalidateBufferData(vertexBuffer));
	GL_ASSERT(glDeleteBuffers(1, &vertexBuffer));
	for(std::pair<const GLuint, const ShaderBinding*> bind : bindings) delete bind.second;
	bindings.clear();
	vertexBuffer = newVBO;
	unsigned int oldSize = totalBufferSize;
	totalBufferSize = newSize;
	//Mark the new memory as free
	freeInterval(Interval(oldSize, totalBufferSize-oldSize));
}
