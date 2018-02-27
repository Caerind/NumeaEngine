#include "RenderTarget.hpp"

#include "Renderer.hpp"

namespace nu
{

RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
}

bool RenderTarget::setActive(bool active)
{
	if (active)
	{
		return Renderer::instance().setTarget(this);
	}
	else if (isActive())
	{
		return Renderer::instance().setTarget(nullptr);
	}
	return true;
}

bool RenderTarget::isActive() const
{
	return Renderer::instance().getTarget() == this;
}

void RenderTarget::deactivate() const
{
	// Only RenderTarget without context need to deactivate (RenderTexture)
}

} // namespace nu