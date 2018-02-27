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

bool RenderBuffer::create(U32 width, U32 height, PixelFormat format)
{
	destroy();

	if (width == 0 || height == 0)
	{
		LogError(nu::LogChannel::Graphics, 6, "RenderBuffer : Invalid size");
		return false;
	}

	if (!isPixelFormatValid(format))
	{
		LogError(nu::LogChannel::Graphics, 6, "RenderBuffer : Undefined pixel format");
		return false;
	}

	mBuffer = 0;
	glCheck(glGenRenderbuffers(1, &mBuffer));
	if (!isValid())
	{
		LogError(nu::LogChannel::Graphics, 6, "RenderBuffer : Failed to create RenderBuffer");
		return false;
	}

	glCheck(glBindRenderbuffer(GL_RENDERBUFFER, mBuffer));
	glCheck(glRenderbufferStorage(GL_RENDERBUFFER, convertPixelFormat(format), width, height));

	mSize.set(width, height);
	mFormat = format;
	
	return true;
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

PixelFormat RenderBuffer::getFormat() const
{
	return mFormat;
}

void RenderBuffer::bind()
{
	glCheck(glBindRenderbuffer(GL_RENDERBUFFER, mBuffer));
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