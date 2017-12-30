#include "Renderer.hpp"

namespace nu
{

Renderer* Renderer::sSingleton = nullptr;

Renderer::Renderer()
	: mCamera()
{
	nu::VertexDeclaration::initialize();
	nu::VertexArray::initialize();

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
}

Camera& Renderer::getCamera()
{
	return mCamera;
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