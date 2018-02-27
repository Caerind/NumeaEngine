#ifndef NU_TERRAIN_HPP
#define NU_TERRAIN_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Node.hpp"
#include "../Math/Noise.hpp"

namespace nu
{

class Terrain : public Node
{
	public:
		Terrain();

		void setTexture(Texture::Ptr texture);
		Texture::Ptr getTexture();

		F32 getSize() const;
		F32 getHeightScale() const;
		U32 getVertices() const;
		U32 getIndices() const;

		bool build(const nu::Image& image, F32 size, U32 verticesPerLine, F32 heightScale, bool buildNormals);

		void draw();

	private:
		Mesh mMesh;
		Shader mShader;
		Texture::Ptr mTexture;
		F32 mSize;
		F32 mHeightScale;
};

} // namespace nu

#endif // NU_SPRITE_HPP