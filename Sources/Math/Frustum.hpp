#ifndef NU_FRUSTUM_HPP
#define NU_FRUSTUM_HPP

#include "Plane.hpp"

namespace nu 
{

class Frustum
{
	public:
		Frustum();
		Frustum(F32 fov, F32 ratio, F32 zNear, F32 zFar, const Vector3f& eye, const Vector3f& target, const Vector3f& up = Vector3f::up, const F32 handedness = -1.0f);

		void build(F32 fov, F32 ratio, F32 zNear, F32 zFar, const Vector3f& eye, const Vector3f& target, const Vector3f& up = Vector3f::up, const F32 handedness = -1.0f);

		bool contains(const Vector3f& point) const;

		const Plane& getPlane(U8 index) const;

	private:
		Plane mPlanes[6];
};

} // namespace nu

#endif // NU_FRUSTUM_HPP
