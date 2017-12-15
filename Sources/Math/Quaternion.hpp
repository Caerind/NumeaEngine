#ifndef NU_QUATERNION_HPP
#define NU_QUATERNION_HPP

#include "Vector4.hpp"

namespace nu
{

template <typename T>
class Quaternion
{
	public:
		inline Quaternion();
		inline Quaternion(const Quaternion<T>& q);
		template <typename U>
		explicit inline Quaternion(const Quaternion<U>& q);
		explicit inline Quaternion(const T* a);
		explicit inline Quaternion(const Vector4<T>& v);
		inline Quaternion(const T& x, const T& y, const T& z, const T& w);
		inline Quaternion(const Vector3<T>& v, const T& s);
		inline Quaternion(const Vector3<T>& eulerAngles);
		inline Quaternion(const T& pitch, const T& yaw, const T& roll);
		inline Quaternion(const T& angle, const Vector3<T>& axis);
		~Quaternion() = default;

		inline Quaternion<T>& set(const Quaternion<T>& q);
		template <typename U>
		inline Quaternion<T>& set(const Quaternion<U>& q);
		inline Quaternion<T>& set(const T* a);
		inline Quaternion<T>& set(const Vector4<T>& v);
		inline Quaternion<T>& set(const T& x, const T& y, const T& z, const T& w);
		inline Quaternion<T>& set(const Vector3<T>& v, const T& s);
		inline Quaternion<T>& set(const Vector3<T>& eulerAngles);
		inline Quaternion<T>& set(const T& pitch, const T& yaw, const T& roll);
		inline Quaternion<T>& set(const T& angle, const Vector3<T>& axis);

		inline T& operator()(U32 i);
		inline const T& operator()(U32 i) const;
		inline T& operator[](U32 i);
		inline const T& operator[](U32 i) const;

		inline Quaternion<T>& operator=(const Quaternion<T>& q);

		inline Quaternion<T> operator*(const Quaternion<T>& q) const;
		inline Quaternion<T>& operator*=(const Quaternion<T>& q);

		inline bool operator==(const Quaternion<T>& q) const;
		inline bool operator!=(const Quaternion<T>& q) const;

		inline Quaternion<T>& conjugate();
		inline Quaternion<T> conjugated();

		inline Quaternion<T>& inverse();
		inline Quaternion<T> inversed();

		inline Vector3<T>& rotate(Vector3<T>& vector) const;
		inline Vector3<T> rotated(const Vector3<T>& vector) const;

		inline T dotProduct(const Quaternion<T>& q) const;
		inline T getSquaredLength() const;
		inline T getLength() const;
		inline Quaternion<T>& normalize(T* oldLength = nullptr);
		inline Quaternion<T>& ensureNormalized();

		void toEulerAngles(Vector3<T>& vector) const;
		void toAngleAxis(T& angle, Vector3<T>& axis) const;
		//void toMatrix3(Matrix3<T>& matrix) const;

		static inline Quaternion<T> lerp(const Quaternion<T>& start, const Quaternion<T>& end, const T& percent);
		static inline Quaternion<T> slerp(const Quaternion<T>& start, const Quaternion<T>& end, const T& percent);

		inline Quaternion<T>& makeIdentity();

		static Quaternion<T> identity();

