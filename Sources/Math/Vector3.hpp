#ifndef NU_VECTOR3_HPP
#define NU_VECTOR3_HPP

#include "Utilities.hpp"

#include "Vector2.hpp"

#ifndef NU_MATH_VEC3_FORWARD
#define NU_MATH_VEC3_FORWARD 0,0,1
#endif

#ifndef NU_MATH_VEC3_BACK
#define NU_MATH_VEC3_BACK 0,0,-1
#endif

#ifndef NU_MATH_VEC3_UP
#define NU_MATH_VEC3_UP 0,1,0
#endif

#ifndef NU_MATH_VEC3_DOWN
#define NU_MATH_VEC3_DOWN 0,-1,0
#endif

#ifndef NU_MATH_VEC3_RIGHT
#define NU_MATH_VEC3_RIGHT -1,0,0
#endif

#ifndef NU_MATH_VEC3_LEFT
#define NU_MATH_VEC3_LEFT 1,0,0
#endif

// TODO : Vector3 Aligned ?

namespace nu
{

template <typename T>
class Vector3
{
	public:
		static const I32 d = 3;

		inline Vector3();
		inline Vector3(const Vector3<T>& v);
		template <typename U>
		explicit inline Vector3(const Vector3<U>& v);
		explicit inline Vector3(const T& s);
		explicit inline Vector3(const T* a);
		inline Vector3(const T& s1, const T& s2, const T& s3);
		inline Vector3(const Vector2<T>& v12, const T& s3);
		~Vector3() = default;

		inline Vector3<T>& set(const Vector3<T>& v);
		template <typename U>
		inline Vector3<T>& set(const Vector3<U>& v);
		inline Vector3<T>& set(const T& s);
		inline Vector3<T>& set(const T* a);
		inline Vector3<T>& set(const T& s1, const T& s2, const T& s3);
		inline Vector3<T>& set(const Vector2<T>& v12, const T& s3);

		inline T& operator()(U32 i);
		inline const T& operator()(U32 i) const;
		inline T& operator[](U32 i);
		inline const T& operator[](U32 i) const;

		inline Vector3<T>& operator=(const Vector3<T>& vec);
		inline const Vector3<T>& operator+() const;
		inline Vector3<T> operator-() const;

		inline Vector3<T> operator+(const Vector3<T>& vec) const;
		inline Vector3<T> operator-(const Vector3<T>& vec) const;
		inline Vector3<T> operator*(const Vector3<T>& vec) const;
		inline Vector3<T> operator/(const Vector3<T>& vec) const;
		inline Vector3<T>& operator+=(const Vector3<T>& vec);
		inline Vector3<T>& operator-=(const Vector3<T>& vec);
		inline Vector3<T>& operator*=(const Vector3<T>& vec);
		inline Vector3<T>& operator/=(const Vector3<T>& vec);

		inline Vector3<T> operator+(T scale) const;
		inline Vector3<T> operator-(T scale) const;
		inline Vector3<T> operator*(T scale) const;
		inline Vector3<T> operator/(T scale) const;
		inline Vector3<T>& operator+=(T scale);
		inline Vector3<T>& operator-=(T scale);
		inline Vector3<T>& operator*=(T scale);
		inline Vector3<T>& operator/=(T scale);

		inline bool isZero() const;
		inline bool operator==(const Vector3<T>& vec) const;
		inline bool operator!=(const Vector3<T>& vec) const;
		inline bool operator<(const Vector3<T>& vec) const;
		inline bool operator<=(const Vector3<T>& vec) const;
		inline bool operator>(const Vector3<T>& vec) const;
		inline bool operator>=(const Vector3<T>& vec) const;

		inline Vector2<T> xy() const;
		inline Vector2<T> xz() const;
		inline Vector2<T> yz() const;

		inline T dotProduct(const Vector3<T>& v) const;
		static inline T dotProduct(const Vector3<T>& v1, const Vector3<T>& v2);

