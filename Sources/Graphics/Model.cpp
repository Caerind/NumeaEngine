#include "Model.hpp"

#include "Renderer.hpp"

namespace nu
{

Model::Model()
	: TransformBinder()
	, mTexture(nullptr)
	, mMesh(nullptr)
{
	clearUniformBindings();
}

void Model::setTexture(const Texture* texture)
{
	mTexture = texture;
}

void Model::setMesh(const Mesh* mesh)
{
	mMesh = mesh;
}

const Texture* Model::getTexture() const
{
	return mTexture;
}

const Mesh* Model::getMesh() const
{
	return mMesh;
}

void Model::draw()
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
	if (mMesh != nullptr)
	{
		mMesh->bind();
		mMesh->draw();
	}
}

} // namespace nu