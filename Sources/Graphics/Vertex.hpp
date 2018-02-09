#ifndef NU_VERTEX_HPP
#define NU_VERTEX_HPP

#include "../Math/Vector3.hpp"
#include "Color.hpp"

namespace nu
{

enum VertexStruct : U32
{
	VertexStruct_XY = 0,
	VertexStruct_XY_Color,
	VertexStruct_XY_UV,
	VertexStruct_XY_Color_UV,
	VertexStruct_XYZ,
	VertexStruct_XYZ_Color,
	VertexStruct_XYZ_Color_UV,
	VertexStruct_XYZ_Normal,
	VertexStruct_XYZ_Normal_UV,
	VertexStruct_XYZ_Normal_UV_Tangent,
	VertexStruct_XYZ_UV,

	VertexStruct_Count
};

// 2D

struct Vertex_XY
{
	Vertex_XY() : position(Vector2f::zero) {}
	Vertex_XY(const Vector2f& p) : position(p) {}

	Vector2f position;

	static const VertexStruct type = VertexStruct_XY;
};

struct Vertex_XY_Color
{
	Vertex_XY_Color() : position(Vector2f::zero), color(Color::Black) {}
	Vertex_XY_Color(const Vector2f& p, const Color& c) : position(p), color(c) {}

	Vector2f position;
	Color color;

	static const VertexStruct type = VertexStruct_XY_Color;
};

struct Vertex_XY_UV
{
	Vertex_XY_UV() : position(Vector2f::zero), uv(Vector2f::zero) {}
	Vertex_XY_UV(const Vector2f& p, const Vector2f& u) : position(p), uv(u) {}

	Vector2f position;
	Vector2f uv;

	static const VertexStruct type = VertexStruct_XY_UV;
};

struct Vertex_XY_Color_UV
{
	Vertex_XY_Color_UV() : position(Vector2f::zero), color(Color::Black), uv(Vector2f()) {}
	Vertex_XY_Color_UV(const Vector2f& p, const Color& c, const Vector2f& u) : position(p), color(c), uv(u) {}

	Vector2f position;
	Color color;
	Vector2f uv;

	static const VertexStruct type = VertexStruct_XY_Color_UV;
};



// 3D

struct Vertex_XYZ
{
	Vertex_XYZ() : position(Vector3f::zero) {}
	Vertex_XYZ(const Vector3f& p) : position(p) {}

	Vector3f position;

	static const VertexStruct type = VertexStruct_XYZ;
};

struct Vertex_XYZ_Color
{
	Vertex_XYZ_Color() : position(Vector3f::zero), color(Color::Black) {}
	Vertex_XYZ_Color(const Vector3f& p, const Color& c) : position(p), color(c) {}

	Vector3f position;
	Color color;

	static const VertexStruct type = VertexStruct_XYZ_Color;
};

struct Vertex_XYZ_Color_UV
{
	Vertex_XYZ_Color_UV() : position(Vector3f::zero), color(Color::Black), uv(Vector2f::zero) {}
	Vertex_XYZ_Color_UV(const Vector3f& p, const Color& c, const Vector2f& u) : position(p), color(c), uv(u) {}

	Vector3f position;
	Color color;
	Vector2f uv;

	static const VertexStruct type = VertexStruct_XYZ_Color_UV;
};

struct Vertex_XYZ_Normal
{
	Vertex_XYZ_Normal() : position(Vector3f::zero), normal(Vector3f::zero) {}
	Vertex_XYZ_Normal(const Vector3f& p, const Vector3f& n) : position(p), normal(n) {}

	Vector3f position;
	Vector3f normal;

	static const VertexStruct type = VertexStruct_XYZ_Normal;
};

struct Vertex_XYZ_Normal_UV
{
	Vertex_XYZ_Normal_UV() : position(Vector3f::zero), normal(Vector3f::zero), uv(Vector2f::zero) {}
	Vertex_XYZ_Normal_UV(const Vector3f& p, const Vector3f& n, const Vector2f& u) : position(p), normal(n), uv(u) {}

	Vector3f position;
	Vector3f normal;
	Vector2f uv;

	static const VertexStruct type = VertexStruct_XYZ_Normal_UV;
};

struct Vertex_XYZ_Normal_UV_Tangent
{
	Vertex_XYZ_Normal_UV_Tangent() : position(Vector3f::zero), normal(Vector3f::zero), uv(Vector2f::zero), tangent(Vector3f::zero) {}
	Vertex_XYZ_Normal_UV_Tangent(const Vector3f& p, const Vector3f& n, const Vector2f& u, const Vector3f& t) : position(p), normal(n), uv(u), tangent(t) {}

	Vector3f position;
	Vector3f normal;
	Vector2f uv;
	Vector3f tangent;

	static const VertexStruct type = VertexStruct_XYZ_Normal_UV_Tangent;
};

struct Vertex_XYZ_UV
{
	Vertex_XYZ_UV() : position(Vector3f::zero), uv(Vector2f::zero) {}
	Vertex_XYZ_UV(const Vector3f& p, const Vector2f& u) : position(p), uv(u) {}

	Vector3f position;
	Vector2f uv;

	static const VertexStruct type = VertexStruct_XYZ_UV;
};

} // namespace nu

#endif // NU_VERTEX_HPP