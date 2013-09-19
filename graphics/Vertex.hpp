#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "../tools.hpp"

namespace Vertex {

	class Attribute {
		public:
			static Attribute& get(int ID);
			static Attribute& get(const std::string &name);

			int ID();
			bool hasName(const std::string &name) const;

			bool operator == (const Attribute& a) const;
			bool operator != (const Attribute& a) const;

			typedef std::set<std::string>::const_iterator iterator;
			iterator begin() { return m_attrNames.begin();}
			iterator end()   { return m_attrNames.end();  }

			Attribute& addName(const std::string &name);

			enum DefaultId { //Build-in default attributes
				Position = 0,
				Color,
				Normal,
				TexCoord
			};

		private:
			Attribute(int ID);
			int m_id;

			static void init(); //add default attributes
			static bool s_isAttrsInit; //added default attributes?
			static std::map<std::string, Attribute*> s_names; //the names of each attribute and the attribute it points to
			static std::vector<Attribute*> s_attributes; //all the attributes
			std::set<std::string> m_attrNames; //all the names this attribute can have
	};

	class Element {
		public:
			enum Type {
				Byte          = GL_BYTE,
				UnsignedByte  = GL_UNSIGNED_BYTE,
				Short         = GL_SHORT,
				UnsignedShort = GL_UNSIGNED_SHORT,
				Int           = GL_INT,
				UnsignedInt   = GL_UNSIGNED_INT,
				Float         = GL_FLOAT,
				Fixed         = GL_FIXED
			};
			Element(Attribute &attr, unsigned int type, unsigned int size);
			Element(     int attrID, unsigned int type, unsigned int size);
			Element(const Element& element);

			Element& operator=(const Element& e);
			bool operator == (const Element& e) const;
			bool operator != (const Element& e) const;

			Attribute &m_attr;
			unsigned int m_type;
			unsigned int m_size;
	};

	class Format {
		public:
			Format(const std::vector<Element> &elements);
			~Format();

			const Element& element(unsigned int index) const;
			unsigned int offset(unsigned int index) const;
			unsigned int elementCount() const;
			unsigned int vertexSize() const;
			bool operator == (const Format& f) const;
			bool operator != (const Format& f) const;

		private:
			std::vector<Element> m_elements;
			std::vector<unsigned int> m_offsets;
			unsigned int m_vertexSize;
	};

} // namespace Vertex

#endif // VERTEX_HPP
