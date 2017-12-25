#include "Plane.hpp"

namespace nu
{

Plane::Plane()
	: mNormal(0.0f)
	, mConstant(0.0f)
{
}

Plane::Plane(const Vector3f& normal, F32 constant)
	: mNormal(normal)
	, mConstant(-constant)
{
}

Plane::Plane(const Vector3f& normal, const Vector3f& point)
{
	redefine(normal, point);
}

Plane::Plane(F32 a, F32 b, F32 c, F32 d)
{
	redefine(a, b, c, d);
}

Plane::Plane(const Vector3f& point1, const Vector3f& point2, const Vector3f& point3)
{
	redefine(point1, point2, point3);
}

void Plane::redefine(const Vector3f& normal, F32 constant)
{
	mNormal.set(normal);
	mConstant = constant;
}

void Plane::redefine(const Vector3f& normal, const Vector3f& point)
{
	mNormal.set(normal);
	mConstant = -mNormal.dotProduct(point);
}

void Plane::redefine(F32 a, F32 b, F32 c, F32 d)
{
	mNormal.set(a, b, c);
	mConstant = d;
	normalize();
}

void Plane::redefine(const Vector3f& point1, const Vector3f& point2, const Vector3f& point3)
{
	Vector3f edge1 = point2 - point1;
	Vector3f edge2 = point3 - point1;
	mNormal.set(edge1.crossProduct(edge2).normalized());
	mConstant = -mNormal.dotProduct(point1);
}

const Vector3f& Plane::getNormal() const
{
	return mNormal;
}

void Plane::setNormal(const Vector3f& normal)
{
	mNormal.set(normal);
}

F32 Plane::getConstant() const
{
	return mConstant;
}

void Plane::setConstant(F32 constant)
{
	mConstant = constant;
}

F32 Plane::normalize()
{
	F32 length = mNormal.getLength();
	assert(length > 0.0f);
	F32 inv = 1.0f / length;
	mNormal *= inv;
	mConstant *= inv;
	return length;
}

F32 Plane::getDistance(const Vector3f& point) const
{
	return mNormal.dotProduct(point) + mConstant;
}

Plane::Side Plane::getSide(const Vector3f& point) const
{
	F32 distance = getDistance(point);
	if (distance > 0.0f)
	{
		return Plane::Positive;
	}
	if (distance < 0.0f)
	{
		return Plane::Negative;
	}
	return Plane::None;
}

bool Plane::contains(const Vector3f& point) const
{
	return equals(getDistance(point), 0.0f);
}

bool Plane::operator==(const Plane& p) const
{
	return Vector4f(mNormal, mConstant).normalized() == Vector4f(p.mNormal, p.mConstant).normalized();
}

bool Plane::operator!=(const Plane& p) const
{
	return !operator==(p);
}

} // namespace nu
