#include "Window.hpp"

namespace nu
{

Window::Window()
	: mWindow(nullptr)
{
	GLFWWrapper::init();
}

Window::Window(unsigned int width, unsigned int height, const std::string& title)
	: mWindow(nullptr)
{
	GLFWWrapper::init();
	create(width, height, title);
}

Window::~Window()
{
	if (mWindow != nullptr)
	{
		glfwDestroyWindow(mWindow);
	}
	GLFWWrapper::terminate();
}

void Window::makeContextCurrent()
{
	glfwMakeContextCurrent(mWindow);
	GLEWWrapper::init();
}

bool Window::isContextCurrent() const
{
	return mWindow == glfwGetCurrentContext();
}

bool Window::create(unsigned int width, unsigned int height, const std::string& title)
{
	if (mWindow != nullptr)
	{
		glfwDestroyWindow(mWindow);
	}
	mWindow = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);
	if (mWindow == nullptr)
	{
		return false;
	}
	else
	{
		glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE);
		glfwSetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
		makeContextCurrent();
		glCheck(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		return true;
	}
}

void Window::close()
{
	glfwSetWindowShouldClose(mWindow, GL_TRUE);
}

bool Window::isOpen() const
{
	return mWindow != nullptr && glfwWindowShouldClose(mWindow) == GL_FALSE;
}

Vector2u Window::getSize() const
{
	I32 w, h;
	glfwGetWindowSize(mWindow, &w, &h);
	return Vector2u((U32)w, (U32)h);
}

Vector2u Window::getFramebufferSize() const
{
	I32 w, h;
	glfwGetFramebufferSize(mWindow, &w, &h);
	return Vector2u((U32)w, (U32)h);
}

F32 Window::getSizeRatio() const
{
	Vector2u size = getSize();
	return (F32(size.x) / F32(size.y));
}

F32 Window::getFramebufferSizeRatio() const
{
	Vector2u size = getFramebufferSize();
	return (F32(size.x) / F32(size.y));
}

void Window::clear()
{
	glCheck(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::display()
{
	glfwSwapBuffers(mWindow);
}

bool Window::hasFocus() const
{
	return glfwGetWindowAttrib(mWindow, GLFW_FOCUSED) == GLFW_TRUE;
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::waitEvents()
{
	glfwWaitEvents();
}

bool Window::isKeyPressed(int key) const
{
	return glfwGetKey(mWindow, key) == GLFW_PRESS;
}

bool Window::isMouseButtonPressed(int button) const
{
	return glfwGetMouseButton(mWindow, button) == GLFW_PRESS;
}

Vector2f Window::getCursorPos() const
{
	double x, y;
	glfwGetCursorPos(mWindow, &x, &y);
	return Vector2f((float)x, (float)y);
}

void Window::setCursorPos(const Vector2f& cursorPosition)
{
	glfwSetCursorPos(mWindow, (double)cursorPosition.x, (double)cursorPosition.y);
}

void Window::setCursorPos(float x, float y)
{
	glfwSetCursorPos(mWindow, (double)x, (double)y);
}

void Window::setCursorMode(int mode)
{
	glfwSetInputMode(mWindow, GLFW_CURSOR, mode);
}

void Window::setClipboardText(const std::string& text)
{
	glfwSetClipboardString(mWindow, text.c_str());
}

std::string Window::getClipboardText() const
{
	return std::string(glfwGetClipboardString(mWindow));
}

#ifdef _WIN32
HWND Window::getWindowHandle()
{
	return glfwGetWin32Window(mWindow);
}
#endif

} // namespace nu