#include "TransformBinder.hpp"

#include "Renderer.hpp"

namespace nu
{

TransformBinder::TransformBinder()
	: mBindings()
	, mShader(nullptr)
{
	clearUniformBindings();
}

void TransformBinder::setShader(Shader* shader)
{
	mShader = shader;
	clearUniformBindings();
}

Shader* TransformBinder::getShader()
{
	return mShader;
}

void TransformBinder::setUniformBinding(TransformBindingUniform binding, const std::string& uniform)
{
	mBindings[binding] = uniform;
}

void TransformBinder::clearUniformBindings()
{
	for (U32 i = 0; i < TransformBindingUniform::Count; i++)
	{
		mBindings[(TransformBindingUniform)i].clear();
	}
}

void TransformBinder::bindTransforms()
{
	const Matrix4f& m = getGlobalTransform();
	const Matrix4f mv = Renderer::instance().getCamera().getViewMatrix() * m;
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
		const Matrix4f mvp = Renderer::instance().getCamera().getProjectionMatrix() * mv;
		mShader->setUniform(mBindings[ModelViewProjectionMatrix], mvp);
	}
	if (mBindings[ViewProjectionMatrix].size() > 0)
	{
		const Matrix4f vp = Renderer::instance().getCamera().getProjectionMatrix() * Renderer::instance().getCamera().getViewMatrix();
		mShader->setUniform(mBindings[ViewProjectionMatrix], mv);
	}
	if (mBindings[NormalMatrix].size() > 0)
	{
		mShader->setUniform(mBindings[NormalMatrix], n);
	}
}

} // namespace nu