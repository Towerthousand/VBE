#ifndef RENDERTARGETBASE_HPP
#define RENDERTARGETBASE_HPP

#include <set>
#include <map>
#include <vector>

#include <VBE/config.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/Texture2D.hpp>
#include <VBE/graphics/Texture2DArray.hpp>
#include <VBE/graphics/RenderBuffer.hpp>
#include <VBE/math.hpp>
#include <VBE/utils/NonCopyable.hpp>

class RenderTargetBase : public NonCopyable {
    public:
        enum Attachment {
            DEPTH = GL_DEPTH_ATTACHMENT,
            STENCIL = GL_STENCIL_ATTACHMENT,
            COLOR0 = GL_COLOR_ATTACHMENT0,
#ifndef VBE_GLES2
            DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT,
            COLOR1 = GL_COLOR_ATTACHMENT1,
            COLOR2 = GL_COLOR_ATTACHMENT2,
            COLOR3 = GL_COLOR_ATTACHMENT3,
            COLOR4 = GL_COLOR_ATTACHMENT4,
            COLOR5 = GL_COLOR_ATTACHMENT5,
            COLOR6 = GL_COLOR_ATTACHMENT6,
            COLOR7 = GL_COLOR_ATTACHMENT7,
            COLOR8 = GL_COLOR_ATTACHMENT8,
            COLOR9 = GL_COLOR_ATTACHMENT9,
            COLOR10 = GL_COLOR_ATTACHMENT10,
            COLOR11 = GL_COLOR_ATTACHMENT11,
            COLOR12 = GL_COLOR_ATTACHMENT12,
            COLOR13 = GL_COLOR_ATTACHMENT13,
            COLOR14 = GL_COLOR_ATTACHMENT14,
            COLOR15 = GL_COLOR_ATTACHMENT15
#endif
        };

        inline bool isColorAttachment(Attachment a) {
#ifdef VBE_GLES2
            return a == COLOR0;
#else
            return a >= COLOR0 && a <= COLOR15;
#endif
        }

        static void bind(const RenderTargetBase& renderTarget) {
            bind(&renderTarget);
        }

        static void bind(const RenderTargetBase* renderTarget);
        static const RenderTargetBase* getCurrent();

        vec2ui getSize() const;
        unsigned int getNumLayers() const;

        friend void swap(RenderTargetBase& a, RenderTargetBase& b);
    protected:
        RenderTargetBase(unsigned int width, unsigned int height, unsigned int numLayers);
        virtual ~RenderTargetBase();

        void ensureValid() const;
        void valid() const; //validate this framebuffer pls
        void enableAttachment(RenderTargetBase::Attachment a);
        void disableAttachment(RenderTargetBase::Attachment a);

        struct RenderTargetEntry {
                enum Type {
                    RenderBufferEntry = 0,
#ifndef VBE_GLES2
                    Texture2DArrayEntry,
#endif
                    Texture2DEntry
                };

                RenderTargetEntry(RenderBuffer* renderBuffer) :
                    type(RenderBufferEntry), renderBuffer(renderBuffer) {}
                RenderTargetEntry(Texture2D* texture) :
                    type(Texture2DEntry), texture2D(texture) {}
#ifndef VBE_GLES2
                RenderTargetEntry(Texture2DArray* texture) :
                    type(Texture2DArrayEntry), texture2DArray(texture) {}
#endif
                ~RenderTargetEntry() {}

                Type type;
                //TODO: Fix this with handles!
                //Having pointers will wreck everything if the user moves the
                //resource after assigning it. For safety, handles should be
                //applied.
                RenderBuffer* renderBuffer;
                Texture2D* texture2D;
#ifndef VBE_GLES2
                Texture2DArray* texture2DArray;
#endif
        };

        static const RenderTargetBase* current;

        GLuint handle = 0;
        /*const*/ vec2ui size = vec2ui(0); //metaphorical const ftw
        mutable bool dirty = false;
        unsigned int numLayers = 0;
        std::vector<Attachment> drawAttachments;
        std::set<Attachment> allAttachments;
        mutable std::map<Attachment, RenderTargetEntry> entries;
};


#endif // RENDERTARGETBASE_HPP
