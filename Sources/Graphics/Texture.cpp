#include "Texture.hpp"

namespace nu
{

Texture::Texture()
	: mIndex(0)
	, mSize({ 0,0 })
	, mActualSize({ 0,0 })
	, mIsSmooth(false)
	, mHasMipmap(false)
{
	glGenTextures(1, &mIndex);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mIndex);
}

bool Texture::load(const Loader<Texture>& loader)
{
	mLoaded = loader.load(*this);
	return mLoaded;
}

bool Texture::create(U32 width, U32 height)
{
	if ((width == 0) || (height == 0))
	{
		LogError(LogChannel::Graphics, 3, "Failed to create texture, invalid size (%dx%d)\n", width, height);
		return false;
	}
	Vector2u actualSize(getValidSize(width), getValidSize(height));
	U32 maxSize = getMaximumSize();
	if ((actualSize.x > maxSize) || (actualSize.y > maxSize))
	{
		LogError(LogChannel::Graphics, 3, "Failed to create texture, its internal size is too high (%dx%d), maximum is (%dx%d)\n", actualSize.x, actualSize.y, maxSize, maxSize);
		return false;
	}
	mSize.x = width;
	mSize.y = height;
	mActualSize = actualSize;

	glBindTexture(GL_TEXTURE_2D, mIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mActualSize.x, mActualSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mIsSmooth ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mIsSmooth ? GL_LINEAR : GL_NEAREST);
	mHasMipmap = false;
	return true;
}

void Texture::update(const Image& image)
{
	update(image.getPixels(), image.getSize().x, image.getSize().y, 0, 0);
}

void Texture::update(const Image& image, U32 x, U32 y)
{
	update(image.getPixels(), image.getSize().x, image.getSize().y, x, y);
}

void Texture::update(const U8* pixels)
{
	update(pixels, mSize.x, mSize.y, 0, 0);
}

void Texture::update(const U8* pixels, U32 width, U32 height, U32 x, U32 y)
{
	if (pixels && mIndex)
	{
		glBindTexture(GL_TEXTURE_2D, mIndex);
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mIsSmooth ? GL_LINEAR : GL_NEAREST);
		mHasMipmap = false;
	}
}

void Texture::update(const Texture& texture)
{
	update(texture, 0, 0);
}

void Texture::update(const Texture& texture, U32 x, U32 y)
{
	if (!glIsTexture(mIndex) || !glIsTexture(texture.mIndex))
		return;

	if (GL_EXT_framebuffer_object && GL_EXT_framebuffer_blit)
	{
		// Save the current bindings so we can restore them after we are done
		GLint readFramebuffer = 0;
		GLint drawFramebuffer = 0;

		glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFramebuffer);
		glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFramebuffer);

		// Create the framebuffers
		GLuint sourceFrameBuffer = 0;
		GLuint destFrameBuffer = 0;
		glGenFramebuffers(1, &sourceFrameBuffer);
		glGenFramebuffers(1, &destFrameBuffer);

		if (!sourceFrameBuffer || !destFrameBuffer)
		{
			LogError(LogChannel::Graphics, 3, "Cannot copy texture, failed to create a frame buffer object\n");
			return;
		}

		// Link the source texture to the source frame buffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, sourceFrameBuffer);
		glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.mIndex, 0);

		// Link the destination texture to the destination frame buffer
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, destFrameBuffer);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mIndex, 0);

		// A final check, just to be sure...
		GLenum sourceStatus = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);
		GLenum destStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

		if ((sourceStatus == GL_FRAMEBUFFER_COMPLETE) && (destStatus == GL_FRAMEBUFFER_COMPLETE))
		{
			// Blit the texture contents from the source to the destination texture
			glBlitFramebuffer(0, 0, texture.mSize.x, texture.mSize.y, x, y, x + texture.mSize.x, y + texture.mSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
		else
		{
			LogError(LogChannel::Graphics, 3, "Cannot copy texture, failed to link texture to frame buffer\n");
		}

		// Restore previously bound framebuffers
		glBindFramebuffer(GL_READ_FRAMEBUFFER, readFramebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFramebuffer);

		// Delete the framebuffers
		glDeleteFramebuffers(1, &sourceFrameBuffer);
		glDeleteFramebuffers(1, &destFrameBuffer);

		return;
	}

	update(texture.copyToImage(), x, y);
}

