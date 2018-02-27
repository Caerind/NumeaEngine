#ifndef NU_RENDERTARGET_HPP
#define NU_RENDERTARGET_HPP

#include "../Math/Vector2.hpp"

namespace nu
{

struct RenderTargetParameters
{
	RenderTargetParameters(U8 antialiasing = 0, U8 depth = 24, U8 stencil = 0) 
		: antialiasingLevel(antialiasing)
		, depthBits(depth)
		, stencilBits(stencil)
	{
	}

	U8 antialiasingLevel;
	U8 depthBits;
	U8 stencilBits;
};

class RenderTarget
{
	friend class Renderer;

	public:
		RenderTarget();
		NU_NON_COPYABLE(RenderTarget);
		virtual ~RenderTarget();

		virtual Vector2u getSize() const = 0;

		bool setActive(bool active);
		bool isActive() const;

		virtual bool hasContext() const = 0;

	protected:
		virtual bool activate() const = 0;
		virtual void deactivate() const;
};

} // namespace nu

#endif // NU_RENDERTARGET_HPP