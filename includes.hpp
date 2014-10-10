#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include "tools.hpp"
///	@defgroup Scene Scene Graph
///
/// Scene graph nodes and Game root node
///
#include "scene/Game.hpp"
#include "scene/GameObject.hpp"
#include "scene/Camera.hpp"
///	@defgroup Geometry Geometry
///
/// Geometry objects and collision tests
///
#include "geometry/Collision.hpp"
///	@defgroup Utils Utilities
///
///	Logging system and generic interfaces
///
#include "utils/Manager.hpp"
///	@defgroup Graphics Graphics
///
/// OpenGL objects and 3D graphics utilities
///
#include "graphics/Model.hpp"
#include "graphics/Shader.hpp"
#include "graphics/ShaderBinding.hpp"
#include "graphics/Uniform.hpp"
///	@defgroup System System
///
/// System and I/O device classes
///
#include "environment/Environment.hpp"
#include "environment/Screen.hpp"

#endif // INCLUDES_HPP
