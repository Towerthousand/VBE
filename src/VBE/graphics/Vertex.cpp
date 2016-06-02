#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Vertex.hpp>
#include <VBE/system/Log.hpp>

namespace Vertex {
    Attribute::Attribute(const std::string& name, Type type, unsigned int size, Conversion conv, unsigned int divisor)
        : name(name), type(type), size(size), conv(conv), divisor(divisor) {
        calcDefaultConversion();
    }

    void Attribute::calcDefaultConversion()
    {
        if(conv == ConvertDefault)
        {
            if(Vertex::Attribute::isIntegerType(type))
                conv = ConvertToInt;
            else
                conv = ConvertToFloat;
        }
    }

    Attribute::Attribute(const Attribute &element) : name(element.name), type(element.type), size(element.size), conv(element.conv), divisor(element.divisor) {
    }

    bool Attribute::hasName(const std::string& name) const {
        return name == this->name;
    }

    Attribute& Attribute::operator=(const Attribute& e) {
        return *(new (this) Attribute(e));
    }

    bool Attribute::operator == (const Attribute& e) const {
        return name == e.name && type == e.type && size == e.size && conv == e.conv && divisor == e.divisor;
    }

    bool Attribute::operator != (const Attribute& e) const {
        return !(*this == e);
    }

    Format::Format() : Format(std::vector<Attribute>()) {

    }

    Format::Format(const std::vector<Attribute> &elements)
        : elements(elements), offsets(elements.size(), 0) {
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); ++i) {
            offsets[i] = offset;
            unsigned int size = 4;
            switch(elements[i].type) {
                case Attribute::Byte:          size = sizeof(GLbyte); break;
                case Attribute::UnsignedByte:  size = sizeof(GLchar); break;
                case Attribute::Short:         size = sizeof(GLshort); break;
                case Attribute::UnsignedShort: size = sizeof(GLushort); break;
                case Attribute::Int:           size = sizeof(GLint); break;
                case Attribute::UnsignedInt:   size = sizeof(GLuint); break;
                case Attribute::Float:         size = sizeof(GLfloat); break;
                case Attribute::Fixed:         size = sizeof(GLint); break; //FIXME: GLFixed no existe para mi (?)
                default: VBE_ASSERT(0, "Not a knownt element type " << elements[i].type); break;
            }
            offset += elements[i].size * size;
        }
        vertSize = offset;
    }

    Format::~Format() {
    }

    const Attribute& Format::element(unsigned int index) const {
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
