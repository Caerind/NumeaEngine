#ifndef NU_RENDERER_HPP
#define NU_RENDERER_HPP

#include "../Application/GLEWWrapper.hpp"

#include "LinearColor.hpp"
#include "VertexDeclaration.hpp"
#include "VertexArray.hpp"
#include "Camera.hpp"
#include "DebugDraw.hpp"
#include "ShaderBank.hpp"
#include "RenderTarget.hpp"
//#include "RenderTexture.hpp"

namespace nu
{

enum class Primitive
{
	Triangles,
	Lines
};

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void reset();

		void enable(U32 flags);
		void disable(U32 flags);

		void drawArrays(Primitive mode, U32 vertices);
		void drawElements(Primitive mode, U32 vertices);

		void begin(const Color& clearColor = Color::Black);
		void end();

		bool setTarget(const RenderTarget* target);
		const RenderTarget* getTarget();

		U32 getCurrentVertexArray() const;
		U32 getCurrentVertexBuffer() const;
		U32 getCurrentIndexBuffer() const;
		U32 getCurrentShader() const;
		U32 getCurrentTexture() const;

		Camera& getCamera();
		DebugDraw& getDebug();
		ShaderBank& getShaders();

		static bool instantiated();
		static Renderer& instance();

	private:
		static GLenum convertPrimitive(Primitive mode);

	private:
		Camera mCamera;
		DebugDraw mDebug;
		ShaderBank mShaders;

		const RenderTarget* mTarget;

		static Renderer* sSingleton;
};

} // namespace nu

#endif // NU_RENDERER_HPP