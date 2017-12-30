#include "GLEWWrapper.hpp"

namespace nu
{

const char* glErrorString(GLenum gl_err)
{
	switch (gl_err)
	{
		case GL_NO_ERROR: return "GL_NO_ERROR"; break;
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION"; break;
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE"; break;
	}
	return "";
}

namespace GLEWWrapper
{

namespace priv
{

bool initialized = false;

} // namespace priv

bool isInitialized()
{
	return priv::initialized;
}

bool init()
{
	if (!priv::initialized)
	{
		glewExperimental = true; // Needed in core profile
		if (glewInit() != GLEW_OK)
		{
			LogError(nu::LogChannel::Application, 10, "Failed to initialize GLEW");
			priv::initialized = false;
		}
		else
		{
			priv::initialized = true;
		}
	}
	return priv::initialized;
}

} // namespace GLEWWrapper

} // namespace nu