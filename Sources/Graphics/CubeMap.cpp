#include "CubeMap.hpp"

#include "Image.hpp"
#include "Renderer.hpp"

namespace nu
{

CubeMap::CubeMap()
{
	std::string vertexShader = "#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"uniform mat4 MVP;\n"
		"out vec3 TexCoords;\n"
		"void main()\n"
		"{\n"
		"TexCoords = vPos;\n"
		"gl_Position = MVP * vec4(vPos, 1.0);\n"
		"}";

	std::string fragmentShader = "#version 330 core\n"
		"in vec3 TexCoords;\n"
		"uniform samplerCube Texture;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = texture(Texture, TexCoords);\n"
		"}";

	mShader.load(ShaderLoader::fromSource(vertexShader, fragmentShader));

	mSize = 0.0f;
	setSize(10.0f);
}

void CubeMap::setSize(F32 size)
{
	if (mSize != size)
	{
		mSize = size;

		std::vector<Vertex_XYZ> vertices = {
			Vertex_XYZ(-1.0f,  1.0f, -1.0f),
			Vertex_XYZ(-1.0f, -1.0f, -1.0f),
			Vertex_XYZ(1.0f, -1.0f, -1.0f),
			Vertex_XYZ(1.0f, -1.0f, -1.0f),
			Vertex_XYZ(1.0f,  1.0f, -1.0f),
			Vertex_XYZ(-1.0f,  1.0f, -1.0f),

			Vertex_XYZ(-1.0f, -1.0f,  1.0f),
			Vertex_XYZ(-1.0f, -1.0f, -1.0f),
			Vertex_XYZ(-1.0f,  1.0f, -1.0f),
			Vertex_XYZ(-1.0f,  1.0f, -1.0f),
			Vertex_XYZ(-1.0f,  1.0f,  1.0f),
			Vertex_XYZ(-1.0f, -1.0f,  1.0f),

			Vertex_XYZ(1.0f, -1.0f, -1.0f),
			Vertex_XYZ(1.0f, -1.0f,  1.0f),
			Vertex_XYZ(1.0f,  1.0f,  1.0f),
			Vertex_XYZ(1.0f,  1.0f,  1.0f),
			Vertex_XYZ(1.0f,  1.0f, -1.0f),
			Vertex_XYZ(1.0f, -1.0f, -1.0f),

			Vertex_XYZ(-1.0f, -1.0f,  1.0f),
			Vertex_XYZ(-1.0f,  1.0f,  1.0f),
			Vertex_XYZ(1.0f,  1.0f,  1.0f),
			Vertex_XYZ(1.0f,  1.0f,  1.0f),
			Vertex_XYZ(1.0f, -1.0f,  1.0f),
			Vertex_XYZ(-1.0f, -1.0f,  1.0f),

			Vertex_XYZ(-1.0f,  1.0f, -1.0f),
			Vertex_XYZ(1.0f,  1.0f, -1.0f),
			Vertex_XYZ(1.0f,  1.0f,  1.0f),
			Vertex_XYZ(1.0f,  1.0f,  1.0f),
			Vertex_XYZ(-1.0f,  1.0f,  1.0f),
			Vertex_XYZ(-1.0f,  1.0f, -1.0f),

			Vertex_XYZ(-1.0f, -1.0f, -1.0f),
			Vertex_XYZ(-1.0f, -1.0f,  1.0f),
			Vertex_XYZ(1.0f, -1.0f, -1.0f),
			Vertex_XYZ(1.0f, -1.0f, -1.0f),
			Vertex_XYZ(-1.0f, -1.0f,  1.0f),
			Vertex_XYZ(1.0f, -1.0f,  1.0f)
		};
		for (U32 i = 0; i < vertices.size(); i++)
		{
			vertices[i].position *= mSize;
		}

		mVertices.set(vertices);
	}
}

F32 CubeMap::getSize() const
{
	return mSize;
}

bool CubeMap::loadTexture(const std::vector<TextureSide>& sides)
{
	glCheck(glActiveTexture(GL_TEXTURE0));
	glCheck(glGenTextures(1, &mTexture));
	glCheck(glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture));

	for (const TextureSide& side : sides)
	{
		if (!loadSide(side.s, side.filename))
		{
			return false;
		}
	}

	glCheck(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glCheck(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glCheck(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	glCheck(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glCheck(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	return true;
}

bool CubeMap::loadSide(Side side, const std::string& filename)
{
	Image image;
	if (!image.load(ImageLoader::fromFile(filename)))
	{
		return false;
	}

	glCheck(glTexImage2D(convertSide(side), 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixels()));

	return true;
}

void CubeMap::draw()
{
	glCheck(glDepthMask(GL_FALSE));

	mShader.bind();
	mShader.setUniform("MVP", Renderer::instance().getCamera().getViewProjectionMatrix() * Matrix4f::translation(Renderer::instance().getCamera().getPosition()));

	glCheck(glActiveTexture(GL_TEXTURE0));
	glCheck(glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture));

	mVertices.bind();
	mVertices.draw();

	glCheck(glDepthMask(GL_TRUE));
}

GLenum CubeMap::convertSide(Side side)
{
	switch (side)
	{
		case Side::NegZ: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
		case Side::PosZ: return GL_TEXTURE_CUBE_MAP_POSITIVE_Z; break;
		case Side::NegY: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
		case Side::PosY: return GL_TEXTURE_CUBE_MAP_POSITIVE_Y; break;
		case Side::NegX: return GL_TEXTURE_CUBE_MAP_NEGATIVE_X; break;
		case Side::PosX: return GL_TEXTURE_CUBE_MAP_POSITIVE_X; break;
	}
	return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
}

} // namespace nu