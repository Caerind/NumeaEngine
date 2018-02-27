#include "RenderBuffer.hpp"

#include "Renderer.hpp"

namespace nu
{

RenderBuffer::RenderBuffer()
	: mSize(0, 0)
	, mBuffer(0)
{
}

RenderBuffer::~RenderBuffer()
{
	destroy();
}

bool RenderBuffer::create(U32 width, U32 height)
{
	destroy();

	if (width == 0 || height == 0)
	{
		LogError(nu::LogChannel::Graphics, 6, "RenderBuffer : Invalid size");
		return false;
	}

	mBuffer = 0;
	glGenRenderbuffers(1, &mBuffer);
	if (!isValid())
	{
		LogError(nu::LogChannel::Graphics, 6, "RenderBuffer : Failed to create RenderBuffer");
		return false;
	}

	// Get the previous renderbuffer
	I32 previous;
	glGetIntegerv(GL_RENDERBUFFER_BINDING, &previous);

	// Define the format of the new renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, mBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, width, height);

	// Reset the previous renderbuffer
	if (glIsRenderbuffer(previous) == GL_TRUE)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, previous);
	}

	mSize.set(width, height);
	
	return false;
}

void RenderBuffer::destroy()
{
	if (isValid())
	{
		glDeleteRenderbuffers(1, &mBuffer);
		mBuffer = 0;
	}
}

const Vector2u& RenderBuffer::getSize() const
{
	return mSize;
}

bool RenderBuffer::isValid() const
{
	return glIsRenderbuffer(mBuffer) == GL_TRUE;
}

U32 RenderBuffer::getOpenGLId() const
{
	return mBuffer;
}

} // namespace nu