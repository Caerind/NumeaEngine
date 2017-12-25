#ifndef NU_AABB_HPP
#define NU_AABB_HPP

#include "Vector3.hpp"
#include "Matrix4.hpp"

namespace nu 
{

class AABB
{
	public:
		AABB();
		AABB(const Vector3f& min, const Vector3f& max);
		AABB(F32 minX, F32 minY, F32 minZ, F32 maxX, F32 maxY, F32 maxZ);

		const Vector3f& getMinimum() const;
		void setMinimum(const Vector3f& minimum);
		void setMinimum(F32 x, F32 y, F32 z);

		const Vector3f& getMaximum() const;
		void setMaximum(const Vector3f& maximum);
		void setMaximum(F32 x, F32 y, F32 z);

		void setBox(const Vector3f& minimum, const Vector3f& maximum);
		void setBox(F32 minX, F32 minY, F32 minZ, F32 maxX, F32 maxY, F32 maxZ);
		void setCenteredBox(const Vector3f& center, const Vector3f& halfSize);
		void setCenteredBox(F32 cX, F32 cY, F32 cZ, F32 hsX, F32 hsY, F32 hsZ);

		void merge(const Vector3f& point);
		void merge(const AABB& box);

		void transform(const Matrix4f& m);

		Vector3f getCenter() const;
		Vector3f getSize() const;
		Vector3f getHalfSize() const;
		F32 getVolume() const;

		/*
		   1-------2
		  /|      /|
		 / |     / |
		6-------7  |
		|  0----|--3
		| /     | /
		|/      |/
		5-------4
		*/
		Vector3f getCorner(U8 index) const;

		F32 getDistanceSquared(const Vector3f& point) const;
		F32 getDistance(const Vector3f& point) const;

		bool contains(const Vector3f& point) const;

		bool operator==(const AABB& box) const;
		bool operator!=(const AABB& box) const;

	private:
		Vector3f mMin;
		Vector3f mMax;
};

} // namespace nu

#endif // NU_AABB_HPP