Image Texture::copyToImage() const
{
	if (!glIsTexture(mIndex))
		return Image();
	std::vector<U8> pixels(mSize.x * mSize.y * 4);
	if ((mSize == mActualSize))
	{
		glBindTexture(GL_TEXTURE_2D, mIndex);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
	}
	else
	{
		std::vector<U8> allPixels(mActualSize.x * mActualSize.y * 4);
		glBindTexture(GL_TEXTURE_2D, mIndex);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, &allPixels[0]);
		const U8* src = &allPixels[0];
		U8* dst = &pixels[0];
		U32 srcPitch = mActualSize.x * 4;
		U32 dstPitch = mSize.x * 4;
		for (U32 i = 0; i < mSize.y; i++)
		{
			std::memcpy(dst, src, dstPitch);
			src += srcPitch;
			dst += dstPitch;
		}
	}
	Image image;
	image.create(mSize.x, mSize.y, &pixels[0]);
	return image;
}

void Texture::setSmooth(bool smooth)
{
	if (smooth != mIsSmooth)
	{
		mIsSmooth = smooth;
		if (glIsTexture(mIndex))
		{
			glBindTexture(GL_TEXTURE_2D, mIndex);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mIsSmooth ? GL_LINEAR : GL_NEAREST);
			if (mHasMipmap)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mIsSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mIsSmooth ? GL_LINEAR : GL_NEAREST);
			}
		}
	}
}

bool Texture::isSmooth() const
{
	return mIsSmooth;
}

bool Texture::generateMipmap()
{
	if (!glIsTexture(mIndex))
		return false;
	glBindTexture(GL_TEXTURE_2D, mIndex);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mIsSmooth ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_LINEAR);
	mHasMipmap = true;
	return true;
}

void Texture::invalidateMipmap()
{
	if (!mHasMipmap)
		return;
	glBindTexture(GL_TEXTURE_2D, mIndex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mIsSmooth ? GL_LINEAR : GL_NEAREST);
	mHasMipmap = false;
}

bool Texture::hasMipmap() const
{
	return mHasMipmap;
}

void Texture::swap(Texture& right)
{
	std::swap(mIndex, right.mIndex);
	std::swap(mSize, right.mSize);
	std::swap(mActualSize, right.mActualSize);
	std::swap(mIsSmooth, right.mIsSmooth);
	std::swap(mHasMipmap, right.mHasMipmap);
}

const Vector2u& Texture::getSize() const
{
	return mSize;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, mIndex);
}

bool Texture::isValid() const
{
	return glIsTexture(mIndex) == GL_TRUE;
}

U32 Texture::getIndex() const
{
	return mIndex;
}

U32 Texture::getMaximumSize()
{
	I32 size = 0;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
	return U32(size);
}

U32 Texture::getValidSize(U32 size) const
{
	if (GL_ARB_texture_non_power_of_two)
	{
		return size; // If hardware supports NPOT textures, then just return the unmodified size
	}
	else
	{
		// If hardware doesn't support NPOT textures, we calculate the nearest power of two
		U32 powerOfTwo = 1;
		while (powerOfTwo < size)
			powerOfTwo *= 2;
		return powerOfTwo;
	}
}

Loader<Texture> TextureLoader::fromFile(const std::string& filename)
{
	return Loader<Texture>([=](Texture& texture)
	{
		Image image;
		if (!image.load(ImageLoader::fromFile(filename)))
		{
			return false;
		}
		Vector2u size = image.getSize();
		if (texture.create(size.x, size.y))
		{
			texture.update(image);
			return true;
		}
		return false;
	});
}

Loader<Texture> TextureLoader::fromImage(const Image& image)
{
	return Loader<Texture>([=](Texture& texture)
	{
		Vector2u size = image.getSize();
		if (texture.create(size.x, size.y))
		{
			texture.update(image);
			return true;
		}
		return false;
	});
}

} // namespace nu