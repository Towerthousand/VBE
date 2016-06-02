#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture.hpp>
#include <VBE/system/Log.hpp>

// static
int Texture::maxSlots = -1;
std::vector<std::vector<GLuint>> Texture::current;
unsigned int Texture::currentUnit = 0;

//static
unsigned int Texture::getMaxSlots() {
    if(maxSlots == -1) {
        GL_ASSERT(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxSlots));
        VBE_DLOG("* Platform info: Max concurrent texture images: " << maxSlots);
        current = std::vector<std::vector<GLuint>>(TypeCount, std::vector<GLuint>(maxSlots, 0));
        GL_ASSERT(glActiveTexture(GL_TEXTURE0));
    }
    return maxSlots;
}

void swap(Texture& a, Texture& b) {
    using std::swap;

    swap(a.handle, b.handle);
    swap(a.format, b.format);
    swap(a.type, b.type);
}

// static
void Texture::bind(Texture::Type type, const Texture* tex, unsigned int slot) {
    VBE_ASSERT(slot < getMaxSlots(), "Invalid texture slot on Texture::bind");

    if(currentUnit != slot) {
        GL_ASSERT(glActiveTexture(GL_TEXTURE0 + slot));
        currentUnit = slot;
    }

    if(tex != nullptr) {
        VBE_ASSERT(type == tex->type, "Invalid tex, type on Texture::bind");
        if(current[type][slot] == tex->handle) return;
        current[type][slot] = tex->handle;
    }

    if(tex != nullptr)
        GL_ASSERT(glBindTexture(typeToGL(type), tex->handle));
    else
        GL_ASSERT(glBindTexture(typeToGL(type), 0));
}

// static
GLenum Texture::typeToGL(Texture::Type t) {
    switch(t) {
        case Type2D: return GL_TEXTURE_2D;
#ifndef VBE_GLES2
        case Type2DArray: return GL_TEXTURE_2D_ARRAY;
        case Type3D: return GL_TEXTURE_3D;
#endif
        case TypeCubemap: return GL_TEXTURE_CUBE_MAP;
        case TypeCubemapArray: return GL_TEXTURE_CUBE_MAP_ARRAY;
        default: break;
    }
    VBE_ASSERT(false, "Unknown type when trying to convert from Texture::Type to GL enum");
    return 0;
}

Texture::Texture(Type type, TextureFormat::Format format): format(format), type(type) {
    getMaxSlots();
    GL_ASSERT(glGenTextures(1, &handle));
    VBE_ASSERT(handle != 0, "Failed to create texture");

    // Default filtering in OpenGL uses mipmaps, which will show black in most cases
    // where mipmaps are not generated. Change it to a saner default here.
    setFilter(GL_LINEAR, GL_LINEAR);

    // Set clamp by default too, just in case.
    setWrap(GL_CLAMP_TO_EDGE);
}

Texture::~Texture(){
    GL_ASSERT(glDeleteTextures(1, (GLuint*) &handle));
}

GLuint Texture::getHandle() const {
    return handle;
}

TextureFormat::Format Texture::getFormat() const {
    return format;
}

Texture::Type Texture::getType() const {
    return type;
}

#ifndef VBE_GLES2
void Texture::setComparison(GLenum func, GLenum mode) {
    VBE_ASSERT(TextureFormat::isDepth(format), "Can't set comparison for a non-depth, non_stencil texture");
    Texture::bind(type, this, 0);
    GL_ASSERT(glTexParameteri(typeToGL(type), GL_TEXTURE_COMPARE_FUNC, func));
    GL_ASSERT(glTexParameteri(typeToGL(type), GL_TEXTURE_COMPARE_MODE, mode));
}
#endif

void Texture::setFilter(GLenum min, GLenum mag) {
    Texture::bind(type, this, 0);
    GL_ASSERT(glTexParameteri(typeToGL(type), GL_TEXTURE_MIN_FILTER, min));
    GL_ASSERT(glTexParameteri(typeToGL(type), GL_TEXTURE_MAG_FILTER, mag));
}

void Texture::setWrap(GLenum wrap) {
    Texture::bind(type, this, 0);
    GL_ASSERT(glTexParameteri(typeToGL(type), GL_TEXTURE_WRAP_S, wrap));
    GL_ASSERT(glTexParameteri(typeToGL(type), GL_TEXTURE_WRAP_T, wrap));
}

void Texture::generateMipmap() {
    Texture::bind(type, this, 0);
    GL_ASSERT(glGenerateMipmap(typeToGL(type)));
    setFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
}
