#ifndef NU_WINDOW_HPP
#define NU_WINDOW_HPP

#include "../System/MovablePtr.hpp"

#include "Event.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "VideoMode.hpp"
#include "WindowHandle.hpp"

namespace nu
{

class WindowImpl;

class Window
{
	public:
		Window();
		Window(WindowHandle handle);
		Window(VideoMode mode, const std::string& title);
		virtual ~Window();

		bool create(WindowHandle handle);
		bool create(VideoMode mode, const std::string& title);
		void close();
		bool isOpen() const;

		bool pollEvent(Event& event);
		bool waitEvent(Event& event);

		void setPosition(I32 x, I32 y);
		void setPosition(const Vector2i& position);
		Vector2i getPosition() const;

		void setSize(U32 width, U32 height);
		void setSize(const Vector2u& size);
		Vector2u getSize() const;

		void requestFocus();
		bool hasFocus() const;

		WindowHandle getSystemHandle();

	protected:
		virtual void onCreate();
		virtual void onResize();

	private:
		bool filterEvent(const Event& event);
		
		bool initialize();

	private:
		WindowImpl* mImpl;

		Vector2u mSize;
};

} // namespace nu

#endif // NU_WINDOW_HPP
