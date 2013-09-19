#include "Vertex.hpp"

namespace Vertex {

	bool Attribute::s_isAttrsInit = false;
	std::map<std::string, Attribute*> Attribute::s_names;
	std::vector<Attribute*> Attribute::s_attributes;

	void Attribute::init() {
		//Default names for default elements
		s_attributes.resize(4);
		s_attributes[Attribute::Position] = new Attribute(Attribute::Position);
		s_attributes[Attribute::Position]->addName("a_position");

		s_attributes[Attribute::Color] = new Attribute(Attribute::Color);
		s_attributes[Attribute::Color]->addName("a_color");

		s_attributes[Attribute::Normal] = new Attribute(Attribute::Normal);
		s_attributes[Attribute::Normal]->addName("a_normal");

		s_attributes[Attribute::TexCoord] = new Attribute(Attribute::TexCoord);
		s_attributes[Attribute::TexCoord]->addName("a_texCoord");
		s_isAttrsInit = true;
	}

	Attribute::Attribute(int id) : m_id(id) {

	}

	Attribute& Attribute::get(int id) {
		if (!s_isAttrsInit) init();
		VBE_ASSERT(id >= 0 && id < int(s_attributes.size()), "Bad attrib id: " << id)
		return *s_attributes.at(id);
	}

	Attribute& Attribute::get(const std::string &name) {
		if (!s_isAttrsInit) init();
		std::map<std::string, Attribute*>::iterator it = s_names.find(name);
		if (it == s_names.end()) {
			s_attributes.push_back(new Attribute(s_attributes.size()));
			it = s_names.insert(std::pair<std::string, Attribute*>(name,s_attributes.back())).first;
		}

		return *(it->second);
	}

	int Attribute::ID() {
		return m_id;
	}

	bool Attribute::hasName(const std::string &name) const {
		std::map<std::string,Attribute*>::const_iterator it = s_names.find(name);
		if(it != s_names.end() && it->second->ID() == m_id)
			return true;
		return false;
	}

	bool Attribute::operator == (const Attribute& a) const {
		return m_id == a.m_id;
	}

	bool Attribute::operator != (const Attribute& a) const {
		return m_id != a.m_id;
	}

	Attribute& Attribute::addName(const std::string &name) {
		std::pair<std::map<std::string, Attribute*>::iterator, bool>
				result = s_names.insert(std::pair<std::string, Attribute*>(name, this));
		if (result.second) m_attrNames.insert(name);

		return *this;
	}

	Element::Element(Attribute &attr, unsigned int type, unsigned int size)
		: m_attr(attr), m_type(type), m_size(size) {

	}

	Element::Element(int attrID, unsigned int type, unsigned int size)
		: m_attr(Attribute::get(attrID)), m_type(type), m_size(size) {

	}

	Element::Element(const Element &element) : m_attr(element.m_attr), m_type(element.m_type), m_size(element.m_size) {
	}

	Element& Element::operator=(const Element& e) {
		return *(new (this) Element(e));
	}

	bool Element::operator == (const Element& e) const {
		return m_attr == e.m_attr && m_size == e.m_size;
	}

	bool Element::operator != (const Element& e) const {
		return m_attr != e.m_attr && m_size != e.m_size;
	}

	Format::Format(const std::vector<Element> &elements)
		: m_elements(elements), m_offsets(elements.size(),0), m_vertexSize(0) {
		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_elements.size(); ++i) {
			m_offsets[i] = offset;
			unsigned int size = 4;
			switch(m_elements[i].m_type) {
				case Element::Byte:          size = sizeof(char); break;
				case Element::UnsignedByte:  size = sizeof(unsigned char); break;
				case Element::Short:         size = sizeof(short); break;
				case Element::UnsignedShort: size = sizeof(unsigned short); break;
				case Element::Int:           size = sizeof(int); break;
				case Element::UnsignedInt:   size = sizeof(unsigned int); break;
				case Element::Float:         size = sizeof(float); break;
				case Element::Fixed:         size = sizeof(int); break;
				default: VBE_ASSERT(0, "Not a knownt element type " << m_elements[i].m_type) break;
			}
			offset += m_elements[i].m_size * size;
		}
		m_vertexSize = offset;
	}

	Format::~Format() {
	}

	const Element& Format::element(unsigned int index) const {
		return m_elements[index];
	}

	unsigned int Format::offset(unsigned int index) const {
		return m_offsets[index];
	}

	unsigned int Format::elementCount() const {
		return m_elements.size();
	}

	unsigned int Format::vertexSize() const {
		return m_vertexSize;
	}

	bool Format::operator == (const Format& f) const {
		if (m_elements.size() != f.m_elements.size())
			return false;

		for (unsigned int i = 0, count = m_elements.size(); i < count; ++i) {
			if (m_elements[i] != f.m_elements[i])
				return false;
		}

		return true;
	}

	bool Format::operator != (const Format& f) const {
		return !(this->operator == (f));
	}

} // namespace Vertex
