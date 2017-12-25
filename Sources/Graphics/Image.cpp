#include "Image.hpp"

#include <cctype>

#define STB_IMAGE_IMPLEMENTATION
#include "../ExtLibs/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ExtLibs/stb/stb_image_write.h"

namespace nu
{

Image::Image()
	: mSize({ 0, 0 })
{
}

void Image::create(U32 width, U32 height, const Color& color)
{
	if (width && height)
	{
		std::vector<U8> newPixels(width * height * 4);
		U8* ptr = &newPixels[0];
		U8* end = ptr + newPixels.size();
		while (ptr < end)
		{
			*ptr++ = color.r;
			*ptr++ = color.g;
			*ptr++ = color.b;
			*ptr++ = color.a;
		}
		mPixels.swap(newPixels);
		mSize.x = width;
		mSize.y = height;
	}
	else
	{
		std::vector<U8>().swap(mPixels);
		mSize.x = 0;
		mSize.y = 0;
	}
}

void Image::create(U32 width, U32 height, const U8* pixels)
{
	if (pixels && width && height)
	{
		std::vector<U8> newPixels(pixels, pixels + width * height * 4);
		mPixels.swap(newPixels);
		mSize.x = width;
		mSize.y = height;
	}
	else
	{
		std::vector<U8>().swap(mPixels);
		mSize.x = 0;
		mSize.y = 0;
	}
}

bool Image::loadFromFile(const std::string& filename)
{
	mPixels.clear();
	int width = 0;
	int height = 0;
	int channels = 0;
	U8* ptr = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	if (ptr)
	{
		if (width && height)
		{
			mSize.x = width;
			mSize.y = height;
			mPixels.resize(width * height * 4);
			memcpy(&mPixels[0], ptr, mPixels.size());
		}
		else
		{
			mSize.x = 0;
			mSize.y = 0;
		}
		stbi_image_free(ptr);
		return true;
	}
	else
	{
		LogError(nu::LogChannel::Graphics, 2, "Failed to load image : %s. Reason : %s\n", filename.c_str(), stbi_failure_reason());
		return false;
	}
}

bool Image::saveToFile(const std::string& filename) const
{
	if (!mPixels.empty() && (mSize.x > 0) && (mSize.y > 0))
	{
		const I32 dot = filename.find_last_of('.');
		std::string extension = "";
		if (dot != std::string::npos)
		{
			extension = filename.substr(dot + 1);
			for (std::string::iterator i = extension.begin(); i != extension.end(); ++i)
				*i = static_cast<I8>(std::tolower(*i));
		}
		if (extension == "bmp")
		{
			if (stbi_write_bmp(filename.c_str(), mSize.x, mSize.y, 4, &mPixels[0]))
				return true;
		}
		else if (extension == "tga")
		{
			if (stbi_write_tga(filename.c_str(), mSize.x, mSize.y, 4, &mPixels[0]))
				return true;
		}
		else if (extension == "png")
		{
			if (stbi_write_png(filename.c_str(), mSize.x, mSize.y, 4, &mPixels[0], 0))
				return true;
		}
		else if (extension == "jpg" || extension == "jpeg")
		{
			if (stbi_write_jpg(filename.c_str(), mSize.x, mSize.y, 4, &mPixels[0], 90))
				return true;
		}
	}
	LogError(nu::LogChannel::Graphics, 2, "Failed to save image : %s\n", filename.c_str());
	return false;
}

const Vector2u& Image::getSize() const
{
	return mSize;
}

void Image::createMaskFromColor(const Color& color, U8 alpha)
{
	if (!mPixels.empty())
	{
		U8* ptr = &mPixels[0];
		U8* end = ptr + mPixels.size();
		while (ptr < end)
		{
			if ((ptr[0] == color.r) && (ptr[1] == color.g) && (ptr[2] == color.b) && (ptr[3] == color.a))
				ptr[3] = alpha;
			ptr += 4;
		}
	}
}

void Image::setPixel(U32 x, U32 y, const Color& color)
{
	U8* pixel = &mPixels[(x + y * mSize.x) * 4];
	*pixel++ = color.r;
	*pixel++ = color.g;
	*pixel++ = color.b;
	*pixel++ = color.a;
}

Color Image::getPixel(U32 x, U32 y) const
{
	const U8* pixel = &mPixels[(x + y * mSize.x) * 4];
	return Color(pixel[0], pixel[1], pixel[2], pixel[3]);
}

const U8* Image::getPixels() const
{
	if (!mPixels.empty())
	{
		return &mPixels[0];
	}
	else
	{
		LogError(nu::LogChannel::Graphics, 2, "Trying to access the pixels of an empty image\n");
		return nullptr;
	}
}

void Image::flipHorizontally()
{
	if (!mPixels.empty())
	{
		std::size_t rowSize = mSize.x * 4;
		for (std::size_t y = 0; y < mSize.y; y++)
		{
			std::vector<U8>::iterator left = mPixels.begin() + y * rowSize;
			std::vector<U8>::iterator right = mPixels.begin() + (y + 1) * rowSize - 4;
			for (std::size_t x = 0; x < mSize.x / 2; x++)
			{
				std::swap_ranges(left, left + 4, right);
				left += 4;
				right -= 4;
			}
		}
	}
}

void Image::flipVertically()
{
	if (!mPixels.empty())
	{
		std::size_t rowSize = mSize.x * 4;
		std::vector<U8>::iterator top = mPixels.begin();
		std::vector<U8>::iterator bottom = mPixels.end() - rowSize;
		for (std::size_t y = 0; y < mSize.y / 2; y++)
		{
			std::swap_ranges(top, top + rowSize, bottom);
			top += rowSize;
			bottom -= rowSize;
		}
	}
}

} // namespace nu