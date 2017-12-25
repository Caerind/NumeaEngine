#include "Sphere.hpp"

namespace nu
{

Sphere::Sphere()
	: mCenter()
	, mRadius(1.0f)
{
}

Sphere::Sphere(const Vector3f& center, F32 radius)
	: mCenter(center)
	, mRadius(radius)
{
}

Sphere::Sphere(F32 radius, const Vector3f& center)
	: mCenter(center)
	, mRadius(radius)
{
}

const Vector3f& Sphere::getCenter() const
{
	return mCenter;
}

void Sphere::setCenter(const Vector3f& center)
{
	mCenter.set(center);
}

F32 Sphere::getRadius() const
{
	return mRadius;
}

void Sphere::setRadius(F32 radius)
{
	mRadius = radius;
}

bool Sphere::contains(const Vector3f& point) const
{
	return (point - mCenter).getSquaredLength() <= mRadius * mRadius;
}

bool Sphere::operator==(const Sphere& p) const
{
	return mCenter == p.mCenter && equals(mRadius, p.mRadius);
}

bool Sphere::operator!=(const Sphere& p) const
{
	return !operator==(p);
}

} // namespace nu
