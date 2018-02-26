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

void Model::setTexture(Texture::Ptr texture)
{
	mTexture = texture;
}

void Model::setMesh(Mesh::Ptr mesh)
{
	mMesh = mesh;
}

Texture::Ptr Model::getTexture()
{
	return mTexture;
}

Mesh::Ptr Model::getMesh()
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