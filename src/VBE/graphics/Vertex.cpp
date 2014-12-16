#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Vertex.hpp>
#include <VBE/system/Log.hpp>

namespace Vertex {
	Element::Element(const std::string& name, Type type, unsigned int size, Conversion conv)
		: name(name), type(type), size(size), conv(conv) {
		calcDefaultConversion();
	}

	void Element::calcDefaultConversion()
	{
		if(conv == ConvertDefault)
		{
			if(Vertex::Element::isIntegerType(type))
				conv = ConvertToInt;
			else
				conv = ConvertToFloat;
		}
	}

	Element::Element(const Element &element) : name(element.name), type(element.type), size(element.size), conv(element.conv) {
	}

	bool Element::hasName(const std::string& name) const {
		return name == this->name;
	}

	Element& Element::operator=(const Element& e) {
		return *(new (this) Element(e));
	}

	bool Element::operator == (const Element& e) const {
		return name == e.name && type == e.type && size == e.size && conv == e.conv;
	}

	bool Element::operator != (const Element& e) const {
		return !(*this == e);
	}

	Format::Format() : Format(std::vector<Element>()) {

	}

	Format::Format(const std::vector<Element> &elements)
		: elements(elements), offsets(elements.size(), 0), vertSize(0) {
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); ++i) {
			offsets[i] = offset;
			unsigned int size = 4;
			switch(elements[i].type) {
				case Element::Byte:          size = sizeof(GLbyte); break;
				case Element::UnsignedByte:  size = sizeof(GLchar); break;
				case Element::Short:         size = sizeof(GLshort); break;
				case Element::UnsignedShort: size = sizeof(GLushort); break;
				case Element::Int:           size = sizeof(GLint); break;
				case Element::UnsignedInt:   size = sizeof(GLuint); break;
				case Element::Float:         size = sizeof(GLfloat); break;
				case Element::Fixed:         size = sizeof(GLint); break; //FIXME: GLFixed no existe para mi (?)
				default: VBE_ASSERT(0, "Not a knownt element type " << elements[i].type); break;
			}
			offset += elements[i].size * size;
		}
		vertSize = offset;
	}

	Format::~Format() {
	}

	const Element& Format::element(unsigned int index) const {
		return elements[index];
	}

	unsigned int Format::offset(unsigned int index) const {
		return offsets[index];
	}

	unsigned int Format::elementCount() const {
		return elements.size();
	}

	unsigned int Format::vertexSize() const {
		return vertSize;
	}

	bool Format::operator == (const Format& f) const {
		if (elements.size() != f.elements.size())
			return false;

		for (unsigned int i = 0, count = elements.size(); i < count; ++i) {
			if (elements[i] != f.elements[i])
				return false;
		}

		return true;
	}

	bool Format::operator != (const Format& f) const {
		return !(this->operator == (f));
	}

} // namespace Vertex
