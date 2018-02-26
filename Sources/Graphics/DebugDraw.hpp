#ifndef NU_DEBUGDRAW_HPP
#define NU_DEBUGDRAW_HPP

#include "VertexBuffer.hpp"
#include "Shader.hpp"
#include "LinearColor.hpp"
#include "../Math/Matrix4.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Frustum.hpp"

namespace nu
{

class DebugDraw
{
	public:
		DebugDraw();
		~DebugDraw();

		void line(const Vector3f& p1, const Vector3f& p2, const LinearColor& color = LinearColor::LightGray);
		void box(const Vector3f& boxCenter, const Vector3f& boxHalfSize, const LinearColor& color = LinearColor::LightGray);
		void aabb(const Vector3f& p1, const Vector3f& p2, const LinearColor& color = LinearColor::LightGray);
		void cross(const Vector3f& center);
		void transform(const Matrix4f& transform);
		void transform(const Quaternionf& transform);
		void point(const Vector3f& p, const LinearColor& color = LinearColor::LightGray);
		void xzGrid(F32 begin, F32 end, F32 y, F32 interval, const LinearColor& color = LinearColor::LightGray);
		void sphere(const Vector3f& center, F32 radius, const LinearColor& color = LinearColor::LightGray);
		void circle(const Vector3f& center, const Vector3f& normal, F32 radius, const LinearColor& color = LinearColor::LightGray);
		void cone(const Vector3f& origin, const Vector3f& dir, F32 length, F32 radius, const LinearColor& color = LinearColor::LightGray);
		void frustum(const Frustum& frustum, const LinearColor& color = LinearColor::LightGray);

		void render(const Matrix4f& viewMatrix, const Matrix4f& projectionMatrix);

		static bool instantiated();
		static DebugDraw& instance();

	private:
		void addVertex(F32 x, F32 y, F32 z, const LinearColor& c);
		void addVertex(const Vector3f& p, const LinearColor& c);

	private:
		std::vector<Vertex_XYZ_Color> mVertices;
		VertexBuffer mVBO;
		Shader mShader;

		static DebugDraw* sSingleton;
};

} // namespace nu

#endif // NU_DEBUGDRAW_HPP