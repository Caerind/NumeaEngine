#ifndef NU_WINDOWHANDLE_HPP
#define NU_WINDOWHANDLE_HPP

#include "../System/Prerequisites.hpp"

namespace nu
{

	#if defined(NU_PLATFORM_WINDOWS)
	using WindowHandle = void*;
	#endif // NU_PLATFORM_WINDOWS

} // namespace nu

#endif // NU_WINDOWHANDLE_HPP
