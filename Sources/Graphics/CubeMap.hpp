#ifndef NU_CUBEMAP_HPP
#define NU_CUBEMAP_HPP

#include "VertexBuffer.hpp"
#include "Shader.hpp"

namespace nu
{

class CubeMap
{
	public:
		CubeMap();

		enum Side
		{
			NegZ,
			PosZ,
			NegY,
			PosY,
			NegX,
			PosX
		};

		struct TextureSide
		{
			TextureSide(Side pS, const std::string& pFilename) : s(pS), filename(pFilename) {}

			Side s;
			std::string filename;
		};

		void setSize(F32 size);
		F32 getSize() const;

		bool loadTexture(const std::vector<TextureSide>& sides);
		bool loadSide(Side side, const std::string& filename);

		void draw();

	private:
		static GLenum convertSide(Side side);

	private:
		VertexBuffer mVertices;
		Shader mShader;
		U32 mTexture;
		F32 mSize;
};

} // namespace nu

#endif // NU_CUBEMAP_HPP