#include "Frustum.hpp"

namespace nu
{

Frustum::Frustum()
{
}

Frustum::Frustum(F32 fov, F32 ratio, F32 zNear, F32 zFar, const Vector3f& eye, const Vector3f& target, const Vector3f& up, const F32 handedness)
{
	build(fov, ratio, zNear, zFar, eye, target, up, handedness);
}

void Frustum::build(F32 fov, F32 ratio, F32 zNear, F32 zFar, const Vector3f& eye, const Vector3f& target, const Vector3f& up, const F32 handedness)
{
	fov *= 0.5f;
	F32 tangent = nu::tan(fov);
	F32 nearH = zNear * tangent;
	F32 nearW = nearH * ratio;
	F32 farH = zFar * tangent;
	F32 farW = farH * ratio;

	Vector3f f((target - eye).normalized());
	Vector3f s(up.crossProduct(f).normalized());
	Vector3f u(f.crossProduct(s));
	const F32 neg = -handedness;
	f *= neg;
	s *= neg;

	Vector3f nc = eye + f * zNear;
	Vector3f fc = eye + f * zFar;

	// Computing the frustum
	Vector3f corners[8];
	corners[0] = fc - u * farH - s * farW; // FarLeftBottom
	corners[1] = fc + u * farH - s * farW; // FarLeftTop
	corners[2] = fc + u * farH + s * farW; // FarRightTop
	corners[3] = fc - u * farH + s * farW; // FarRightBottom
	corners[4] = nc - u * nearH - s * nearW; // NearLeftBottom
	corners[5] = nc + u * nearH - s * nearW; // NearLeftTop
	corners[6] = nc + u * nearH + s * nearW; // NearRightTop
	corners[7] = nc - u * nearH + s * nearW; // NearRightBottom

	// Construction of frustum's planes
	mPlanes[0].redefine(corners[4], corners[7], corners[3]); // Bottom
	mPlanes[1].redefine(corners[2], corners[1], corners[0]); // Far
	mPlanes[2].redefine(corners[5], corners[4], corners[0]); // Left
	mPlanes[3].redefine(corners[5], corners[6], corners[7]); // Near
	mPlanes[4].redefine(corners[7], corners[6], corners[3]); // Right 
	mPlanes[5].redefine(corners[6], corners[5], corners[1]); // Top
}

bool Frustum::contains(const Vector3f& point) const
{
	for (U8 i = 0; i < 6; i++)
	{
		if (mPlanes[i].getSide(point) == Plane::Side::Negative)
		{
			return false;
		}
	}
	return true;
}

const Plane& Frustum::getPlane(U8 index) const
{
	return mPlanes[index];
}

} // namespace nu
