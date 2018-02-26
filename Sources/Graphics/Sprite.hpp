#ifndef NU_SPRITE_HPP
#define NU_SPRITE_HPP

#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Node.hpp"
#include "TransformBinder.hpp"

namespace nu
{

class Sprite : public TransformBinder
{
	public:
		Sprite();

		void setTexture(Texture::Ptr texture);
		Texture::Ptr getTexture();

		void setSize(F32 x, F32 y);
		void setSize(const Vector2f& size);
		const Vector2f& getSize() const;

		void useNormals(bool use);
		bool hasNormals() const;

		void draw();

	private:
		void update();

	private:
		VertexBuffer mVertices;
		Vector2f mSize;
		bool mUseNormals;
		bool mNeedUpdate;
		Texture::Ptr mTexture;
};

} // namespace nu

#endif // NU_SPRITE_HPP