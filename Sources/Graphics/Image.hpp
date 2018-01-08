#ifndef NU_IMAGE_HPP
#define NU_IMAGE_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "Color.hpp"
#include "../Math/Vector2.hpp"
#include "../Application/Resource.hpp"

namespace nu
{

class Image : public Resource<Image>
{
	public:
		Image();

		bool load(const nu::Loader<Image>& loader);
		bool save(const nu::Saver<Image>& saver);

		void create(U32 width, U32 height, const Color& color = Color(0, 0, 0));
		void create(U32 width, U32 height, const U8* pixels);
		
		const Vector2u& getSize() const;

		void createMaskFromColor(const Color& color, U8 alpha = 0);

		void setPixel(U32 x, U32 y, const Color& color);
		Color getPixel(U32 x, U32 y) const;

		const U8* getPixels() const;

		bool resize(U32 newWidth, U32 newHeight);
		bool resize(F32 widthScale, F32 heightScale);

		void flipHorizontally();
		void flipVertically();

	private:
		std::vector<U8> mPixels;
		Vector2u mSize;
};

class ImageLoader
{
	public:
		static Loader<Image> fromFile(const std::string& filename);
		static Loader<Image> fromMemory(const void* data, U32 dataSize);

		static Saver<Image> toFile(const std::string& filename);
};

} // namespace nu

#endif // NU_IMAGE_HPP