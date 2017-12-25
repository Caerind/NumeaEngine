#ifndef NU_PLANE_HPP
#define NU_PLANE_HPP

#include "Vector4.hpp"

namespace nu
{

class Plane
{
	public:
		Plane();
		Plane(const Vector3f& normal, F32 constant);
		Plane(const Vector3f& normal, const Vector3f& point);
		Plane(F32 a, F32 b, F32 c, F32 d);
		Plane(const Vector3f& point1, const Vector3f& point2, const Vector3f& point3);

		void redefine(const Vector3f& normal, F32 constant);
		void redefine(const Vector3f& normal, const Vector3f& point);
		void redefine(F32 a, F32 b, F32 c, F32 d);
		void redefine(const Vector3f& point1, const Vector3f& point2, const Vector3f& point3);

		const Vector3f& getNormal() const;
		void setNormal(const Vector3f& normal);

		F32 getConstant() const;
		void setConstant(F32 constant);

		F32 normalize();

		F32 getDistance(const Vector3f& point) const;

		enum Side : U8
		{
			None,
			Positive,
			Negative,
			Both
		};
		Side getSide(const Vector3f& point) const;

		bool contains(const Vector3f& point) const;

		bool operator==(const Plane& p) const;
		bool operator!=(const Plane& p) const;

	private:
		Vector3f mNormal;
		F32 mConstant;
};

} // namespace nu

#endif // NU_PLANE_HPP
