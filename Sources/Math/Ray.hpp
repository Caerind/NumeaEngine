#ifndef NU_RAY_HPP
#define NU_RAY_HPP

#include "Vector3.hpp"

namespace nu
{

class Ray
{
	public:
		Ray();
		Ray(const Vector3f& origin, const Vector3f& direction);

		void setOrigin(const Vector3f& origin);
		void setOrigin(F32 x, F32 y, F32 z);
		const Vector3f& getOrigin() const;

		void setDirection(const Vector3f& direction);
		void setDirection(F32 x, F32 y, F32 z);
		const Vector3f& getDirection() const;

		Vector3f getPoint(F32 t) const;
		Vector3f operator*(F32 t) const;

		bool contains(const Vector3f& point) const;

		bool operator==(const Ray& ray) const;
		bool operator!=(const Ray& ray) const;

	private:
		Vector3f mOrigin;
		Vector3f mDirection;
};

} // namespace nu

#endif // NU_RAY_HPP
