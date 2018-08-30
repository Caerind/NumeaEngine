#include "Window.hpp"

#include "../System/Prerequisites.hpp"

#ifdef NU_PLATFORM_WINDOWS
#include "Win32/WindowImpl.hpp"
#endif // NU_PLATFORM_WINDOWS

namespace nu
{

Window::Window()
	: mImpl(nullptr)
	, mSize(0, 0)
{
}

Window::Window(WindowHandle handle)
	: Window()
{
	create(handle);
}

Window::Window(VideoMode mode, const std::string& title) 
	: Window()
{
	create(mode, title);
}

Window::~Window()
{
	close();
}

bool Window::create(WindowHandle handle)
{
	close();

	mImpl = new WindowImpl(handle);

	if (!initialize())
	{
		return false;
	}

	return true;
}

bool Window::create(VideoMode mode, const std::string& title)
{
	close();

	mImpl = new WindowImpl(mode, title);

	if (!initialize())
	{
		return false;
	}

	return true;
}

void Window::close()
{
	if (mImpl != nullptr)
	{
		delete mImpl;
		mImpl = nullptr;
	}
}

bool Window::isOpen() const
{
	return mImpl != nullptr;
}

bool Window::pollEvent(Event& event)
{
	if (isOpen() && mImpl->popEvent(event, false))
	{
		return filterEvent(event);
	}
	else
	{
		return false;
	}
}

bool Window::waitEvent(Event& event)
{
	if (isOpen() && mImpl->popEvent(event, true))
	{
		return filterEvent(event);
	}
	else
	{
		return false;
	}
}

void Window::setPosition(I32 x, I32 y)
{
	if (isOpen())
	{
		mImpl->setPosition(x, y);
	}
}

void Window::setPosition(const Vector2i& position)
{
	if (isOpen())
	{
		mImpl->setPosition(position);
	}
}

Vector2i Window::getPosition() const
{
	return (isOpen()) ? mImpl->getPosition() : Vector2i();
}

void Window::setSize(U32 width, U32 height)
{
	if (isOpen())
	{
		mImpl->setSize(width, height);
	}
}

void Window::setSize(const Vector2u& size)
{
	if (isOpen())
	{
		mImpl->setSize(size);
	}
}

Vector2u Window::getSize() const
{
	return mSize;
}

void Window::requestFocus()
{
	if (isOpen())
	{
		mImpl->requestFocus();
	}
}

bool Window::hasFocus() const
{
	return isOpen() && mImpl->hasFocus();
}

WindowHandle Window::getSystemHandle()
{
	return (isOpen()) ? mImpl->getSystemHandle() : nullptr;
}

void Window::onCreate()
{
}

void Window::onResize()
{
}

bool Window::filterEvent(const Event& event)
{
	if (event.type == Event::Resized)
	{
		mSize.x = event.size.width;
		mSize.y = event.size.height;
		onResize();
	}

	return true;
}

bool Window::initialize()
{
	/*
	// Setup default behaviors (to get a consistent behavior across different implementations)
	setVisible(true);
	setMouseCursorVisible(true);
	setVerticalSyncEnabled(false);
	setKeyRepeatEnabled(true);
	setFramerateLimit(0);
	*/

	// Get and cache the initial size of the window
	mSize = mImpl->getSize();

	/*
	// Activate the window
	setActive();
	*/

	// Notify the derived class
	onCreate();

	return true;
}

} // namespace nu
