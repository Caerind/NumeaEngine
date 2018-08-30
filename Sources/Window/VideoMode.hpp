#ifndef NU_VIDEOMODE_HPP
#define NU_VIDEOMODE_HPP

#include <vector>

namespace nu
{

class VideoMode
{
	public:
		VideoMode();
		VideoMode(unsigned int w, unsigned int h);
		VideoMode(unsigned int w, unsigned int h, unsigned char bpp);

		bool isFullscreenValid() const;

		unsigned char bitsPerPixel;
		unsigned int height;
		unsigned int width;

		static VideoMode getDesktopMode();
		static const std::vector<VideoMode>& getFullscreenModes();
};

bool operator==(const VideoMode& left, const VideoMode& right);
bool operator!=(const VideoMode& left, const VideoMode& right);
bool operator<(const VideoMode& left, const VideoMode& right);
bool operator<=(const VideoMode& left, const VideoMode& right);
bool operator>(const VideoMode& left, const VideoMode& right);
bool operator>=(const VideoMode& left, const VideoMode& right);

} // namespace nu

#endif // NU_VIDEOMODE_HPP

