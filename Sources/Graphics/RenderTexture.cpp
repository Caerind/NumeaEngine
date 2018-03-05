#include "RenderTexture.hpp"

#include "Renderer.hpp"

namespace nu
{

RenderTexture::RenderTexture()
	: RenderTarget()
	, mFBO(0)
{
	mTexture.setSmooth(true);
}

RenderTexture::~RenderTexture()
{
	destroy();
}

bool RenderTexture::create(U32 width, U32 height)
{
	destroy();

	mSize.set(width, height);

	// Frame Buffer
	mFBO = 0;
	glCheck(glGenFramebuffers(1, &mFBO));
	glCheck(glBindFramebuffer(GL_FRAMEBUFFER, mFBO));

	// Color Buffer
	mTexture.create(width, height);
	glCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, 1, GL_TEXTURE_2D, mTexture.getOpenGLId(), 0));

	// Depth Buffer
	mDepthBuffer.create(width, height, PixelFormat::Depth);
	glCheck(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer.getOpenGLId()));

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		LogError(nu::LogChannel::Graphics, 6, "RenderTexture : Can't create framebuffer");
		return false;
	}

	glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	glCheck(glBindRenderbuffer(GL_RENDERBUFFER, 0));
	glCheck(glBindFramebuffer(GL_FRAMEBUFFER, 0));

	return true;
}

void RenderTexture::destroy()
{
	if (isValid())
	{
		if (isActive())
		{
			Renderer::instance().setTarget(nullptr);
		}

		glCheck(glDeleteFramebuffers(1, &mFBO));
		mFBO = 0;

		mTexture.destroy();
		mDepthBuffer.destroy();
	}
}

Vector2u RenderTexture::getSize() const
{
	return mSize;
}

bool RenderTexture::isValid() const
{
	return glIsFramebuffer(mFBO) == GL_TRUE && mTexture.isValid() && mDepthBuffer.isValid();
}

U32 RenderTexture::getOpenGLId() const
{
	return mFBO;
}

bool RenderTexture::hasContext() const
{
	return false;
}

const Texture* RenderTexture::getTexture() const
{
	return &mTexture;
}

bool RenderTexture::activate() const
{
	static const GLenum colorAttachments[] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3
	};

	glCheck(glGetIntegerv(GL_VIEWPORT, mPrevViewport));
	glCheck(glBindTexture(GL_TEXTURE_2D, 0));
	glCheck(glBindFramebuffer(GL_FRAMEBUFFER, mFBO));
	glCheck(glDrawBuffers(1, colorAttachments));
	glCheck(glViewport(0, 0, mSize.x, mSize.y));

	return true;
}

void RenderTexture::deactivate() const
{
	glCheck(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	glCheck(glViewport(mPrevViewport[0], mPrevViewport[1], mPrevViewport[2], mPrevViewport[3]));
}

void RenderTexture::toWindow(U32 w, U32 h, U32 attachment)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
	glReadBuffer(attachment);
	glBlitFramebuffer(0, 0, mSize.x, mSize.y, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace nu