#include "Sprite.hpp"

#include "Renderer.hpp"

namespace nu
{

Sprite::Sprite()
	: TransformBinder()
	, mVertices()
	, mSize(0.0f, 0.0f)
	, mUseNormals(false)
	, mNeedUpdate(false)
	, mTexture(nullptr)
{
}

void Sprite::setTexture(const Texture* texture)
{
	mTexture = texture;
}

const Texture* Sprite::getTexture() const
{
	return mTexture;
}

void Sprite::setSize(F32 x, F32 y)
{
	if (mSize.x != x && mSize.y != y)
	{
		mSize.set(x, y);
		mNeedUpdate = true;
	}
}

void Sprite::setSize(const Vector2f& size)
{
	if (size != mSize)
	{
		mSize.set(size);
		mNeedUpdate = true;
	}
}

const Vector2f& Sprite::getSize() const
{
	return mSize;
}

void Sprite::useNormals(bool use)
{
	if (use != mUseNormals)
	{
		mUseNormals = use;
		mNeedUpdate = true;
	}
}

bool Sprite::hasNormals() const
{
	return mUseNormals;
}

void Sprite::draw()
{
	if (mShader != nullptr)
	{
		mShader->bind();
		bindTransforms();
	}
	if (mTexture != nullptr)
	{
		mTexture->bind();
	}
	if (mNeedUpdate)
	{
		update();
	}
	if (mVertices.getVertices() >= 3)
	{
		mVertices.bind();
		mVertices.draw();
	}
}

void Sprite::update()
{
	if (mNeedUpdate)
	{
		if (mUseNormals)
		{
			std::vector<Vertex_XYZ_Normal_UV> vertices;
			vertices.emplace_back(Vector3f(0.0f, mSize.y, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 0.0f));
			vertices.emplace_back(Vector3f(mSize.x, mSize.y, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
			vertices.emplace_back(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
			vertices.emplace_back(Vector3f(mSize.x, mSize.y, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 0.0f));
			vertices.emplace_back(Vector3f(mSize.x, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(1.0f, 1.0f));
			vertices.emplace_back(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f), Vector2f(0.0f, 1.0f));
			mVertices.set(vertices);
		}
		else
		{
			std::vector<Vertex_XYZ_UV> vertices;
			vertices.emplace_back(Vector3f(0.0f, mSize.y, 0.0f), Vector2f(0.0f, 0.0f));
			vertices.emplace_back(Vector3f(mSize.x, mSize.y, 0.0f), Vector2f(1.0f, 0.0f));
			vertices.emplace_back(Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f));
			vertices.emplace_back(Vector3f(mSize.x, mSize.y, 0.0f), Vector2f(1.0f, 0.0f));
			vertices.emplace_back(Vector3f(mSize.x, 0.0f, 0.0f), Vector2f(1.0f, 1.0f));
			vertices.emplace_back(Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.0f, 1.0f));
			mVertices.set(vertices);
		}
		mNeedUpdate = false;
	}
}

} // namespace nu