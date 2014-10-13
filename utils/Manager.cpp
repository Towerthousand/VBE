#include "Manager.hpp"

Manager<RenderTarget> FrameBuffers = Manager<RenderTarget>();
Manager<Texture2D> Textures2D = Manager<Texture2D>();
Manager<Mesh> Meshes = Manager<Mesh>();
Manager<ShaderProgram> Programs = Manager<ShaderProgram>();

#ifndef VBE_GLES2
Manager<Texture3D> Textures3D = Manager<Texture3D>();
Manager<Texture2DArray> Textures2DArrays = Manager<Texture2DArray>();
#endif