		inline T getSquaredLength() const;
		inline T getLength() const;

		inline Vector3<T>& setLength(const T& length, T* oldLength = nullptr);

		inline Vector3<T>& normalize(T* oldLength = nullptr);
		inline Vector3<T> normalized(T* oldLength = nullptr) const;

		inline Vector3<T> crossProduct(const Vector3<T>& v) const;
		static inline Vector3<T> crossProduct(const Vector3<T>& v1, const Vector3<T>& v2);

		inline Vector3<T> perpendicularVector() const;

		static inline Vector3<T> lerp(const Vector3<T>& v1, const Vector3<T>& v2, const T& percent);

		inline Vector3<T>& maximize(const Vector3<T>& v);
		static inline Vector3<T> maximum(const Vector3<T>& v1, const Vector3<T>& v2);

		inline Vector3<T>& minimize(const Vector3<T>& v);
		static inline Vector3<T> minimum(const Vector3<T>& v1, const Vector3<T>& v2);

		inline Vector3<T>& makeUnit();
		inline Vector3<T>& makeUnitX();
		inline Vector3<T>& makeUnitY();
		inline Vector3<T>& makeUnitZ();
		inline Vector3<T>& makeZero();

		static const Vector3<T> unit;
		static const Vector3<T> unitX;
		static const Vector3<T> unitY;
		static const Vector3<T> unitZ;
		static const Vector3<T> zero;

		static const Vector3<T> forward;
		static const Vector3<T> back;
		static const Vector3<T> up;
		static const Vector3<T> down;
		static const Vector3<T> right;
		static const Vector3<T> left;

		#include "DisableAnonymousStructBegin.hpp"
		union 
		{
			T data[3];
			struct 
			{
				T x;
				T y;
				T z;
			};
		};
		#include "DisableAnonymousStructEnd.hpp"
};

template <typename T> Vector3<T> operator+(const T& scale, const Vector3<T>& vector);
template <typename T> Vector3<T> operator-(const T& scale, const Vector3<T>& vector);
template <typename T> Vector3<T> operator*(const T& scale, const Vector3<T>& vector);
template <typename T> Vector3<T> operator/(const T& scale, const Vector3<T>& vector);

template <typename T> T dot(const Vector3<T>& v1, const Vector3<T>& v2);

template <typename T> Vector3<T> normalize(const Vector3<T>& vec, T* oldLength = nullptr);

template <typename T> Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2);

template <typename T> bool equalsVector(const Vector3<T>& v1, const Vector3<T>& v2, const T& epsilon = std::numeric_limits<T>::epsilon());

template<typename T>
inline Vector3<T>::Vector3()
{
}

template<typename T>
inline Vector3<T>::Vector3(const Vector3<T>& v)
{
	std::memcpy(data, v.data, 3 * sizeof(T));
}

template<typename T>
template<typename U>
inline Vector3<T>::Vector3(const Vector3<U>& v)
{
	data[0] = T(v.data[0]);
	data[1] = T(v.data[1]);
	data[2] = T(v.data[2]);
}

template<typename T>
inline Vector3<T>::Vector3(const T& s)
{
	data[0] = s;
	data[1] = s;
	data[2] = s;
}

template<typename T>
inline Vector3<T>::Vector3(const T* a)
{
	std::memcpy(data, a, 3 * sizeof(T));
}

template<typename T>
inline Vector3<T>::Vector3(const T& s1, const T& s2, const T& s3)
{
	data[0] = s1;
	data[1] = s2;
	data[2] = s3;
}

template<typename T>
inline Vector3<T>::Vector3(const Vector2<T>& v12, const T& s3)
{
	data[0] = v12.data[0];
	data[1] = v12.data[1];
	data[2] = s3;
}

template<typename T>
inline Vector3<T>& Vector3<T>::set(const Vector3<T>& v)
{
	std::memcpy(data, v.data, 3 * sizeof(T));
	return *this;
}

