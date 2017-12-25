#ifndef NU_IMAGE_HPP
#define NU_IMAGE_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "Color.hpp"
#include "../Math/Vector2.hpp"

// TODO : Load From Memory

namespace nu
{

class Image
{
	public:
		Image();

		void create(U32 width, U32 height, const Color& color = Color(0, 0, 0));
		void create(U32 width, U32 height, const U8* pixels);

		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename) const; 
		
		const Vector2u& getSize() const;

		void createMaskFromColor(const Color& color, U8 alpha = 0);

		void setPixel(U32 x, U32 y, const Color& color);
		Color getPixel(U32 x, U32 y) const;

		const U8* getPixels() const;

		void flipHorizontally();
		void flipVertically();

	private:
		std::vector<U8> mPixels;
		Vector2u mSize;
};

} // namespace nu

#endif // NU_IMAGE_HPP