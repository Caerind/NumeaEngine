#ifndef NU_PIXEL_HPP
#define NU_PIXEL_HPP

#include "../Application/GLEWWrapper.hpp"

// TODO : Add pixel format
// TODO : Things to do here (type to memory, type to color...)
// TODO : Memory size : to get the size of a render buffer

namespace nu
{

enum class PixelFormat
{
	Undefined = -1,

	R8, // 1 * U8
	G8, // 1 * U8
	B8,	// 1 * U8
	A8, // 1 * U8

	R16, // 1 * U16
	G16, // 1 * U16
	B16, // 1 * U16
	A16, // 1 * U16

	R32, // 1 * U32
	G32, // 1 * U32
	B32, // 1 * U32
	A32, // 1 * U32

	R32F, // 1 * F32
	G32F, // 1 * F32
	B32F, // 1 * F32
	A32F, // 1 * F32

	RGB8, // 3 * U8
	RGB16, // 3 * U16
	RGB32, // 3 * U32
	RGB32F, // 3 * F32

	RGBA8, // 4 * U8
	RGBA16, // 4 * U16
	RGBA32, // 4 * U32
	RGBA32F, // 4 * F32

	Depth16, // 1 * U16
	Depth32, // 1 * U32
	Depth32F, // 1 * F32

	Stencil1,
	Stencil4,
	Stencil8,
	Stencil16,

	DepthStencil
};

inline bool isPixelFormatValid(PixelFormat pxFormat)
{
	return pxFormat != PixelFormat::Undefined;
}

inline GLenum convertPixelFormat(PixelFormat pxFormat)
{
	switch (pxFormat)
	{
		case PixelFormat::R8: return GL_R8UI; break;
		case PixelFormat::G8: return GL_R8UI; break;
		case PixelFormat::B8: return GL_R8UI; break;
		case PixelFormat::A8: return GL_R8UI; break;
		case PixelFormat::R16: return GL_R16UI; break;
		case PixelFormat::G16: return GL_R16UI; break;
		case PixelFormat::B16: return GL_R16UI; break;
		case PixelFormat::A16: return GL_R16UI; break;
		case PixelFormat::R32: return GL_R32UI; break;
		case PixelFormat::G32: return GL_R32UI; break;
		case PixelFormat::B32: return GL_R32UI; break;
		case PixelFormat::A32: return GL_R32UI; break;
		case PixelFormat::R32F: return GL_R32F; break;
		case PixelFormat::G32F: return GL_R32F; break;
		case PixelFormat::B32F: return GL_R32F; break;
		case PixelFormat::A32F: return GL_R32F; break;
		case PixelFormat::RGB8: return GL_RGB8UI; break;
		case PixelFormat::RGB16: return GL_RGB16UI; break;
		case PixelFormat::RGB32: return GL_RGB32UI; break;
		case PixelFormat::RGB32F: return GL_RGB32F; break;
		case PixelFormat::RGBA8: return GL_RGBA8UI; break;
		case PixelFormat::RGBA16: return GL_RGBA16UI; break;
		case PixelFormat::RGBA32: return GL_RGBA32UI; break;
		case PixelFormat::RGBA32F: return GL_RGBA32F; break;
		case PixelFormat::Depth16: return GL_DEPTH_COMPONENT16; break;
		case PixelFormat::Depth32: return GL_DEPTH_COMPONENT32; break;
		case PixelFormat::Depth32F: return GL_DEPTH_COMPONENT32F; break;
		case PixelFormat::Stencil1: return GL_STENCIL_INDEX1; break;
		case PixelFormat::Stencil4: return GL_STENCIL_INDEX4; break;
		case PixelFormat::Stencil8: return GL_STENCIL_INDEX8; break;
		case PixelFormat::Stencil16: return GL_STENCIL_INDEX16; break;
		case PixelFormat::DepthStencil: return GL_DEPTH_STENCIL; break;
	}
	return GL_RGBA;
}

} // namespace nu

#endif // NU_PIXEL_HPP