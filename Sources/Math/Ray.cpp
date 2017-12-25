#include "Ray.hpp"

namespace nu
{

Ray::Ray()
	: mOrigin(Vector3f::zero())
	, mDirection(Vector3f::zero())
{
}

Ray::Ray(const Vector3f& origin, const Vector3f& direction)
	: mOrigin(origin)
	, mDirection(direction)
{
}

void Ray::setOrigin(const Vector3f& origin)
{
	mOrigin = origin;
}

void Ray::setOrigin(F32 x, F32 y, F32 z)
{
	setOrigin(Vector3f(x, y, z));
}

const Vector3f& Ray::getOrigin() const
{
	return mOrigin;
}

void Ray::setDirection(const Vector3f& direction)
{
	mDirection = direction;
}

void Ray::setDirection(F32 x, F32 y, F32 z)
{
	setDirection(Vector3f(x, y, z));
}

const Vector3f& Ray::getDirection() const
{
	return mDirection;
}

Vector3f Ray::getPoint(F32 t) const
{
	return mOrigin + mDirection * t;
}

Vector3f Ray::operator*(F32 t) const
{
	return mOrigin + mDirection * t;
}

bool Ray::contains(const Vector3f& point) const
{
	if (mOrigin == point)
	{
		return true;
	}
	assert(mDirection.getSquaredLength() > 0.0f);
	Vector3f p = (point - mOrigin) / mDirection;
	return (p.x > 0.0f && (p.x, p.y) && equals(p.x, p.z));
}

bool Ray::operator==(const Ray& ray) const
{
	return mOrigin == ray.mOrigin && mDirection == ray.mDirection;
}

bool Ray::operator!=(const Ray& ray) const
{
	return !operator==(ray);
}

} // namespace nu
