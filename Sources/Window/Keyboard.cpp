#include "Keyboard.hpp"

#include "../System/Prerequisites.hpp"

#ifdef NU_PLATFORM_WINDOWS
#include "Win32/InputImpl.hpp"
#endif // NU_PLATFORM_WINDOWS

namespace nu
{

std::string Keyboard::getKeyName(Key key)
{
	return InputImpl::getKeyName(key);
}

bool InputImpl::isKeyPressed(Keyboard::Key key)
{
	return InputImpl::isKeyPressed(key);
}

} // namespace nu