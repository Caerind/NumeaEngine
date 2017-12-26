#ifndef NU_MACROS_HPP
#define NU_MACROS_HPP

#include "Platform.hpp"

#include <type_traits>

#define NU_PREPROCESSOR_TOSTRING(x) NU_PREPROCESSOR_TOSTRING_IMPL(x)
#define NU_PREPROCESSOR_TOSTRING_IMPL(x) #x

#define NU_NON_COPYABLE(Type) \
	Type(const Type&) = delete; \
	void operator=(const Type&) = delete;

#define NU_NON_MOVABLE(Type) \
	Type(Type&&) = delete; \
	void operator=(Type&&) = delete;

#define NU_ALIGN(x) __declspec(align(x))
#define NU_ALIGN16 NU_ALIGN(16)
#define NU_ALIGN32 NU_ALIGN(32)
#define NU_ALIGN64 NU_ALIGN(64)
#define NU_ALIGN128 NU_ALIGN(128)

#ifdef assert
#undef assert
#endif
#if NU_ENABLE_ASSERT
	#define assert(expr) \
		if (expr) {} \
		else \
		{ \
			printf("Assertion failed!\nExpr : %s\n File : %s\n Line : %d\n", #expr, __FILE__, __LINE__); \
			for (;;) {} \
		}
#else
	#define assert
#endif

#if defined(NU_COMPILER_MSVC)
	// Note: On newer MSVC versions, using deprecated functions causes a compiler error. In order to
	// trigger a warning instead of an error, the compiler flag /sdl- (instead of /sdl) must be specified.
	#define NU_DEPRECATED __declspec(deprecated)
#elif defined(NU_COMPILER_GCC) || defined(NU_COMPILER_CLANG)
	#define NU_DEPRECATED __attribute__ ((deprecated))
#else
	// Other compilers are not supported, leave class or function as-is.
	// With a bit of luck, the #pragma directive works, otherwise users get a warning (no error!) for unrecognized #pragma.
	#pragma message("NU_DEPRECATED is not supported for this compiler")
	#define NU_DEPRECATED
#endif

#define NU_STATIC_BASE_OF(Base, Derived) static_assert(std::is_base_of<Base, Derived>::value, #Derived " must be a descendant of " #Base);
#define NU_BASE_OF(Base, Derived) bool(std::is_base_of<Base, Derived>::value));

namespace nu
{

namespace priv
{

template <typename T, typename M> M getMemberType(M T::*);
template <typename T, typename M> T getClassType(M T::*);

template <typename T, typename R, typename R T::*M>
constexpr std::size_t OffsetOf()
{
	return reinterpret_cast<std::size_t>(&((static_cast<T*>(0))->*M));
}

} // namespace priv
} // namespace nu

#define NU_OFFSET_OF(M) nu::priv::OffsetOf<decltype(getClassType(M)), decltype(getMemberType(M)), M>()


#endif // NU_MACROS_HPP
