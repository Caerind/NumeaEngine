#ifndef NU_VECTOR4_HPP
#define NU_VECTOR4_HPP

#include "Utilities.hpp"

#include "Vector3.hpp"

namespace nu
{

template <typename T>
class Vector4
{
	public:
		static const int d = 4;

		inline Vector4();
		inline Vector4(const Vector4<T>& v);
		template <typename U>
		explicit inline Vector4(const Vector4<U>& v);
		explicit inline Vector4(const T& s);
		explicit inline Vector4(const T* a);
		inline Vector4(const T& s1, const T& s2, const T& s3, const T& s4);
		inline Vector4(const Vector3<T>& v123, const T& s4);
		inline Vector4(const Vector2<T>& v12, const Vector2<T>& v34);
		~Vector4() = default;

		inline Vector4<T>& set(const Vector4<T>& v);
		template <typename U>
		inline Vector4<T>& set(const Vector4<U>& v);
		inline Vector4<T>& set(const T& s);
		inline Vector4<T>& set(const T* a);
		inline Vector4<T>& set(const T& s1, const T& s2, const T& s3, const T& s4);
		inline Vector4<T>& set(const Vector3<T>& v123, const T& s4);
		inline Vector4<T>& set(const Vector2<T>& v12, const Vector2<T>& v34);

		inline T& operator()(U32 i);
		inline const T& operator()(U32 i) const;
		inline T& operator[](U32 i);
		inline const T& operator[](U32 i) const;

		inline Vector4<T>& operator=(const Vector4<T>& vec);
		inline const Vector4<T>& operator+() const;
		inline Vector4<T> operator-() const;

		inline Vector4<T> operator+(const Vector4<T>& vec) const;
		inline Vector4<T> operator-(const Vector4<T>& vec) const;
		inline Vector4<T> operator*(const Vector4<T>& vec) const;
		inline Vector4<T> operator/(const Vector4<T>& vec) const;
		inline Vector4<T>& operator+=(const Vector4<T>& vec);
		inline Vector4<T>& operator-=(const Vector4<T>& vec);
		inline Vector4<T>& operator*=(const Vector4<T>& vec);
		inline Vector4<T>& operator/=(const Vector4<T>& vec);

		inline Vector4<T> operator+(T scale) const;
		inline Vector4<T> operator-(T scale) const;
		inline Vector4<T> operator*(T scale) const;
		inline Vector4<T> operator/(T scale) const;
		inline Vector4<T>& operator+=(T scale);
		inline Vector4<T>& operator-=(T scale);
		inline Vector4<T>& operator*=(T scale);
		inline Vector4<T>& operator/=(T scale);

		inline bool isZero() const;
		inline bool operator==(const Vector4<T>& vec) const;
		inline bool operator!=(const Vector4<T>& vec) const;
		inline bool operator<(const Vector4<T>& vec) const;
		inline bool operator<=(const Vector4<T>& vec) const;
		inline bool operator>(const Vector4<T>& vec) const;
		inline bool operator>=(const Vector4<T>& vec) const;

		inline Vector3<T> xyz();
		inline const Vector3<T> xyz() const;
		inline Vector2<T> xy();
		inline const Vector2<T> xy() const;
		inline Vector2<T> xz();
		inline const Vector2<T> xz() const;
		inline Vector2<T> yz();
		inline const Vector2<T> yz() const;
		inline Vector2<T> zw();
		inline const Vector2<T> zw() const;

		inline T dotProduct(const Vector4<T>& v) const;
		static inline T dotProduct(const Vector4<T>& v1, const Vector4<T>& v2);

		inline T getSquaredLength() const;
		inline T getLength() const;

		inline T getSquaredDistance(const Vector4<T>& v);
		static inline T getSquaredDistance(const Vector4<T>& v1, const Vector4<T>& v2);
		inline T getDistance(const Vector4<T>& v);
		static inline T getDistance(const Vector4<T>& v1, const Vector4<T>& v2);

		inline Vector4<T>& setLength(const T& length, T* oldLength = nullptr);

		inline Vector4<T>& normalize(T* oldLength = nullptr);
		inline Vector4<T> normalized(T* oldLength = nullptr) const;

