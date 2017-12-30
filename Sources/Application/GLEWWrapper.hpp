#ifndef NU_GLEWWRAPPER_HPP
#define NU_GLEWWRAPPER_HPP

#include "../System/Prerequisites.hpp"

#include <GL/glew.h>

namespace nu
{

#if !defined(NU_ENABLE_GRAPHICS_API_DEBUG)
	#if (defined(NU_BUILD_DEBUG) || defined(NU_BUILD_RELEASE))
		#define NU_ENABLE_GRAPHICS_API_DEBUG 1
	#else
		#define NU_ENABLE_GRAPHICS_API_DEBUG 0
	#endif
#endif

const char* glErrorString(GLenum gl_err);

#if NU_ENABLE_GRAPHICS_API_DEBUG
	#define glCheck(expr) expr; { GLenum gl_err = glGetError(); if (gl_err == GL_NO_ERROR) { } else { nu::LogManager::error("(%s) " #expr "\n", nu::glErrorString(gl_err)); } }
#else
	#define glCheck(expr) expr;
#endif

namespace GLEWWrapper
{

bool isInitialized();
bool init();

} // namespace GLEWWrapper

} // namespace nu

#endif // NU_GLEWWRAPPER_HPP