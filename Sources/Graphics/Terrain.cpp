#include "Terrain.hpp"

#include "Renderer.hpp"

#include <algorithm>

namespace nu
{

Terrain::Terrain()
	: Node()
	, mMesh()
	, mShader()
	, mTexture(nullptr)
	, mSize(0)
	, mHeightScale(1.0f)
{
	std::string vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec3 vNormal;\n"
		"uniform mat4 MVP;\n"
		"uniform float heightScale;\n"
		"out float Color;\n"
		"void main()\n"
		"{\n"
		"Color = vPos.y / heightScale;\n"
		"gl_Position = MVP * vec4(vPos, 1.0);\n"
		"}";
	std::string fragmentShader = "#version 330 core\n"
		"in float Color;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(Color, Color, Color, 1.0);\n"
		"}";

	mShader.load(ShaderLoader::fromSource(vertexShader, fragmentShader));
}

void Terrain::setTexture(Texture::Ptr texture)
{
	mTexture = texture;
}

Texture::Ptr Terrain::getTexture()
{
	return mTexture;
}

F32 Terrain::getSize() const
{
	return mSize;
}

F32 Terrain::getHeightScale() const
{
	return mHeightScale;
}

U32 Terrain::getVertices() const
{
	return mMesh.getVertices();
}

U32 Terrain::getIndices() const
{
	return mMesh.getIndices();
}

bool Terrain::build(const nu::Image& image, F32 size, U32 verticesPerLine, F32 heightScale)
{
	if (!image.isLoaded())
	{
		return false;
	}

	printf("Size : %d %d\n", image.getSize().x, image.getSize().y);

	const F32 imgScaleX = (F32)(image.getSize().x) / (verticesPerLine - 1);
	const F32 imgScaleZ = (F32)(image.getSize().y) / (verticesPerLine - 1);

	std::vector<Vertex_XYZ_Normal> vertices;
	std::vector<U32> indices;

	const F32 delta = size / (verticesPerLine - 1);

	U32 a, b, c;
	U32 d = verticesPerLine - 1;
	for (U32 z = 0; z < verticesPerLine; z++)
	{
		for (U32 x = 0; x < verticesPerLine; x++)
		{
			// Height
			U32 imgX = (x != d) ? U32(imgScaleX * F32(x)) : image.getSize().x - 1;
			U32 imgZ = (z != d) ? U32(imgScaleZ * F32(z)) : image.getSize().y - 1;
			F32 y = image.getPixel(imgX, imgZ).r * heightScale * 0.00392156862f;

			// Vertex
			vertices.emplace_back(Vector3f(x * delta, y, z * delta), Vector3f::up);

			// Triangles
			if (x < d && z < d)
			{
				a = z * verticesPerLine + x;
				b = (z + 1) * verticesPerLine + x;
				c = a + 1;
				indices.emplace_back(a);
				indices.emplace_back(c);
				indices.emplace_back(b);
				indices.emplace_back(c);
				indices.emplace_back(b + 1);
				indices.emplace_back(b);
			}
		}
	}

	mMesh.set(vertices, indices);
	mSize = size;
	mHeightScale = heightScale;

	return true;
}

void Terrain::draw()
{
	mShader.bind();
	mShader.setUniform("heightScale", mHeightScale);
	mShader.setUniform("MVP", Renderer::instance().getCamera().getViewProjectionMatrix() * getGlobalTransform());

	if (mTexture != nullptr)
	{
		mTexture->bind();
	}

	mMesh.bind();
	mMesh.draw();
}

} // namespace nu