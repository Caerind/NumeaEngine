#ifndef NU_RENDERBUFFER_HPP
#define NU_RENDERBUFFER_HPP

#include "../Application/GLEWWrapper.hpp"
#include "../Math/Vector2.hpp"

// TODO : PixelFormat

namespace nu
{

class RenderBuffer
{
	public:
		RenderBuffer();
		NU_NON_COPYABLE(RenderBuffer);
		~RenderBuffer();

		bool create(U32 width, U32 height);
		void destroy();

		const Vector2u& getSize() const;

		bool isValid() const;
		U32 getOpenGLId() const;

	private:
		Vector2u mSize;
		U32 mBuffer;
};

} // namespace nu

#endif // NU_RENDERBUFFER_HPP