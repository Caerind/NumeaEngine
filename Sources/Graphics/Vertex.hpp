#ifndef NU_VERTEX_HPP
#define NU_VERTEX_HPP

#include "../Math/Vector3.hpp"
#include "Color.hpp"

namespace nu
{

// 2D

struct Vertex_XY
{
	Vector2f position;
};

struct Vertex_XY_Color
{
	Vector2f position;
	Color color;
};

struct Vertex_XY_UV
{
	Vector2f position;
	Vector2f uv;
};

struct Vertex_XY_Color_UV
{
	Vector2f position;
	Color color;
	Vector2f uv;
};



// 3D

struct Vertex_XYZ
{
	Vector3f position;
};

struct Vertex_XYZ_Color
{
	Vector3f position;
	Color color;
};

struct Vertex_XYZ_Color_UV
{
	Vector3f position;
	Color color;
	Vector2f uv;
};

struct Vertex_XYZ_Normal
{
	Vector3f position;
	Vector3f normal;
};

struct Vertex_XYZ_Normal_UV
{
	Vector3f position;
	Vector3f normal;
	Vector2f uv;
};

struct Vertex_XYZ_Normal_UV_Tangent
{
	Vector3f position;
	Vector3f normal;
	Vector2f uv;
	Vector3f tangent;
};

struct Vertex_XYZ_UV
{
	Vector3f position;
	Vector2f uv;
};

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

} // namespace nu

#endif // NU_VERTEX_HPP