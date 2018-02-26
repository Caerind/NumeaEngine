#include "Model.hpp"

#include "Renderer.hpp"

namespace nu
{

Model::Model()
{
	clearUniformBindings();
}

void Model::setShader(Shader::Ptr shader)
{
	mShader = shader;
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

Shader::Ptr Model::getShader()
{
	return mShader;
}

Texture::Ptr Model::getTexture()
{
	return mTexture;
}

Mesh::Ptr Model::getMesh()
{
	return mMesh;
}

void Model::setUniformBinding(TransformBindingUniform binding, const std::string& uniform)
{
	mBindings[binding] = uniform;
}

void Model::clearUniformBindings()
{
	for (U32 i = 0; i < TransformBindingUniform::Count; i++)
	{
		mBindings[(TransformBindingUniform)i].clear();
	}
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

void Model::bindTransforms()
{
	const Matrix4f& m = getGlobalTransform();
	const Matrix4f mv = Renderer::instance().getCamera().getViewMatrix() * m;
	const Matrix4f mvp = Renderer::instance().getCamera().getProjectionMatrix() * mv;
	const Matrix3f n = mv.toMatrix3();

	if (mBindings[ModelMatrix].size() > 0)
	{
		mShader->setUniform(mBindings[ModelMatrix], m);
	}
	if (mBindings[ModelViewMatrix].size() > 0)
	{
		mShader->setUniform(mBindings[ModelViewMatrix], mv);
	}
	if (mBindings[ModelViewProjectionMatrix].size() > 0)
	{
		mShader->setUniform(mBindings[ModelViewProjectionMatrix], mvp);
	}
	if (mBindings[NormalMatrix].size() > 0)
	{
		mShader->setUniform(mBindings[NormalMatrix], n);
	}
}

} // namespace nu