		#include "DisableAnonymousStructBegin.hpp"
		union
		{
			T data[4];
			struct
			{
				Vector3<T> v;
				T s;
			};
		};
		#include "DisableAnonymousStructEnd.hpp"
};

template<typename T>
inline Quaternion<T>::Quaternion()
{
	v = Vector3<T>::zero();
	s = T(1);

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const Quaternion<T>& q)
{
	v = q.v;
	s = q.s;

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const T* a)
{
	v.x = a[0];
	v.y = a[1];
	v.z = a[2];
	s = a[3];

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const Vector4<T>& v)
{
	this->v.x = v.x;
	this->v.y = v.y;
	this->v.z = v.z;
	s = v.w;

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const T& x, const T& y, const T& z, const T& w)
{
	v.set(x, y, z);
	s = w;

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const Vector3<T>& v, const T& s)
{
	this->v = v;
	this->s = s;

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const Vector3<T>& eulerAngles)
{
	T cp = cos(eulerAngles.x * 0.5);
	T sp = sin(eulerAngles.x * 0.5);
	T cy = cos(eulerAngles.y * 0.5);
	T sy = sin(eulerAngles.y * 0.5);
	T cr = cos(eulerAngles.z * 0.5);
	T sr = sin(eulerAngles.z * 0.5);

	v.x = cy * sr * cp - sy * cr * sp;
	v.y = cy * cr * sp + sy * sr * cp;
	v.z = sy * cr * cp - cy * sr * sp;
	s = cy * cr * cp + sy * sr * sp;

	ensureNormalized();

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const T& pitch, const T& yaw, const T& roll)
{
	T cp = cos(pitch * 0.5);
	T sp = sin(pitch * 0.5);
	T cy = cos(yaw * 0.5);
	T sy = sin(yaw * 0.5);
	T cr = cos(roll * 0.5);
	T sr = sin(roll * 0.5);

	v.x = cy * sr * cp - sy * cr * sp;
	v.y = cy * cr * sp + sy * sr * cp;
	v.z = sy * cr * cp - cy * sr * sp;
	s = cy * cr * cp + sy * sr * sp;

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>::Quaternion(const T& angle, const Vector3<T>& axis)
{
	const T halfAngle = angle * T(0.5);

	v.set(axis.normalize() * oe::sin(halfAngle));
	s = oe::cos(halfAngle);

	ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const Quaternion<T>& q)
{
	v = q.v;
	s = q.s;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const T* a)
{
	v.x = a[0];
	v.y = a[1];
	v.z = a[2];
	s = a[3];

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const Vector4<T>& v)
{
	this->v.x = v.x;
	this->v.y = v.y;
	this->v.z = v.z;
	s = v.w;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const T& x, const T& y, const T& z, const T& w)
{
	v.set(x, y, z);
	s = w;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const Vector3<T>& v, const T& s)
{
	this->v = v;
	this->s = s;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const Vector3<T>& eulerAngles)
{
	T cp = cos(eulerAngles.x * 0.5);
	T sp = sin(eulerAngles.x * 0.5);
	T cy = cos(eulerAngles.y * 0.5);
	T sy = sin(eulerAngles.y * 0.5);
	T cr = cos(eulerAngles.z * 0.5);
	T sr = sin(eulerAngles.z * 0.5);

	v.x = cy * sr * cp - sy * cr * sp;
	v.y = cy * cr * sp + sy * sr * cp;
	v.z = sy * cr * cp - cy * sr * sp;
	s = cy * cr * cp + sy * sr * sp;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const T& pitch, const T& yaw, const T& roll)
{
	T cp = cos(pitch * 0.5);
	T sp = sin(pitch * 0.5);
	T cy = cos(yaw * 0.5);
	T sy = sin(yaw * 0.5);
	T cr = cos(roll * 0.5);
	T sr = sin(roll * 0.5);

	v.x = cy * sr * cp - sy * cr * sp;
	v.y = cy * cr * sp + sy * sr * cp;
	v.z = sy * cr * cp - cy * sr * sp;
	s = cy * cr * cp + sy * sr * sp;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::set(const T& angle, const Vector3<T>& axis)
{
	const T halfAngle = angle * T(0.5);

	v.set(axis.normalize() * oe::sin(halfAngle));
	s = oe::cos(halfAngle);

	ensureNormalized();
}

template<typename T>
inline T& Quaternion<T>::operator()(U32 i)
{
	switch (i)
	{
		case 0: return v.x; break;
		case 1: return v.y; break;
		case 2: return v.z; break;
		default: break;
	}
	return s;
}

template<typename T>
inline const T& Quaternion<T>::operator()(U32 i) const
{
	switch (i)
	{
		case 0: return v.x; break;
		case 1: return v.y; break;
		case 2: return v.z; break;
		default: break;
	}
	return s;
}

template<typename T>
inline T & Quaternion<T>::operator[](U32 i)
{
	switch (i)
	{
		case 0: return v.x; break;
		case 1: return v.y; break;
		case 2: return v.z; break;
		default: break;
	}
	return s;
}

template<typename T>
inline const T & Quaternion<T>::operator[](U32 i) const
{
	switch (i)
	{
		case 0: return v.x; break;
		case 1: return v.y; break;
		case 2: return v.z; break;
		default: break;
	}
	return s;
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& q)
{
	v = q.v;
	s = q.s;

	return ensureNormalized();
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& q) const
{
	Quaternion<T> result;
	result.v += s * q.v;
	result.v += q.s * v;
	result.v += v.crossProduct(q.v);
	result.s = s * q.s - v.dotProduct(q.v);
	return result.ensureNormalized();
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& q)
{
	Quaternion<T> p(*this);
	v = Vector3<T>::zero();
	v += p.s * q.v;
	v += q.s * p.v;
	v += p.v.crossProduct(q.v);
	s = p.s * q.s - p.v.dotProduct(q.v);
	return ensureNormalized();
}

template<typename T>
inline bool Quaternion<T>::operator==(const Quaternion<T>& q) const
{
	if (!equals(s, q.s)) return false;
	return v == q.v;
}

template<typename T>
inline bool Quaternion<T>::operator!=(const Quaternion<T>& q) const
{
	return !operator==(q);
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::conjugate()
{
	v *= T(-1);
	return *this;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::conjugated()
{
	return Quaternion<T>(-v, s);
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::inverse()
{
	conjugate();
	if (!equals(getSquaredLength(), T(1)))
	{
		const T sLength = getSquaredLength();
		v /= sLength;
		s /= sLength;
	}
	return *this;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::inversed()
{
	return Quaternion<T>(*this).inverse();
}

template<typename T>
inline Vector3<T>& Quaternion<T>::rotate(Vector3<T>& vector) const
{
	Vector3<T> v(vector);
	Vector3<T> u(q.x, q.y, q.z);
	T s = q.w;
	vector = T(2) * u.dotProduct(v) * u + (s*s - u.dotProduct(u)) * v + T(2) * s * u.crossProduct(v);
}

template<typename T>
inline Vector3<T> Quaternion<T>::rotated(const Vector3<T>& vector) const
{
	return Vector3<T>(vector).rotate();
}

template<typename T>
inline T Quaternion<T>::dotProduct(const Quaternion<T>& q) const
{
	return v.dotProduct(q.v) + s * q.s;
}

template<typename T>
inline T Quaternion<T>::getSquaredLength() const
{
	return dotProduct(*this);
}

template<typename T>
inline T Quaternion<T>::getLength() const
{
	return std::sqrt(getSquaredLength());
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::normalize(T* oldLength)
{
	const T currentLength = getLength();
	if (oldLength != nullptr)
	{
		*oldLength = currentLength;
	}
	const T factor = T(1) / currentLength;
	v *= factor;
	s *= factor;
	return *this;
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::ensureNormalized()
{
	if (!equals(getSquaredLength(), T(1)))
	{
		return normalize();
	}
	return *this;
}

template<typename T>
inline void Quaternion<T>::toEulerAngles(Vector3<T>& vector) const
{
	// TODO : 
}

template<typename T>
inline void Quaternion<T>::toAngleAxis(T& angle, Vector3<T>& axis) const
{
	// TODO :
}

template<typename T>
inline Quaternion<T> Quaternion<T>::lerp(const Quaternion<T>& start, const Quaternion<T>& end, const T& percent)
{
	return Quaternion<T>(); // TODO : 
}

template<typename T>
inline Quaternion<T> Quaternion<T>::slerp(const Quaternion<T>& start, const Quaternion<T>& end, const T& percent)
{
	return Quaternion<T>(); // TODO : 
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::makeIdentity()
{
	v.makeZero();
	s = T(1);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::identity()
{
	return Quaternion<T>(Vector3<T>::zero(), T(1));
}


typedef Quaternion<F32> Quaternionf;

typedef Quaternionf quat; // GLSL-like

} // namespace nu

#endif // NU_QUATERNION_HPP