#include "GLFWWrapper.hpp"

namespace nu
{

namespace GLFWWrapper
{

namespace priv
{

bool initialized = false;
int windows = 0;

void error(int error, const char* description)
{
	LogError(nu::LogChannel::Application, 10, "Failed to initialize GLFW : %s", description);
}

} // namespace priv

bool isInitialized()
{
	return priv::initialized;
}

bool init()
{
	if (!priv::initialized)
	{
		glfwSetErrorCallback(priv::error);

		if (glfwInit() != GLFW_TRUE)
		{
			priv::initialized = false;
		}
		else
		{
			priv::initialized = true;
			priv::windows++;

			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
	}
	return priv::initialized;
}

void terminate()
{
	priv::windows--;
	if (priv::initialized && priv::windows == 0)
	{
		priv::initialized = false;
		glfwTerminate();
	}
}

} // namespace GLFWWrapper

} // namespace nu