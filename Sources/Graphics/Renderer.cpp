#include "Renderer.hpp"

namespace nu
{

Renderer* Renderer::sSingleton = nullptr;

Renderer::Renderer()
	: mCamera()
{
	nu::VertexDeclaration::initialize();
	printf("An error message is displayed because there is a VertexBuffer in DebugDraw which comes before the initialization\n");

	sSingleton = this;

	reset();
}

Renderer::~Renderer()
{
}

void Renderer::reset()
{
	glCheck(glEnable(GL_DEPTH_TEST));
	glCheck(glDepthFunc(GL_LESS));
}

void Renderer::enable(U32 flags)
{
	glCheck(glEnable(flags));
}

void Renderer::disable(U32 flags)
{
	glCheck(glDisable(flags));
}

void Renderer::drawArrays(Primitive mode, U32 vertices)
{
	glCheck(glDrawArrays(convertPrimitive(mode), 0, vertices));
}

void Renderer::drawElements(Primitive mode, U32 vertices)
{
	glCheck(glDrawElements(convertPrimitive(mode), vertices, GL_UNSIGNED_INT, 0));
}

void Renderer::begin(const Color& clearColor)
{
	LinearColor color(clearColor);
	glCheck(glClearColor(color.r, color.g, color.b, color.a));
	glCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::end()
{
	mDebug.render(mCamera.getViewMatrix(), mCamera.getProjectionMatrix());
}

// TODO : RT
/*
bool Renderer::setTarget(const RenderTarget* target)
{
	if (mTarget == target)
	{
		return true;
	}

	if (mTarget)
	{
		if (!mTarget->hasContext())
		{
			mTarget->deactivate();
		}
		mTarget = nullptr;
	}

	if (target)
	{
		if (!target->activate())
		{
			LogError(nu::LogChannel::Graphics, 6, "Renderer : Failed to activate target\n");
			return false;
		}
		mTarget = target;
	}

	// TODO : Update Scissor & Viewport if needed

	return true;
}

const RenderTarget* Renderer::getTarget()
{
	return mTarget;
}
*/

U32 Renderer::getCurrentVertexArray() const
{
	int id;
	glCheck(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &id));
	return U32(id);
}

U32 Renderer::getCurrentVertexBuffer() const
{
	int id;
	glCheck(glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &id));
	return U32(id);
}

U32 Renderer::getCurrentIndexBuffer() const
{
	int id;
	glCheck(glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id));
	return U32(id);
}

U32 Renderer::getCurrentShader() const
{
	int id;
	glCheck(glGetIntegerv(GL_CURRENT_PROGRAM, &id));
	return U32(id);
}

U32 Renderer::getCurrentTexture() const
{
	int id;
	glCheck(glGetIntegerv(GL_TEXTURE_BINDING_2D, &id));
	return U32(id);
}

Camera& Renderer::getCamera()
{
	return mCamera;
}

DebugDraw& Renderer::getDebug()
{
	return mDebug;
}

ShaderBank& Renderer::getShaders()
{
	return mShaders;
}

bool Renderer::instantiated()
{
	return sSingleton != nullptr;
}

Renderer& Renderer::instance()
{
	assert(sSingleton != nullptr);
	return *sSingleton;
}

GLenum Renderer::convertPrimitive(Primitive mode)
{
	switch (mode)
	{
		case Primitive::Triangles: return GL_TRIANGLES; break;
		case Primitive::Lines: return GL_LINES; break;
	}
	return GL_TRIANGLES;
}

} // namespace nu