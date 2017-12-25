#ifndef NU_WINDOW_HPP
#define NU_WINDOW_HPP

#include "GLEWWrapper.hpp"
#include "GLFWWrapper.hpp"

#include "../Math/Vector2.hpp"

namespace nu
{

class Window
{
	public:
		Window();
		Window(unsigned int width, unsigned int height, const std::string& title);
		~Window();

		void makeContextCurrent();
		bool isContextCurrent() const;

		bool create(unsigned int width, unsigned int height, const std::string& title);
		void close();
		bool isOpen() const;

		Vector2u getSize() const;
		Vector2u getFramebufferSize() const;

		void clear();
		void display();

		bool hasFocus() const;

		void pollEvents();
		void waitEvents();

		bool isKeyPressed(int key) const;
		bool isMouseButtonPressed(int button) const;

		Vector2f getCursorPos() const;
		void setCursorPos(const Vector2f& cursorPosition);
		void setCursorPos(float x, float y);
		void setCursorMode(int mode); // GLFW_NORMAL, GLFW_HIDDEN, GLFW_DISABLED

		void setClipboardText(const std::string& text);
		std::string getClipboardText() const;

		#ifdef _WIN32
		HWND getWindowHandle();
		#endif

	private:
		GLFWwindow* mWindow;

};

} // namespace nu

#endif // NU_WINDOW_HPP