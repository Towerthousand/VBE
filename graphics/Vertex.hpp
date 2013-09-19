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
			iterator begin() { return attrNames.begin();}
			iterator end()   { return attrNames.end();  }

			Attribute& addName(const std::string &name);

			enum DefaultId { //Build-in default attributes
				Position = 0,
				Color,
				Normal,
				TexCoord
			};

		private:
			Attribute(int ID);
			int id;

			static void init(); //add default attributes
			static bool isAttrsInit; //added default attributes?
			static std::map<std::string, Attribute*> names; //the names of each attribute and the attribute it points to
			static std::vector<Attribute*> attributes; //all the attributes
			std::set<std::string> attrNames; //al the names this attribute can have
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

			Attribute &attr;
			unsigned int type;
			unsigned int size;
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
			std::vector<Element> elements;
			std::vector<unsigned int> offsets;
			unsigned int vertSize;
	};

} // namespace Vertex

#endif // VERTEX_HPP
