#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>

namespace Vertex {

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
				Fixed         = GL_FIXED,
#ifndef VBE_GLES2
                Double        = GL_DOUBLE
#endif
			};
			inline bool isIntegerType(Type t) {
				switch(t) {
					case GL_FLOAT:
					case GL_FIXED:
#ifndef VBE_GLES2
					case GL_DOUBLE:
#endif
                        return false;
					default:
                        return true;
				}
			}
			enum Conversion {
				ConvertDefault,
				ConvertToFloat,
				ConvertToFloatNormalized,
				ConvertToInt
			};

			Element(const std::string& name, Type type, unsigned int size, Conversion conv = ConvertDefault);
			Element(const Element& element);

			bool hasName(const std::string& name) const;

			Element& operator=(const Element& e);
			bool operator == (const Element& e) const;
			bool operator != (const Element& e) const;

			std::string name;
			Type type;
			unsigned int size;
			Conversion conv;

		private:
			void calcDefaultConversion();
	};

	class Format {
		public:
			Format();
			explicit Format(const std::vector<Element> &elements);
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
