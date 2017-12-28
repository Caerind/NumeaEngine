#ifndef NU_TEXTURE_HPP
#define NU_TEXTURE_HPP

#include "Image.hpp"
#include "../Application/GLEWWrapper.hpp"

namespace nu
{

class Texture : public Resource<Texture>
{
	public:
		Texture();
		~Texture();

		bool load(const Loader<Texture>& loader);

		bool create(U32 width, U32 height);

		void update(const Image& image);
		void update(const Image& image, U32 x, U32 y);
		void update(const U8* pixels);
		void update(const U8* pixels, U32 width, U32 height, U32 x, U32 y);
		void update(const Texture& texture);
		void update(const Texture& texture, U32 x, U32 y);

		Image copyToImage() const;

		void setSmooth(bool smooth);
		bool isSmooth() const;

		bool generateMipmap();
		void invalidateMipmap();
		bool hasMipmap() const;

		void swap(Texture& right);

		const Vector2u& getSize() const;

		void bind() const;
		bool isValid() const;

		U32 getIndex() const;

		static U32 getMaximumSize();

	private:
		U32 getValidSize(U32 size) const;

	private:
		U32 mIndex;
		Vector2u mSize;
		Vector2u mActualSize;
		bool mIsSmooth;
		bool mHasMipmap;
};

class TextureLoader
{
	public:
		static Loader<Texture> fromFile(const std::string& filename);
		static Loader<Texture> fromImage(const Image& image);
};

} // namespace nu

#endif // NU_TEXTURE_HPP