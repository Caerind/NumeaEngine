#ifndef NU_RENDERSTATE_HPP
#define NU_RENDERSTATE_HPP

#include "../Application/GLEWWrapper.hpp"

#include "../Math/Matrix4.hpp"

namespace nu
{

struct RenderState
{
	nu::Matrix4f modelMatrix;

	U32 shader;
	U32 texture;
	U32 vao;
	U32 vbo;
	U32 ibo;

	U32 vertices;
};

} // namespace nu

#endif // NU_RENDERSTATE_HPP