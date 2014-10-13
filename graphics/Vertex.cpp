#include "Vertex.hpp"

namespace Vertex {

	bool Attribute::isAttrsInit = false;
	std::map<std::string, Attribute*> Attribute::names;
	std::vector<Attribute*> Attribute::attributes;

	void Attribute::init() {
		//Default names for default elements
		attributes.resize(4);
		attributes[Attribute::Position] = new Attribute(Attribute::Position);
		attributes[Attribute::Position]->addName("a_position");

		attributes[Attribute::Color] = new Attribute(Attribute::Color);
		attributes[Attribute::Color]->addName("a_color");

		attributes[Attribute::Normal] = new Attribute(Attribute::Normal);
		attributes[Attribute::Normal]->addName("a_normal");

		attributes[Attribute::TexCoord] = new Attribute(Attribute::TexCoord);
		attributes[Attribute::TexCoord]->addName("a_texCoord");
		isAttrsInit = true;
	}

	Attribute::Attribute(int id) : id(id) {

	}

	Attribute& Attribute::get(int id) {
		if (!isAttrsInit) init();
		VBE_ASSERT(id >= 0 && id < int(attributes.size()), "Bad attrib id: " << id);
		return *attributes.at(id);
	}

	Attribute& Attribute::get(const std::string &name) {
		if (!isAttrsInit) init();
		std::map<std::string, Attribute*>::iterator it = names.find(name);
		if (it == names.end()) {
			attributes.push_back(new Attribute(attributes.size()));
			it = names.insert(std::pair<std::string, Attribute*>(name, attributes.back())).first;
		}

		return *(it->second);
	}

	int Attribute::ID() {
		return id;
	}

	bool Attribute::hasName(const std::string &name) const {
		std::map<std::string, Attribute*>::const_iterator it = names.find(name);
		if(it != names.end() && it->second->ID() == id)
			return true;
		return false;
	}

	bool Attribute::operator == (const Attribute& a) const {
		return id == a.id;
	}

	bool Attribute::operator != (const Attribute& a) const {
		return id != a.id;
	}

	Attribute& Attribute::addName(const std::string &name) {
		std::pair<std::map<std::string, Attribute*>::iterator, bool>
				result = names.insert(std::pair<std::string, Attribute*>(name, this));
		if (result.second) attrNames.insert(name);

		return *this;
	}

	Element::Element(Attribute &attr, Type type, unsigned int size, Conversion conv)
		: attr(attr), type(type), size(size), conv(conv) {
		calcDefaultConversion();
	}

	Element::Element(int attrID, Type type, unsigned int size, Conversion conv)
		: attr(Attribute::get(attrID)), type(type), size(size), conv(conv) {
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

	Element::Element(const Element &element) : attr(element.attr), type(element.type), size(element.size), conv(element.conv) {
	}

	Element& Element::operator=(const Element& e) {
		return *(new (this) Element(e));
	}

	bool Element::operator == (const Element& e) const {
		return attr == e.attr && size == e.size;
	}

	bool Element::operator != (const Element& e) const {
		return attr != e.attr && size != e.size;
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
