#include "Mouse.hpp"

#include "../System/Prerequisites.hpp"

#ifdef NU_PLATFORM_WINDOWS
	#include "Win32/InputImpl.hpp"
#endif // NU_PLATFORM_WINDOWS

namespace nu
{

Vector2i Mouse::getPosition()
{
	return InputImpl::getPosition();
}

Vector2i Mouse::getPosition(const Window& relativeTo)
{
	return InputImpl::getPosition(relativeTo);
}

bool Mouse::isButtonPressed(Button button)
{
	return InputImpl::isButtonPressed(button);
}

void Mouse::setPosition(const Vector2i& position)
{
	InputImpl::setPosition(position);
}

void Mouse::setPosition(const Vector2i& position, const Window& relativeTo)
{
	InputImpl::setPosition(position, relativeTo);
}

void Mouse::setPosition(I32 x, I32 y)
{
	InputImpl::setPosition(x, y);
}

void Mouse::setPosition(I32 x, I32 y, const Window& relativeTo)
{
	InputImpl::setPosition(x, y, relativeTo);
}

} // namespace nu
