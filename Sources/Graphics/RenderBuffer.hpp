#ifndef NU_RENDERBUFFER_HPP
#define NU_RENDERBUFFER_HPP

#include "../Application/GLEWWrapper.hpp"
#include "../Math/Vector2.hpp"
#include "Pixel.hpp"

namespace nu
{

class RenderBuffer
{
	public:
		RenderBuffer();
		NU_NON_COPYABLE(RenderBuffer);
		~RenderBuffer();

		bool create(U32 width, U32 height, PixelFormat format);
		void destroy();

		const Vector2u& getSize() const;
		PixelFormat getFormat() const;

		bool isValid() const;
		U32 getOpenGLId() const;

	private:
		Vector2u mSize;
		PixelFormat mFormat;
		U32 mBuffer;
};

} // namespace nu

#endif // NU_RENDERBUFFER_HPP