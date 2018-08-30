#include "VideoMode.hpp"

#include <algorithm>
#include <functional>

#include "../System/Prerequisites.hpp"

#ifdef NU_PLATFORM_WINDOWS
	#include <windows.h>
#endif // NU_PLATFORM_WINDOWS

namespace nu
{

VideoMode::VideoMode()
	: bitsPerPixel(0)
	, height(0)
	, width(0)
{
}

VideoMode::VideoMode(unsigned int w, unsigned int h) 
	: VideoMode(w, h, getDesktopMode().bitsPerPixel)
{
}

VideoMode::VideoMode(unsigned int w, unsigned int h, unsigned char bpp) 
	: bitsPerPixel(bpp)
	, height(h)
	, width(w)
{
}

bool VideoMode::isFullscreenValid() const
{
	const std::vector<VideoMode>& modes = getFullscreenModes();
	return std::binary_search(modes.begin(), modes.end(), *this, std::greater<VideoMode>());
}

VideoMode VideoMode::getDesktopMode()
{
	#ifdef NU_PLATFORM_WINDOWS
		DEVMODE mode;
		mode.dmSize = sizeof(DEVMODE);
		EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &mode);
		return VideoMode(mode.dmPelsWidth, mode.dmPelsHeight, static_cast<unsigned char>(mode.dmBitsPerPel));
	#endif // NU_PLATFORM_WINDOWS
	return VideoMode();
}

const std::vector<VideoMode>& VideoMode::getFullscreenModes()
{
	static std::vector<VideoMode> modes;
	if (modes.size() == 0)
	{
		#ifdef NU_PLATFORM_WINDOWS
			DEVMODE win32Mode;
			win32Mode.dmSize = sizeof(DEVMODE);
			for (unsigned int i = 0; EnumDisplaySettings(nullptr, i, &win32Mode); ++i)
			{
				VideoMode mode(win32Mode.dmPelsWidth, win32Mode.dmPelsHeight, static_cast<unsigned char>(win32Mode.dmBitsPerPel));
				if (std::find(modes.begin(), modes.end(), mode) == modes.end())
				{
					modes.push_back(mode);
				}
			}
			std::sort(modes.begin(), modes.end(), std::greater<VideoMode>());
		#endif // NU_PLATFORM_WINDOWS
	}
	return modes;
}

bool operator==(const VideoMode& left, const VideoMode& right)
{
	return left.width == right.width && left.height == right.height && left.bitsPerPixel == right.bitsPerPixel;
}

bool operator!=(const VideoMode& left, const VideoMode& right)
{
	return left.width != right.width || left.height != right.height || left.bitsPerPixel != right.bitsPerPixel;
}

bool operator<(const VideoMode& left, const VideoMode& right)
{
	if (left.bitsPerPixel == right.bitsPerPixel)
	{
		if (left.width == right.width)
		{
			return left.height < right.height;
		}
		else
		{
			return left.width < right.width;
		}
	}
	else
	{
		return left.bitsPerPixel < right.bitsPerPixel;
	}
}

bool operator<=(const VideoMode& left, const VideoMode& right)
{
	if (left.bitsPerPixel == right.bitsPerPixel)
	{
		if (left.width == right.width)
		{
			return left.height <= right.height;
		}
		else
		{
			return left.width < right.width;
		}
	}
	else
	{
		return left.bitsPerPixel < right.bitsPerPixel;
	}
}

bool operator>(const VideoMode& left, const VideoMode& right)
{
	return right < left;
}

bool operator>=(const VideoMode& left, const VideoMode& right)
{
	return right <= left;
}

} // namespace nu