		inline Vector3<T> crossProduct(const Vector4<T>& v) const;
		static inline Vector3<T> crossProduct(const Vector4<T>& v1, const Vector4<T>& v2);

		static inline Vector4<T> lerp(const Vector4<T>& v1, const Vector4<T>& v2, const T& percent);

		inline Vector4<T>& maximize(const Vector4<T>& v);
		static inline Vector4<T> maximum(const Vector4<T>& v1, const Vector4<T>& v2);

		inline Vector4<T>& minimize(const Vector4<T>& v);
		static inline Vector4<T> minimum(const Vector4<T>& v1, const Vector4<T>& v2);

		inline Vector4<T>& makeUnit();
		inline Vector4<T>& makeUnitX();
		inline Vector4<T>& makeUnitY();
		inline Vector4<T>& makeUnitZ();
		inline Vector4<T>& makeUnitW();
		inline Vector4<T>& makeZero();

		static inline Vector4<T> unit();
		static inline Vector4<T> unitX();
		static inline Vector4<T> unitY();
		static inline Vector4<T> unitZ();
		static inline Vector4<T> unitW();
		static inline Vector4<T> zero();

		#include "DisableAnonymousStructBegin.hpp"
		union 
		{
			T data[4];
			struct 
			{
				T x;
				T y;
				T z;
				T w;
			};
		};
		#include "DisableAnonymousStructEnd.hpp"
};

template <typename T>
Vector4<T> operator*(const T& scale, const Vector4<T>& vector);

template<typename T>
inline Vector4<T>::Vector4()
{
	data[0] = T(0);
	data[1] = T(0);
	data[2] = T(0);
	data[3] = T(0);
}

template<typename T>
inline Vector4<T>::Vector4(const Vector4<T>& v)
{
	std::memcpy(data, v.data, 4 * sizeof(T));
}

template<typename T>
template<typename U>
inline Vector4<T>::Vector4(const Vector4<U>& v)
{
	data[0] = T(v.data[0]);
	data[1] = T(v.data[1]);
	data[2] = T(v.data[2]);
	data[3] = T(v.data[3]);
}

template<typename T>
inline Vector4<T>::Vector4(const T& s)
{
	data[0] = s;
	data[1] = s;
	data[2] = s;
	data[3] = s;
}

template<typename T>
inline Vector4<T>::Vector4(const T* a)
{
	std::memcpy(data, a, 4 * sizeof(T));
}

template<typename T>
inline Vector4<T>::Vector4(const T& s1, const T& s2, const T& s3, const T& s4)
{
	data[0] = s1;
	data[1] = s2;
	data[2] = s3;
	data[3] = s4;
}

template<typename T>
inline Vector4<T>::Vector4(const Vector3<T>& v123, const T& s4)
{
	data[0] = v123.data[0];
	data[1] = v123.data[1];
	data[2] = v123.data[2];
	data[3] = s4;
}

template<typename T>
inline Vector4<T>::Vector4(const Vector2<T>& v12, const Vector2<T>& v34)
{
	data[0] = v12.data[0];
	data[1] = v12.data[1];
	data[2] = v34.data[0];
	data[3] = v34.data[1];
}

template<typename T>
inline Vector4<T>& Vector4<T>::set(const Vector4<T>& v)
{
	std::memcpy(data, v.data, 4 * sizeof(T));
	return *this;
}

template<typename T>
template<typename U>
inline Vector4<T>& Vector4<T>::set(const Vector4<U>& v)
{
	data[0] = T(v.data[0]);
	data[1] = T(v.data[1]);
	data[2] = T(v.data[2]);
	data[3] = T(v.data[3]);
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::set(const T& s)
{
	data[0] = s;
	data[1] = s;
	data[2] = s;
	data[3] = s;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::set(const T* a)
{
	std::memcpy(data, a, 4 * sizeof(T));
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::set(const T& s1, const T& s2, const T& s3, const T& s4)
{
	data[0] = s1;
	data[1] = s2;
	data[2] = s3;
	data[3] = s4;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::set(const Vector3<T>& v123, const T& s4)
{
	data[0] = v123.data[0];
	data[1] = v123.data[1];
	data[2] = v123.data[2];
	data[3] = s4;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::set(const Vector2<T>& v12, const Vector2<T>& v34)
{
	data[0] = v12.data[0];
	data[1] = v12.data[1];
	data[2] = v34.data[0];
	data[3] = v34.data[1];
	return *this;
}

template<typename T>
inline T& Vector4<T>::operator()(U32 i)
{
	return data[i];
}

template<typename T>
inline const T& Vector4<T>::operator()(U32 i) const
{
	return data[i];
}

template<typename T>
inline T& Vector4<T>::operator[](U32 i)
{
	return data[i];
}

template<typename T>
inline const T& Vector4<T>::operator[](U32 i) const
{
	return data[i];
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(const Vector4<T>& vec)
{
	std::memcpy(data, vec.data, 4 * sizeof(T));
	return *this;
}

template<typename T>
inline const Vector4<T>& Vector4<T>::operator+() const
{
	return *this;
}

template<typename T>
inline Vector4<T> Vector4<T>::operator-() const
{
	return Vector4<T>(-data[0], -data[1], -data[2], -data[3]);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator+(const Vector4<T>& vec) const
{
	return Vector4<T>(data[0] + vec.data[0], data[1] + vec.data[1], data[2] + vec.data[2], data[3] + vec.data[3]);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator-(const Vector4<T>& vec) const
{
	return Vector4<T>(data[0] - vec.data[0], data[1] - vec.data[1], data[2] - vec.data[2], data[3] - vec.data[3]);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator*(const Vector4<T>& vec) const
{
	return Vector4<T>(data[0] * vec.data[0], data[1] * vec.data[1], data[2] * vec.data[2], data[3] * vec.data[3]);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator/(const Vector4<T>& vec) const
{
	return Vector4<T>(data[0] / vec.data[0], data[1] / vec.data[1], data[2] / vec.data[2], data[3] / vec.data[3]);
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& vec)
{
	data[0] += vec.data[0];
	data[1] += vec.data[1];
	data[2] += vec.data[2];
	data[3] += vec.data[3];
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& vec)
{
	data[0] -= vec.data[0];
	data[1] -= vec.data[1];
	data[2] -= vec.data[2];
	data[3] -= vec.data[3];
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& vec)
{
	data[0] *= vec.data[0];
	data[1] *= vec.data[1];
	data[2] *= vec.data[2];
	data[3] *= vec.data[3];
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& vec)
{
	data[0] /= vec.data[0];
	data[1] /= vec.data[1];
	data[2] /= vec.data[2];
	data[3] /= vec.data[3];
	return *this;
}

template<typename T>
inline Vector4<T> Vector4<T>::operator+(T scale) const
{
	return Vector4<T>(data[0] + scale, data[1] + scale, data[2] + scale, data[3] + scale);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator-(T scale) const
{
	return Vector4<T>(data[0] - scale, data[1] - scale, data[2] - scale, data[3] - scale);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator*(T scale) const
{
	return Vector4<T>(data[0] * scale, data[1] * scale, data[2] * scale, data[3] * scale);
}

template<typename T>
inline Vector4<T> Vector4<T>::operator/(T scale) const
{
	const T inv = 1 / scale;
	return Vector4<T>(data[0] * inv, data[1] * inv, data[2] * inv, data[3] * inv);
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(T scale)
{
	data[0] += scale;
	data[1] += scale;
	data[2] += scale;
	data[3] += scale;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(T scale)
{
	data[0] -= scale;
	data[1] -= scale;
	data[2] -= scale;
	data[3] -= scale;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator*=(T scale)
{
	data[0] *= scale;
	data[1] *= scale;
	data[2] *= scale;
	data[3] *= scale;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(T scale)
{
	const T inv = 1 / scale;
	data[0] *= inv;
	data[1] *= inv;
	data[2] *= inv;
	data[3] *= inv;
	return *this;
}

template<typename T>
inline bool Vector4<T>::isZero() const
{
	if (!equals(data[0], 0)) return false;
	if (!equals(data[1], 0)) return false;
	if (!equals(data[2], 0)) return false;
	return equals(data[3], 0);
}

template<typename T>
inline bool Vector4<T>::operator==(const Vector4<T>& vec) const
{
	if (!equals(data[0], vec.data[0])) return false;
	if (!equals(data[1], vec.data[1])) return false;
	if (!equals(data[2], vec.data[2])) return false;
	return equals(data[3], vec.data[3]);
}

template<typename T>
inline bool Vector4<T>::operator!=(const Vector4<T>& vec) const
{
	return !operator==(vec);
}

template<typename T>
inline bool Vector4<T>::operator<(const Vector4<T>& vec) const
{
	if (data[0] >= vec.data[0]) return false;
	if (data[1] >= vec.data[1]) return false;
	if (data[2] >= vec.data[2]) return false;
	return (data[3] < vec.data[3]);
}

template<typename T>
inline bool Vector4<T>::operator<=(const Vector4<T>& vec) const
{
	if (data[0] > vec.data[0]) return false;
	if (data[1] > vec.data[1]) return false;
	if (data[2] > vec.data[2]) return false;
	return (data[3] <= vec.data[3]);
}

template<typename T>
inline bool Vector4<T>::operator>(const Vector4<T>& vec) const
{
	return !operator<=(vec);
}

template<typename T>
inline bool Vector4<T>::operator>=(const Vector4<T>& vec) const
{
	return !operator<(vec);
}

template<typename T>
inline Vector3<T> Vector4<T>::xyz()
{
	return Vector3<T>(x, y, z);
}

template<typename T>
inline const Vector3<T> Vector4<T>::xyz() const
{
	return Vector3<T>(x, y, z);
}

template<typename T>
inline Vector2<T> Vector4<T>::xy()
{
	return Vector2<T>(x ,y);
}

template<typename T>
inline const Vector2<T> Vector4<T>::xy() const
{
	return Vector2<T>(x, y);
}

template<typename T>
inline Vector2<T> Vector4<T>::xz()
{
	return Vector2<T>(x, z);
}

template<typename T>
inline const Vector2<T> Vector4<T>::xz() const
{
	return Vector2<T>(x, z);
}

template<typename T>
inline Vector2<T> Vector4<T>::yz()
{
	return Vector2<T>(y, z);
}

template<typename T>
inline const Vector2<T> Vector4<T>::yz() const
{
	return Vector2<T>(y, z);
}

template<typename T>
inline Vector2<T> Vector4<T>::zw()
{
	return Vector2<T>(z, w);
}

template<typename T>
inline const Vector2<T> Vector4<T>::zw() const
{
	return Vector2<T>(z, w);
}

template<typename T>
inline T Vector4<T>::dotProduct(const Vector4<T>& v) const
{
	return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2] + data[3] * v.data[3];
}

template<typename T>
inline T Vector4<T>::dotProduct(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return v1.data[0] * v2.data[0] + v1.data[1] * v2.data[1] + v1.data[2] * v2.data[2] + v1.data[3] * v2.data[3];
}

template<typename T>
inline T Vector4<T>::getSquaredLength() const
{
	return dotProduct(*this);
}

template<typename T>
inline T Vector4<T>::getLength() const
{
	return std::sqrt(getSquaredLength());
}

template<typename T>
inline T Vector4<T>::getSquaredDistance(const Vector4<T>& v)
{
	return (*this - v).getSquaredLength();
}

template<typename T>
inline T Vector4<T>::getSquaredDistance(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return (v1 - v2).getSquaredLength();
}

template<typename T>
inline T Vector4<T>::getDistance(const Vector4<T>& v)
{
	return std::sqrt(getSquaredDistance(v));
}

template<typename T>
inline T Vector4<T>::getDistance(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return std::sqrt(getSquaredDistance(v1, v2));
}

template<typename T>
inline Vector4<T>& Vector4<T>::setLength(const T& length, T* oldLength)
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
	data[3] *= factor;
	return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::normalize(T* oldLength)
{
	return setLength(T(1), oldLength);
}

template<typename T>
inline Vector4<T> Vector4<T>::normalized(T* oldLength) const
{
	return Vector4<T>(*this).normalize(oldLength);
}

template<typename T>
inline Vector3<T> Vector4<T>::crossProduct(const Vector4<T>& v) const
{
	return Vector3<T>(data[1] * v.data[2] - data[2] * v.data[1], data[2] * v.data[0] - data[0] * v.data[2], data[0] * v.data[1] - data[1] * v.data[0]);
}

template<typename T>
inline Vector3<T> Vector4<T>::crossProduct(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector3<T>(v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1], v1.data[2] * v2.data[0] - v1.data[0] * v2.data[2], v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]);
}

template<typename T>
inline Vector4<T> Vector4<T>::lerp(const Vector4<T>& v1, const Vector4<T>& v2, const T& percent)
{
	const T one_minus_percent = T(1) - percent;
	return Vector4<T>(one_minus_percent * v1.data[0] + percent * v2.data[0], one_minus_percent * v1.data[1] + percent * v2.data[1], one_minus_percent * v1.data[2] + percent * v2.data[2], one_minus_percent * v1.data[3] + percent * v2.data[3]);
}

template<typename T>
inline Vector4<T>& Vector4<T>::maximize(const Vector4<T>& v)
{
	if (v.data[0] > data[0]) data[0] = v.data[0];
	if (v.data[1] > data[1]) data[1] = v.data[1];
	if (v.data[2] > data[2]) data[2] = v.data[2];
	if (v.data[3] > data[3]) data[3] = v.data[3];
	return *this;
}

template<typename T>
inline Vector4<T> Vector4<T>::maximum(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector4<T>(std::max(v1.data[0], v2.data[0]), std::max(v1.data[1], v2.data[1]), std::max(v1.data[2], v2.data[2]), std::max(v1.data[3], v2.data[3]));
}

template<typename T>
inline Vector4<T>& Vector4<T>::minimize(const Vector4<T>& v)
{
	if (v.data[0] < data[0]) data[0] = v.data[0];
	if (v.data[1] < data[1]) data[1] = v.data[1];
	if (v.data[2] < data[2]) data[2] = v.data[2];
	if (v.data[3] < data[3]) data[3] = v.data[3];
	return *this;
}

template<typename T>
inline Vector4<T> Vector4<T>::minimum(const Vector4<T>& v1, const Vector4<T>& v2)
{
	return Vector4<T>(std::min(v1.data[0], v2.data[0]), std::min(v1.data[1], v2.data[1]), std::min(v1.data[2], v2.data[2]), std::min(v1.data[3], v2.data[3]));
}

template<typename T>
inline Vector4<T>& Vector4<T>::makeUnit()
{
	return set(T(1), T(1), T(1), T(1));
}

template<typename T>
inline Vector4<T>& Vector4<T>::makeUnitX()
{
	return set(T(1), T(0), T(0), T(0));
}

template<typename T>
inline Vector4<T>& Vector4<T>::makeUnitY()
{
	return set(T(0), T(1), T(0), T(0));
}

template<typename T>
inline Vector4<T>& Vector4<T>::makeUnitZ()
{
	return set(T(0), T(0), T(1), T(0));
}

template<typename T>
inline Vector4<T>& Vector4<T>::makeUnitW()
{
	return set(T(0), T(0), T(0), T(1));
}

template<typename T>
inline Vector4<T>& Vector4<T>::makeZero()
{
	return set(T(0), T(0), T(0), T(0));
}

template<typename T>
inline Vector4<T> Vector4<T>::unit()
{
	return Vector4<T>(T(1), T(1), T(1), T(1));
}

template<typename T>
inline Vector4<T> Vector4<T>::unitX()
{
	return Vector4<T>(T(1), T(0), T(0), T(0));
}

template<typename T>
inline Vector4<T> Vector4<T>::unitY()
{
	return Vector4<T>(T(0), T(1), T(0), T(0));
}

template<typename T>
inline Vector4<T> Vector4<T>::unitZ()
{
	return Vector4<T>(T(0), T(0), T(1), T(0));
}

template<typename T>
inline Vector4<T> Vector4<T>::unitW()
{
	return Vector4<T>(T(0), T(0), T(0), T(1));
}

template<typename T>
inline Vector4<T> Vector4<T>::zero()
{
	return Vector4<T>(T(0), T(0), T(0), T(0));
}

template<typename T>
inline Vector4<T> operator*(const T& scale, const Vector4<T>& vector)
{
	return vector * scale;
}

typedef Vector4<float>			Vector4f;
typedef Vector4<double>			Vector4d;
typedef Vector4<int>			Vector4i;
typedef Vector4<unsigned int>	Vector4u;

typedef Vector4f vec4; // GLSL-like

} // namespace nu

#endif // NU_VECTOR4_HPP