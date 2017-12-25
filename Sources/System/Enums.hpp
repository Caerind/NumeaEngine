#ifndef NU_ENUMS_HPP
#define NU_ENUMS_HPP

#include "Macros.hpp"

namespace nu
{

// Platforms
enum class Platform
{
	Unknown = -1,
	Android,
	iOS,
	macOS,
	Linux,
	Windows
};

// Compilers
enum class Compiler
{
	Unknown = -1, 
	Clang,
	GCC, 
	Intel, 
	MSVC
};

// Endianness
enum class Endianness
{
	Unknown = -1,
	BigEndian,
	LittleEndian
};

// Build
enum class Build
{
	Debug,
	Release,
	Profile,
	Deploy
};

// LogType
enum class LogType : U32
{
	None = 0x0,
	Info = 0x1,
	Warning = 0x2,
	Error = 0x4,
	All = 0x7
};

// LogChannel
enum class LogChannel : U32
{ 
	None        = 0x00,
	Global      = 0x01,
	System      = 0x02, 
	Math        = 0x04,
	Application = 0x08,
	Graphics    = 0x10,
	// TODO : Add others
	All         = 0xFF,
};

} // namespace nu


inline constexpr nu::Platform getPlatform()
{
	#ifdef NU_PLATFORM_ANDROID
		return nu::Platform::Android;
	#elif defined NU_PLATFORM_IOS
		return nu::Platform::iOS;
	#elif defined NU_PLATFORM_MACOS
		return nu::Platform::macOS;
	#elif defined NU_PLATFORM_LINUX
		return nu::Platform::Linux;
	#elif defined NU_PLATFORM_WINDOWS
		return nu::Platform::Windows;
	#else
		#error Unknown platform
	#endif
}

inline constexpr nu::Endianness getEndianness()
{
	#ifdef NU_ENDIAN_BIG
		return nu::Endianness::BigEndian;
	#elif defined NU_ENDIAN_LITTLE
		return nu::Endianness::LittleEndian;
	#else
		#error Unknown endianness
	#endif
}

inline constexpr nu::Compiler getCompiler()
{
	#ifdef NU_COMPILER_CLANG
		return nu::Compiler::Clang;
	#elif defined NU_COMPILER_GCC
		return nu::Compiler::GCC;
	#elif defined NU_COMPILER_INTEL
		return nu::Compiler::Intel;
	#elif defined NU_COMPILER_MSVC
		return nu::Compiler::MSVC;
	#else
		#error Unknown compiler
	#endif
}

inline constexpr nu::Build getBuild()
{
	#ifdef NU_BUILD_DEBUG
		return nu::Build::Debug;
	#elif defined NU_BUILD_RELEASE
		return nu::Build::Release;
	#elif defined NU_BUILD_PROFILE
		return nu::Build::Profile;
	#elif defined NU_BUILD_DEPLOY
		return nu::Build::Deploy;
	#else
		#error Unknown build
	#endif
}

#endif // NU_ENUMS_HPP