template<typename T>
template<typename U>
inline Vector3<T>& Vector3<T>::set(const Vector3<U>& v)
{
	data[0] = T(v.data[0]);
	data[1] = T(v.data[1]);
	data[2] = T(v.data[2]);
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::set(const T& s)
{
	data[0] = s;
	data[1] = s;
	data[2] = s;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::set(const T* a)
{
	std::memcpy(data, a, 3 * sizeof(T));
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::set(const T& s1, const T& s2, const T& s3)
{
	data[0] = s1;
	data[1] = s2;
	data[2] = s3;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::set(const Vector2<T>& v12, const T& s3)
{
	data[0] = v12.data[0];
	data[1] = v12.data[1];
	data[2] = s3;
	return *this;
}

template<typename T>
inline T& Vector3<T>::operator()(U32 i)
{
	return data[i];
}

template<typename T>
inline const T& Vector3<T>::operator()(U32 i) const
{
	return data[i];
}

template<typename T>
inline T& Vector3<T>::operator[](U32 i)
{
	return data[i];
}

template<typename T>
inline const T& Vector3<T>::operator[](U32 i) const
{
	return data[i];
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& vec)
{
	std::memcpy(data, vec.data, 3 * sizeof(T));
	return *this;
}

template<typename T>
inline const Vector3<T>& Vector3<T>::operator+() const
{
	return *this;
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-() const
{
	return Vector3<T>(-data[0], -data[1], -data[2]);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& vec) const
{
	return Vector3<T>(data[0] + vec.data[0], data[1] + vec.data[1], data[2] + vec.data[2]);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& vec) const
{
	return Vector3<T>(data[0] - vec.data[0], data[1] - vec.data[1], data[2] - vec.data[2]);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const Vector3<T>& vec) const
{
	return Vector3<T>(data[0] * vec.data[0], data[1] * vec.data[1], data[2] * vec.data[2]);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator/(const Vector3<T>& vec) const
{
	return Vector3<T>(data[0] / vec.data[0], data[1] / vec.data[1], data[2] / vec.data[2]);
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& vec)
{
	data[0] += vec.data[0];
	data[1] += vec.data[1];
	data[2] += vec.data[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& vec)
{
	data[0] -= vec.data[0];
	data[1] -= vec.data[1];
	data[2] -= vec.data[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& vec)
{
	data[0] *= vec.data[0];
	data[1] *= vec.data[1];
	data[2] *= vec.data[2];
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& vec)
{
	data[0] /= vec.data[0];
	data[1] /= vec.data[1];
	data[2] /= vec.data[2];
	return *this;
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(T scale) const
{
	return Vector3<T>(data[0] + scale, data[1] + scale, data[2] + scale);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(T scale) const
{
	return Vector3<T>(data[0] - scale, data[1] - scale, data[2] - scale);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(T scale) const
{
	return Vector3<T>(data[0] * scale, data[1] * scale, data[2] * scale);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator/(T scale) const
{
	const T inv = 1 / scale;
	return Vector3<T>(data[0] * inv, data[1] * inv, data[2] * inv);
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(T scale)
{
	data[0] += scale;
	data[1] += scale;
	data[2] += scale;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(T scale)
{
	data[0] -= scale;
	data[1] -= scale;
	data[2] -= scale;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(T scale)
{
	data[0] *= scale;
	data[1] *= scale;
	data[2] *= scale;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(T scale)
{
	const T inv = 1 / scale;
	data[0] *= inv;
	data[1] *= inv;
	data[2] *= inv;
	return *this;
}

template<typename T>
inline bool Vector3<T>::isZero() const
{
	if (!equals(data[0], T(0))) return false;
	if (!equals(data[1], T(0))) return false;
	return equals(data[2], T(0));
}

template<typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& vec) const
{
	if (!equals(data[0], vec.data[0])) return false;
	if (!equals(data[1], vec.data[1])) return false;
	return equals(data[2], vec.data[2]);
}

template<typename T>
inline bool Vector3<T>::operator!=(const Vector3<T>& vec) const
{
	return !operator==(vec);
}

template<typename T>
inline bool Vector3<T>::operator<(const Vector3<T>& vec) const
{
	if (data[0] >= vec.data[0]) return false;
	if (data[1] >= vec.data[1]) return false;
	return (data[2] < vec.data[2]);
}

template<typename T>
inline bool Vector3<T>::operator<=(const Vector3<T>& vec) const
{
	if (data[0] > vec.data[0]) return false;
	if (data[1] > vec.data[1]) return false;
	return (data[2] <= vec.data[2]);
}

template<typename T>
inline bool Vector3<T>::operator>(const Vector3<T>& vec) const
{
	return !operator<=(vec);
}

template<typename T>
inline bool Vector3<T>::operator>=(const Vector3<T>& vec) const
{
	return !operator<(vec);
}

template<typename T>
inline Vector2<T> Vector3<T>::xy() const
{
	return Vector2<T>(x ,y);
}

template<typename T>
inline Vector2<T> Vector3<T>::xz() const
{
	return Vector2<T>(x, z);
}

template<typename T>
inline Vector2<T> Vector3<T>::yz() const
{
	return Vector2<T>(y, z);
}

template<typename T>
inline T Vector3<T>::dotProduct(const Vector3<T>& v) const
{
	return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2];
}

template<typename T>
inline T Vector3<T>::dotProduct(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] + v1.data[2] * v2.data[2];
}

template<typename T>
inline T Vector3<T>::getSquaredLength() const
{
	return dotProduct(*this);
}

template<typename T>
inline T Vector3<T>::getLength() const
{
	return std::sqrt(getSquaredLength());
}

template<typename T>
inline Vector3<T>& Vector3<T>::setLength(const T& length, T* oldLength)
{
	const T currentLength = getLength();
	if (oldLength != nullptr)
	{
		*oldLength = currentLength;
	}
	const T factor = length / currentLength;
	data[0] *= factor;
	data[1] *= factor;
	data[2] *= factor;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::normalize(T* oldLength)
{
	return setLength(T(1), oldLength);
}

template<typename T>
inline Vector3<T> Vector3<T>::normalized(T* oldLength) const
{
	return Vector3<T>(*this).normalize(oldLength);
}

template<typename T>
inline Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& v) const
{
	return Vector3<T>(data[1] * v.data[2] - data[2] * v.data[1], data[2] * v.data[0] - data[0] * v.data[2], data[0] * v.data[1] - data[1] * v.data[0]);
}

template<typename T>
inline Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1], v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2], v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]);
}

template<typename T>
inline Vector3<T> Vector3<T>::perpendicularVector() const
{
	Vector3<T> axis = Vector3<T>::crossProduct(unitX(), *this);
	if (axis.getSquaredLength() < T(0.05)) 
	{
		axis = Vector3<T>::crossProduct(unitY(), *this);
	}
	return axis.normalize();
}

template<typename T>
inline Vector3<T> Vector3<T>::lerp(const Vector3<T>& v1, const Vector3<T>& v2, const T& percent)
{
	const T one_minus_percent = T(1) - percent;
	return Vector3<T>(one_minus_percent * v1.data[0] + percent * v2.data[0], one_minus_percent * v1.data[1] + percent * v2.data[1], one_minus_percent * v1.data[2] + percent * v2.data[2]);
}

template<typename T>
inline Vector3<T>& Vector3<T>::maximize(const Vector3<T>& v)
{
	if (v.data[0] > data[0]) data[0] = v.data[0];
	if (v.data[1] > data[1]) data[1] = v.data[1];
	if (v.data[2] > data[2]) data[2] = v.data[2];
	return *this;
}

template<typename T>
inline Vector3<T> Vector3<T>::maximum(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(std::max(v1.data[0], v2.data[0]), std::max(v1.data[1], v2.data[1]), std::max(v1.data[2], v2.data[2]));
}

template<typename T>
inline Vector3<T>& Vector3<T>::minimize(const Vector3<T>& v)
{
	if (v.data[0] < data[0]) data[0] = v.data[0];
	if (v.data[1] < data[1]) data[1] = v.data[1];
	if (v.data[2] < data[2]) data[2] = v.data[2];
	return *this;
}

template<typename T>
inline Vector3<T> Vector3<T>::minimum(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return Vector3<T>(std::min(v1.data[0], v2.data[0]), std::min(v1.data[1], v2.data[1]), std::min(v1.data[2], v2.data[2]));
}

template<typename T>
inline Vector3<T>& Vector3<T>::makeUnit()
{
	return set(T(1), T(1), T(1));
}

template<typename T>
inline Vector3<T>& Vector3<T>::makeUnitX()
{
	return set(T(1), T(0), T(0));
}

template<typename T>
inline Vector3<T>& Vector3<T>::makeUnitY()
{
	return set(T(0), T(1), T(0));
}

template<typename T>
inline Vector3<T>& Vector3<T>::makeUnitZ()
{
	return set(T(0), T(0), T(1));
}

template<typename T>
inline Vector3<T>& Vector3<T>::makeZero()
{
	return set(T(0), T(0), T(0));
}

template <typename T> const Vector3<T> Vector3<T>::unit(1, 1, 1);
template <typename T> const Vector3<T> Vector3<T>::unitX(1, 0, 0);
template <typename T> const Vector3<T> Vector3<T>::unitY(0, 1, 0);
template <typename T> const Vector3<T> Vector3<T>::unitZ(0, 0, 1);
template <typename T> const Vector3<T> Vector3<T>::zero(0, 0, 0);

template <typename T> const Vector3<T> Vector3<T>::forward(NU_MATH_VEC3_FORWARD);
template <typename T> const Vector3<T> Vector3<T>::back(NU_MATH_VEC3_BACK);
template <typename T> const Vector3<T> Vector3<T>::up(NU_MATH_VEC3_UP);
template <typename T> const Vector3<T> Vector3<T>::down(NU_MATH_VEC3_DOWN);
template <typename T> const Vector3<T> Vector3<T>::right(NU_MATH_VEC3_RIGHT);
template <typename T> const Vector3<T> Vector3<T>::left(NU_MATH_VEC3_LEFT);

template<typename T>
Vector3<T> operator+(const T& scale, const Vector3<T>& vector)
{
	return vector + scale;
}

template<typename T>
Vector3<T> operator-(const T& scale, const Vector3<T>& vector)
{
	return scale + (vector.operator-());
}

template<typename T>
inline Vector3<T> operator*(const T& scale, const Vector3<T>& vector)
{
	return vector * scale;
}

template<typename T>
Vector3<T> operator/(const T& scale, const Vector3<T>& vector)
{
	assert(!equals(vector[0], T(0)));
	assert(!equals(vector[1], T(0)));
	assert(!equals(vector[2], T(0)));
	return Vector3<T>(scale / vector[0], scale / vector[1], scale / vector[2]);
}

template<typename T>
T dot(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return v1.dotProduct(v2);
}

template<typename T>
Vector3<T> normalize(const Vector3<T>& vec, T* oldLength)
{
	return vec.normalized(oldLength);
}

template<typename T>
Vector3<T> cross(const Vector3<T>& v1, const Vector3<T>& v2)
{
	return v1.crossProduct(v2);
}

template <typename T>
bool equalsVector(const Vector3<T>& v1, const Vector3<T>& v2, const T& epsilon)
{
	if (!equals(v1.x, v2.x, epsilon)) return false;
	if (!equals(v1.y, v2.y, epsilon)) return false;
	return equals(v1.z, v2.z, epsilon);
}

typedef Vector3<F32> Vector3f;
typedef Vector3<I32> Vector3i;
typedef Vector3<U32> Vector3u;

typedef Vector3f vec3; // GLSL-like

} // namespace nu

#endif // NU_VECTOR3_HPP