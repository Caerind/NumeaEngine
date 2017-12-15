#ifndef NU_TRIGONOMETRY_HPP
#define NU_TRIGONOMETRY_HPP

#include "../System/Prerequisites.hpp"
#include <cmath>

namespace nu
{

template <typename T>
inline T sin(T deg) 
{ 
	return std::sin(degToRad(deg)); 
}

template <typename T>
inline T cos(T deg) 
{ 
	return std::cos(degToRad(deg)); 
}

template <typename T>
inline T tan(T deg) 
{ 
	return std::tan(degToRad(deg)); 
}

template <typename T>
inline T asin(T value) 
{ 
	return radToDeg(std::asin(value)); 
}

template <typename T>
inline T acos(T value) 
{ 
	return radToDeg(std::acos(value));
}

template <typename T>
inline T atan(T value)
{
	return radToDeg(std::atan(value));
}

template <typename T>
inline T atan2(T valY, T valX) 
{ 
	return radToDeg(std::atan2(valY, valX)); 
}

template <typename T>
inline T sqrt(T value) 
{ 
	return std::sqrt(value);
}

template <typename T>
inline T pi()
{ 
	return 3.141592653589793238462643383f; 
}

template <typename T>
inline T radToDeg(T rad) 
{ 
	return 180.0f / pi() * rad; 
}

template <typename T>
inline T degToRad(T deg) 
{ 
	return pi() / 180.0f * deg; 
}

} // namespace nu

#endif // NU_TRIGONOMETRY_HPP