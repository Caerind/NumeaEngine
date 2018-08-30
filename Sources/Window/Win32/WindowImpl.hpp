#ifndef NU_WINDOWIMPL_HPP
#define NU_WINDOWIMPL_HP

#include <queue>

#include <windows.h>

#include "../Window.hpp"

namespace nu
{

class WindowImpl
{
	public:
		WindowImpl(WindowHandle handle);
		WindowImpl(const VideoMode& mode, const std::string& title);
		~WindowImpl();

		bool popEvent(Event& event, bool block);
		void pushEvent(const Event& event);

		void setPosition(I32 x, I32 y);
		void setPosition(const Vector2i& position);
		Vector2i getPosition() const;

		void setSize(U32 width, U32 height);
		void setSize(const Vector2u& size);
		Vector2u getSize() const;

		void requestFocus();
		bool hasFocus() const;

		WindowHandle getSystemHandle() const;

	protected:
		void processEvents();

	private:
		void registerWindowClass();

		void setTracking(bool track);

		void cleanup();

		Keyboard::Key translateVirtualKeyCode(WPARAM key, LPARAM flags);

		void processEvent(UINT message, WPARAM wParam, LPARAM lParam);

		static LRESULT CALLBACK globalOnEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND mHandle;
		LONG_PTR mCallback;
		HCURSOR mLastCursor;

		bool mResizing;
		Vector2u mLastSize;
		bool mKeyRepeatEnabled;
		U16 mSurrogate;
		bool mMouseInside;

		std::queue<Event> mEvents;
};

} // namespace nu

#endif // NU_WINDOWIMPL_HPP
