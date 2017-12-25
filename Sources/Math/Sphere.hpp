#ifndef NU_SPHERE_HPP
#define NU_SPHERE_HPP

#include "Vector3.hpp"

namespace nu 
{

class Sphere
{
	public:
		Sphere();
		Sphere(const Vector3f& center, F32 radius = 1.f);
		Sphere(F32 radius, const Vector3f& center = Vector3f::zero());
		
		const Vector3f& getCenter() const;
		void setCenter(const Vector3f& center);

		F32 getRadius() const;
		void setRadius(F32 radius);

		bool contains(const Vector3f& point) const;

		bool operator==(const Sphere& p) const;
		bool operator!=(const Sphere& p) const;
		
	private:
		Vector3f mCenter;
		F32 mRadius;
};

} // namespace nu

#endif // NU_SPHERE_HPP
