#ifndef NU_GLFWWRAPPER_HPP
#define NU_GLFWWRAPPER_HPP

#include "../System/Prerequisites.hpp"

#include <GLFW/glfw3.h>

#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

namespace nu
{

namespace GLFWWrapper
{

bool isInitialized();
bool init();
void terminate();

} // namespace GLFWWrapper

} // namespace nu

#endif // NU_GLFWWRAPPER_HPP