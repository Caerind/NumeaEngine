#ifndef NU_RENDERTEXTURE_HPP
#define NU_RENDERTEXTURE_HPP

#include "RenderTarget.hpp"
#include "RenderBuffer.hpp"
#include "Texture.hpp"

namespace nu
{

class RenderTexture : public RenderTarget
{
	friend class Renderer;

	public:
		RenderTexture();
		NU_NON_COPYABLE(RenderTexture);
		virtual ~RenderTexture();

		bool create(U32 width, U32 height);
		void destroy();

		virtual Vector2u getSize() const;

		bool isValid() const;
		U32 getOpenGLId() const;

		virtual bool hasContext() const;

		const Texture* getTexture() const;

	// TODO : Temp
	//protected:
		virtual bool activate() const;
		virtual void deactivate() const;

		// TODO : Temp
		void toWindow(U32 w, U32 h, U32 attachment);

	private:
		Vector2u mSize;
		U32 mFBO;
		Texture mTexture;
		RenderBuffer mDepthBuffer;
		mutable int mPrevViewport[4];
};

} // namespace nu

#endif // NU_RENDERTEXTURE_HPP