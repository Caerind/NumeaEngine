#include "Renderer.hpp"

namespace nu
{

Renderer::Renderer()
	: mVertexArray(0)
	, mCamera()
{
	VertexDeclaration::initialize();

	glGenVertexArrays(1, &mVertexArray);

	reset();
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &mVertexArray);
}

void Renderer::reset()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::enable(U32 flags)
{
	glEnable(flags);
}

void Renderer::disable(U32 flags)
{
	glDisable(flags);
}

void Renderer::draw()
{
}

void Renderer::begin(const Color& clearColor)
{
	LinearColor color(clearColor);
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::end()
{
}

Camera& Renderer::getCamera()
{
	return mCamera;
}

} // namespace nu