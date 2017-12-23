#ifndef NU_TRIGONOMETRY_HPP
#define NU_TRIGONOMETRY_HPP

#include "../System/Prerequisites.hpp"
#include <cmath>

namespace nu
{

template <typename T>
inline T sin(T deg) 
{ 
	return std::sin(degToRad<T>(deg)); 
}

template <typename T>
inline T cos(T deg) 
{ 
	return std::cos(degToRad<T>(deg));
}

template <typename T>
inline T tan(T deg) 
{ 
	return std::tan(degToRad<T>(deg));
}

template <typename T>
inline T asin(T value) 
{ 
	return radToDeg<T>(std::asin(value));
}

template <typename T>
inline T acos(T value) 
{ 
	return radToDeg<T>(std::acos(value));
}

template <typename T>
inline T atan(T value)
{
	return radToDeg<T>(std::atan(value));
}

template <typename T>
inline T atan2(T valY, T valX) 
{ 
	return radToDeg<T>(std::atan2(valY, valX));
}

template <typename T>
inline T sqrt(T value) 
{ 
	return std::sqrt(value);
}

template <typename T>
inline T pi()
{ 
	return T(3.141592653589793238462643383); 
}

template <typename T>
inline T radToDeg(T rad) 
{ 
	return T(180.0) / pi<T>() * rad; 
}

template <typename T>
inline T degToRad(T deg) 
{ 
	return pi<T>() / T(180.0) * deg; 
}

} // namespace nu

#endif // NU_TRIGONOMETRY_HPP