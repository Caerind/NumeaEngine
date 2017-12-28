#ifndef NU_RENDERER_HPP
#define NU_RENDERER_HPP

#include "../Application/GLEWWrapper.hpp"

#include "LinearColor.hpp"
#include "VertexDeclaration.hpp"
#include "Camera.hpp"

namespace nu
{

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void reset();

		void enable(U32 flags);
		void disable(U32 flags);

		void draw();

		void begin(const Color& clearColor = Color::Black);
		void end();

		Camera& getCamera();

	private:
		U32 mVertexArray;
		Camera mCamera;
};

} // namespace nu

#endif // NU_RENDERER_HPP