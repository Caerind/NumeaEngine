#ifndef NU_MATRIX4_HPP
#define NU_MATRIX4_HPP

#include "Quaternion.hpp"

namespace nu
{

template <typename T>
class Matrix4
{
	public:
		static const I32 rows = 4;
		static const I32 columns = 4;
		static const I32 elements = 16;

		inline Matrix4();
		inline Matrix4(const Matrix4<T>& m);
		template <typename U>
		explicit inline Matrix4(const Matrix4<U>& m);
		explicit inline Matrix4(const T& s);
		explicit inline Matrix4(const T* a);
		inline Matrix4(const T& a11, const T& a12, const T& a13, const T& a14, const T& a21, const T& a22, const T& a23, const T& a24, const T& a31, const T& a32, const T& a33, const T& a34, const T& a41, const T& a42, const T& a43, const T& a44);
		~Matrix4() = default;

		inline Matrix4<T>& set(const Matrix4<T>& m);
		template <typename U>
		inline Matrix4<T>& set(const Matrix4<U>& m);
		inline Matrix4<T>& set(const T& s);
		inline Matrix4<T>& set(const T* a);
		inline Matrix4<T>& set(const T& a11, const T& a12, const T& a13, const T& a14, const T& a21, const T& a22, const T& a23, const T& a24, const T& a31, const T& a32, const T& a33, const T& a34, const T& a41, const T& a42, const T& a43, const T& a44);
		
		inline T& operator[](U32 i);
		inline const T& operator[](U32 i) const;
		inline T& operator()(U32 row, U32 column);
		inline const T& operator()(U32 row, U32 column) const;

		inline Vector4<T> getColumn(U32 i) const;
		inline Vector4<T> getRow(U32 j) const;

		inline Matrix4<T>& operator=(const Matrix4<T>& m);
		inline const Matrix4<T>& operator+() const;
		inline Matrix4<T> operator-() const;

		inline Matrix4<T> operator+(const Matrix4<T>& m) const;
		inline Matrix4<T> operator-(const Matrix4<T>& m) const;
		inline Matrix4<T> operator*(const Matrix4<T>& m) const;
		inline Matrix4<T>& operator+=(const Matrix4<T>& m);
		inline Matrix4<T>& operator-=(const Matrix4<T>& m);
		inline Matrix4<T>& operator*=(const Matrix4<T>& m);

		inline Matrix4<T> operator+(const T& s) const;
		inline Matrix4<T> operator-(const T& s) const;
		inline Matrix4<T> operator*(const T& s) const;
		inline Matrix4<T> operator/(const T& s) const;
		inline Matrix4<T>& operator+=(const T& s);
		inline Matrix4<T>& operator-=(const T& s);
		inline Matrix4<T>& operator*=(const T& s);
		inline Matrix4<T>& operator/=(const T& s);

		// Operators* with Vector are defined below, outside the class
		// As we use row-major Matrix, we use the form : vector * matrix
		// I don't want to use the matrix * vector form to avoid errors maybe I'll review this later if needed
		// But I'll provide the "trasnformVector" function below to help users but that way they'll know what they're doing 

		inline Vector3<T> transformVector(const Vector3<T>& v1) const;

		inline bool operator==(const Matrix4<T>& m) const;
		inline bool operator!=(const Matrix4<T>& m) const;

		inline Quaternion<T> getRotation() const;
		inline Vector3<T> getScale() const;
		inline Vector3<T> getTranslation() const;

		inline bool hasNegativeScale() const;
		inline bool hasScale() const;
		inline bool isAffine() const;
		inline bool isIdentity() const;

		inline T getTrace() const;
		inline T getDeterminant() const;

		inline Matrix4<T>& inverse(bool* succeeded = nullptr);
		inline Matrix4<T> inversed(bool* succeeded = nullptr) const;

		inline Matrix4<T>& transpose();
		inline Matrix4<T> transposed() const;

		inline Matrix4<T>& setRotation(const Quaternion<T>& rotation);
		inline Matrix4<T>& setScale(const Vector3<T>& scale);
		inline Matrix4<T>& setTranslation(const Vector3<T>& translation);

		inline Matrix4<T>& applyRotation(const Quaternion<T>& rotation);
		inline Matrix4<T>& applyScale(const Vector3<T>& scale);
		inline Matrix4<T>& applyTranslation(const Vector3<T>& translation);

		inline Matrix4<T> rotated(const Quaternion<T>& rotation);
		inline Matrix4<T> scaled(const Vector3<T>& scale);
		inline Matrix4<T> translated(const Vector3<T>& translation);
		inline Matrix4<T> transformed(const Vector3<T>& translation, const Quaternion<T>& rotation);
		inline Matrix4<T> transformed(const Vector3<T>& translation, const Quaternion<T>& rotation, const Vector3<T>& scale);

		inline Matrix4<T>& makeRotation(const Quaternion<T>& rotation);
		inline Matrix4<T>& makeScale(const Vector3<T>& scale);
		inline Matrix4<T>& makeTranslation(const Vector3<T>& translation);
		inline Matrix4<T>& makeTransform(const Vector3<T>& translation, const Quaternion<T>& rotation);
		inline Matrix4<T>& makeTransform(const Vector3<T>& translation, const Quaternion<T>& rotation, const Vector3<T>& scale);

		inline Matrix4<T>& makeViewMatrix(const Vector3<T>& translation, const Quaternion<T>& rotation);
		inline Matrix4<T>& makeLookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up = Vector3<T>::up());
		inline Matrix4<T>& makeOrtho(const T& left, const T& right, const T& top, const T& bottom, const T& zNear, const T& zFar);
		inline Matrix4<T>& makeOrtho(const T& width, const T& height, const T& zNear, const T& zFar);
		inline Matrix4<T>& makePerspective(const T& angle, const T& ratio, const T& zNear, const T& zFar);

		inline Matrix4<T>& makeZero();
		inline Matrix4<T>& makeIdentity();

		static inline Matrix4<T> rotation(const Quaternion<T>& rotation);
		static inline Matrix4<T> scale(const Vector3<T>& scale);
		static inline Matrix4<T> translation(const Vector3<T>& translation);
		static inline Matrix4<T> transform(const Vector3<T>& translation, const Quaternion<T>& rotation);
		static inline Matrix4<T> transform(const Vector3<T>& translation, const Quaternion<T>& rotation, const Vector3<T>& scale);

		static inline Matrix4<T> viewMatrix(const Vector3<T>& translation, const Quaternion<T>& rotation);
		static inline Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up = Vector3<T>::up());
		static inline Matrix4<T> ortho(const T& left, const T& right, const T& top, const T& bottom, const T& zNear, const T& zFar);
		static inline Matrix4<T> ortho(const T& width, const T& height, const T& zNear, const T& zFar);
		static inline Matrix4<T> perspective(const T& angle, const T& ratio, const T& zNear, const T& zFar);

		static inline Matrix4<T> zero();
		static inline Matrix4<T> identity();

		union
		{
			T data[16];
			T m[4][4];
		};
};

template <typename T>
Vector3<T> operator*(const Vector3<T>& vector, const Matrix4<T>& matrix);

template <typename T>
Vector3<T>& operator*=(Vector3<T>& vector, const Matrix4<T>& matrix);

template<typename T>
inline Matrix4<T>::Matrix4()
{
	set(zero());
}

template<typename T>
inline Matrix4<T>::Matrix4(const Matrix4<T>& m)
{
	std::memcpy(data, m.data, 16 * sizeof(T));
}

template<typename T>
template<typename U>
inline Matrix4<T>::Matrix4(const Matrix4<U>& m)
{
	data[0] = T(m.data[0]);
	data[1] = T(m.data[1]);
	data[2] = T(m.data[2]);
	data[3] = T(m.data[3]);
	data[4] = T(m.data[4]);
	data[5] = T(m.data[5]);
	data[6] = T(m.data[6]);
	data[7] = T(m.data[7]);
	data[8] = T(m.data[8]);
	data[9] = T(m.data[9]);
	data[10] = T(m.data[10]);
	data[11] = T(m.data[11]);
	data[12] = T(m.data[12]);
	data[13] = T(m.data[13]);
	data[14] = T(m.data[14]);
	data[15] = T(m.data[15]);
}

template<typename T>
inline Matrix4<T>::Matrix4(const T& s)
{
	data[0] = s;
	data[1] = s;
	data[2] = s;
	data[3] = s;
	data[4] = s;
	data[5] = s;
	data[6] = s;
	data[7] = s;
	data[8] = s;
	data[9] = s;
	data[10] = s;
	data[11] = s;
	data[12] = s;
	data[13] = s;
	data[14] = s;
	data[15] = s;
}

template<typename T>
inline Matrix4<T>::Matrix4(const T* a)
{
	std::memcpy(data, a, 16 * sizeof(T));
}

template<typename T>
inline Matrix4<T>::Matrix4(const T& a11, const T& a12, const T& a13, const T& a14, const T& a21, const T& a22, const T& a23, const T& a24, const T& a31, const T& a32, const T& a33, const T& a34, const T& a41, const T& a42, const T& a43, const T& a44)
{
	data[0] = a11;
	data[1] = a12;
	data[2] = a13;
	data[3] = a14;
	data[4] = a21;
	data[5] = a22;
	data[6] = a23;
	data[7] = a24;
	data[8] = a31;
	data[9] = a32;
	data[10] = a33;
	data[11] = a34;
	data[12] = a41;
	data[13] = a42;
	data[14] = a43;
	data[15] = a44;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::set(const Matrix4<T>& m)
{
	std::memcpy(data, m.data, 16 * sizeof(T));
	return *this;
}

template<typename T>
template<typename U>
inline Matrix4<T>& Matrix4<T>::set(const Matrix4<U>& m)
{
	data[0] = T(m.data[0]);
	data[1] = T(m.data[1]);
	data[2] = T(m.data[2]);
	data[3] = T(m.data[3]);
	data[4] = T(m.data[4]);
	data[5] = T(m.data[5]);
	data[6] = T(m.data[6]);
	data[7] = T(m.data[7]);
	data[8] = T(m.data[8]);
	data[9] = T(m.data[9]);
	data[10] = T(m.data[10]);
	data[11] = T(m.data[11]);
	data[12] = T(m.data[12]);
	data[13] = T(m.data[13]);
	data[14] = T(m.data[14]);
	data[15] = T(m.data[15]);
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::set(const T& s)
{
	data[0] = s;
	data[1] = s;
	data[2] = s;
	data[3] = s;
	data[4] = s;
	data[5] = s;
	data[6] = s;
	data[7] = s;
	data[8] = s;
	data[9] = s;
	data[10] = s;
	data[11] = s;
	data[12] = s;
	data[13] = s;
	data[14] = s;
	data[15] = s;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::set(const T* a)
{
	std::memcpy(data, a, 16 * sizeof(T));
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::set(const T& a11, const T& a12, const T& a13, const T& a14, const T& a21, const T& a22, const T& a23, const T& a24, const T& a31, const T& a32, const T& a33, const T& a34, const T& a41, const T& a42, const T& a43, const T& a44)
{
	data[0] = a11;
	data[1] = a12;
	data[2] = a13;
	data[3] = a14;
	data[4] = a21;
	data[5] = a22;
	data[6] = a23;
	data[7] = a24;
	data[8] = a31;
	data[9] = a32;
	data[10] = a33;
	data[11] = a34;
	data[12] = a41;
	data[13] = a42;
	data[14] = a43;
	data[15] = a44;
	return *this;
}

template<typename T>
inline T& Matrix4<T>::operator[](U32 i)
{
	return data[i];
}

template<typename T>
inline const T& Matrix4<T>::operator[](U32 i) const
{
	return data[i];
}

template<typename T>
inline T& Matrix4<T>::operator()(U32 row, U32 column)
{
	return data[column + rows * row];
}

template<typename T>
inline const T& Matrix4<T>::operator()(U32 row, U32 column) const
{
	return data[column + rows * row];
}

template<typename T>
inline Vector4<T> Matrix4<T>::getColumn(U32 i) const
{
	return Vector4<T>(data[i + rows * 0], data[i + rows * 1], data[i + rows * 2], data[i + rows * 3]);
}

template<typename T>
inline Vector4<T> Matrix4<T>::getRow(U32 j) const
{
	return Vector4<T>(data[0 + rows * i], data[1 + rows * i], data[2 + rows * i], data[3 + rows * i]);
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& m)
{
	std::memcpy(data, m.data, sizeof(*this));
	return *this;
}

template<typename T>
inline const Matrix4<T>& Matrix4<T>::operator+() const
{
	return *this;
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator-() const
{
	return Matrix4<T>(-data[0], -data[1], -data[2], -data[3], -data[4], -data[5], -data[6], -data[7], -data[8], -data[9], -data[10], -data[11], -data[12], -data[13], -data[14], -data[15]);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& m) const
{
	return Matrix4<T>(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], data[3] + m.data[3],
		data[4] + m.data[4], data[5] + m.data[5], data[6] + m.data[6], data[7] + m.data[7],
		data[8] + m.data[8], data[9] + m.data[9], data[10] + m.data[10], data[11] + m.data[11],
		data[12] + m.data[12], data[13] + m.data[13], data[14] + m.data[14], data[15] + m.data[15]);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& m) const
{
	return Matrix4<T>(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], data[3] - m.data[3],
		data[4] - m.data[4], data[5] - m.data[5], data[6] - m.data[6], data[7] - m.data[7],
		data[8] - m.data[8], data[9] - m.data[9], data[10] - m.data[10], data[11] - m.data[11],
		data[12] - m.data[12], data[13] - m.data[13], data[14] - m.data[14], data[15] - m.data[15]);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& m) const
{
	Matrix4<T> out;
	{
		Vector4<T> row(getRow(0));
		out.data[0] = row.dotProduct(m.getColumn(0));
		out.data[4] = row.dotProduct(m.getColumn(1));
		out.data[8] = row.dotProduct(m.getColumn(2));
		out.data[12] = row.dotProduct(m.getColumn(3));
	}
	{
		Vector4<T> row(getRow(1));
		out.data[1] = row.dotProduct(m.getColumn(0));
		out.data[5] = row.dotProduct(m.getColumn(1));
		out.data[9] = row.dotProduct(m.getColumn(2));
		out.data[13] = row.dotProduct(m.getColumn(3));
	}
	{
		Vector4<T> row(getRow(2));
		out.data[2] = row.dotProduct(m.getColumn(0));
		out.data[6] = row.dotProduct(m.getColumn(1));
		out.data[10] = row.dotProduct(m.getColumn(2));
		out.data[14] = row.dotProduct(m.getColumn(3));
	}
	{
		Vector4<T> row(getRow(3));
		out.data[3] = row.dotProduct(m.getColumn(0));
		out.data[7] = row.dotProduct(m.getColumn(1));
		out.data[11] = row.dotProduct(m.getColumn(2));
		out.data[15] = row.dotProduct(m.getColumn(3));
	}
	return out;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& m)
{
	data[0] += m.data[0];
	data[1] += m.data[1];
	data[2] += m.data[2];
	data[3] += m.data[3];
	data[4] += m.data[4];
	data[5] += m.data[5];
	data[6] += m.data[6];
	data[7] += m.data[7];
	data[8] += m.data[8];
	data[9] += m.data[9];
	data[10] += m.data[10];
	data[11] += m.data[11];
	data[12] += m.data[12];
	data[13] += m.data[13];
	data[14] += m.data[14];
	data[15] += m.data[15];
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& m)
{
	data[0] -= m.data[0];
	data[1] -= m.data[1];
	data[2] -= m.data[2];
	data[3] -= m.data[3];
	data[4] -= m.data[4];
	data[5] -= m.data[5];
	data[6] -= m.data[6];
	data[7] -= m.data[7];
	data[8] -= m.data[8];
	data[9] -= m.data[9];
	data[10] -= m.data[10];
	data[11] -= m.data[11];
	data[12] -= m.data[12];
	data[13] -= m.data[13];
	data[14] -= m.data[14];
	data[15] -= m.data[15];
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& m)
{
	Matrix4<T> copy(*this);
	{
		Vector4<T> row(copy.getRow(0));
		data[0] = row.dotProduct(m.getColumn(0));
		data[4] = row.dotProduct(m.getColumn(1));
		data[8] = row.dotProduct(m.getColumn(2));
		data[12] = row.dotProduct(m.getColumn(3));
	}
	{
		Vector4<T> row(copy.getRow(1));
		data[1] = row.dotProduct(m.getColumn(0));
		data[5] = row.dotProduct(m.getColumn(1));
		data[9] = row.dotProduct(m.getColumn(2));
		data[13] = row.dotProduct(m.getColumn(3));
	}
	{
		Vector4<T> row(copy.getRow(2));
		data[2] = row.dotProduct(m.getColumn(0));
		data[6] = row.dotProduct(m.getColumn(1));
		data[10] = row.dotProduct(m.getColumn(2));
		data[14] = row.dotProduct(m.getColumn(3));
	}
	{
		Vector4<T> row(copy.getRow(3));
		data[3] = row.dotProduct(m.getColumn(0));
		data[7] = row.dotProduct(m.getColumn(1));
		data[11] = row.dotProduct(m.getColumn(2));
		data[15] = row.dotProduct(m.getColumn(3));
	}
	return *this;
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator+(const T& s) const
{
	return Matrix4<T>(data[0] + s, data[1] + s, data[2] + s, data[3] + s,
		data[4] + s, data[5] + s, data[6] + s, data[7] + s,
		data[8] + s, data[9] + s, data[10] + s, data[11] + s,
		data[12] + s, data[13] + s, data[14] + s, data[15] + s);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator-(const T& s) const
{
	return Matrix4<T>(data[0] - s, data[1] - s, data[2] - s, data[3] - s,
		data[4] - s, data[5] - s, data[6] - s, data[7] - s,
		data[8] - s, data[9] - s, data[10] - s, data[11] - s,
		data[12] - s, data[13] - s, data[14] - s, data[15] - s);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator*(const T& s) const
{
	return Matrix4<T>(data[0] * s, data[1] * s, data[2] * s, data[3] * s,
		data[4] * s, data[5] * s, data[6] * s, data[7] * s,
		data[8] * s, data[9] * s, data[10] * s, data[11] * s,
		data[12] * s, data[13] * s, data[14] * s, data[15] * s);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator/(const T& s) const
{
	const T inv = 1 / s;
	return Matrix4<T>(data[0] * inv, data[1] * inv, data[2] * inv, data[3] * inv,
		data[4] * inv, data[5] * inv, data[6] * inv, data[7] * inv,
		data[8] * inv, data[9] * inv, data[10] * inv, data[11] * inv,
		data[12] * inv, data[13] * inv, data[14] * inv, data[15] * inv);
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator+=(const T& s)
{
	data[0] += s;
	data[1] += s;
	data[2] += s;
	data[3] += s;
	data[4] += s;
	data[5] += s;
	data[6] += s;
	data[7] += s;
	data[8] += s;
	data[9] += s;
	data[10] += s;
	data[11] += s;
	data[12] += s;
	data[13] += s;
	data[14] += s;
	data[15] += s;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator-=(const T& s)
{
	data[0] -= s;
	data[1] -= s;
	data[2] -= s;
	data[3] -= s;
	data[4] -= s;
	data[5] -= s;
	data[6] -= s;
	data[7] -= s;
	data[8] -= s;
	data[9] -= s;
	data[10] -= s;
	data[11] -= s;
	data[12] -= s;
	data[13] -= s;
	data[14] -= s;
	data[15] -= s;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator*=(const T& s)
{
	data[0] *= s;
	data[1] *= s;
	data[2] *= s;
	data[3] *= s;
	data[4] *= s;
	data[5] *= s;
	data[6] *= s;
	data[7] *= s;
	data[8] *= s;
	data[9] *= s;
	data[10] *= s;
	data[11] *= s;
	data[12] *= s;
	data[13] *= s;
	data[14] *= s;
	data[15] *= s;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::operator/=(const T& s)
{
	const T inv = 1 / s;
	data[0] *= inv;
	data[1] *= inv;
	data[2] *= inv;
	data[3] *= inv;
	data[4] *= inv;
	data[5] *= inv;
	data[6] *= inv;
	data[7] *= inv;
	data[8] *= inv;
	data[9] *= inv;
	data[10] *= inv;
	data[11] *= inv;
	data[12] *= inv;
	data[13] *= inv;
	data[14] *= inv;
	data[15] *= inv;
	return *this;
}

template<typename T>
inline Vector3<T> Matrix4<T>::transformVector(const Vector3<T>& v) const
{
	return Vector3<T>(v.x * data[0] + v.y * data[4] + v.z * data[8], v.x * data[1] + v.y * data[5] + v.z * data[9], v.x * data[2] + v.y * data[6] + v.z * data[10]);
}

template<typename T>
inline bool Matrix4<T>::operator==(const Matrix4<T>& m) const
{
	if (!equals(data[0], m.data[0])) return false;
	if (!equals(data[1], m.data[1])) return false;
	if (!equals(data[2], m.data[2])) return false;
	if (!equals(data[3], m.data[3])) return false;
	if (!equals(data[4], m.data[4])) return false;
	if (!equals(data[5], m.data[5])) return false;
	if (!equals(data[6], m.data[6])) return false;
	if (!equals(data[7], m.data[7])) return false;
	if (!equals(data[8], m.data[8])) return false;
	if (!equals(data[9], m.data[9])) return false;
	if (!equals(data[10], m.data[10])) return false;
	if (!equals(data[11], m.data[11])) return false;
	if (!equals(data[12], m.data[12])) return false;
	if (!equals(data[13], m.data[13])) return false;
	if (!equals(data[14], m.data[14])) return false;
	return equals(data[15], m.data[15]);
}

template<typename T>
inline bool Matrix4<T>::operator!=(const Matrix4<T>& m) const
{
	return !operator==(m);
}

template<typename T>
inline Quaternion<T> Matrix4<T>::getRotation() const
{
	// TODO : Do this algorithm take care of the scale ?

	const T trace = data[0] + data[5] + data[10];
	Quaternion<T> q;

	// Check the diagonal
	if (trace > 0)
	{
		const T s = std::sqrt(trace + T(1));
		q.w = s * T(0.5);

		const T t = T(0.5) / s;
		q.x = (data[9] - data[6]) * t;
		q.y = (data[2] - data[8]) * t;
		q.z = (data[4] - data[1]) * t;

		return q;
	}
	else
	{
		// Diagonal is negative
		int i = 0;
		if (data[5] > data[0]) i = 1;
		if (data[10] > m[i][i]) i = 2;

		static const int next[3] = { 1, 2, 0 };
		int j = next[i];
		int k = next[j];

		const T s = std::sqrt((m[i][j] - (m[j][j] + m[k][k])) + 1);

		q[i] = s * T(0.5);

		const T t = (!equals(s, T(0))) ? T(0.5) / s : s;

		q[3] = (m[k][j] - m[j][k]) * t;
		q[j] = (m[j][i] + m[i][j]) * t;
		q[k] = (m[k][i] + m[i][k]) * t;

		return q;
	}
}

template<typename T>
inline Vector3<T> Matrix4<T>::getScale() const
{
	const T unit = T(1);
	const Vector3<T> scale(data[0] * data[0] + data[1] * data[1] + data[2] * data[2], data[4] * data[4] + data[5] * data[5] + data[6] * data[6], data[8] * data[8] + data[9] * data[9] + data[10] * data[10]);
	if (!equals(unit, scale.x))
	{
		scale.x = std::sqrt(scale.x);
	}
	if (!equals(unit, scale.y))
	{
		scale.y = std::sqrt(scale.y);
	}
	if (!equals(unit, scale.z))
	{
		scale.z = std::sqrt(scale.z);
	}
	return scale;
}

template<typename T>
inline Vector3<T> Matrix4<T>::getTranslation() const
{
	return Vector3<T>(data[12], data[13], data[14]);
}

template<typename T>
inline bool Matrix4<T>::hasNegativeScale() const
{
	return getDeterminant() < F(0);
}

template<typename T>
inline bool Matrix4<T>::hasScale() const
{
	const T unit = T(1);

	T t = data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
	if (!equals(t, unit))
		return true;

	t = data[4] * data[4] + data[5] * data[5] + data[6] * data[6];
	if (!equals(t, unit))
		return true;

	t = data[8] * data[8] + data[9] * data[9] + data[10] * data[10];
	if (!equals(t, unit))
		return true;

	return false;
}

template<typename T>
inline bool Matrix4<T>::isAffine() const
{
	const T zero = T(0);
	if (!equals(data[3], zero)) return false;
	if (!equals(data[7], zero)) return false;
	if (!equals(data[11], zero)) return false;
	return equals(data[15], T(1));
}

template<typename T>
inline bool Matrix4<T>::isIdentity() const
{
	const T unit = T(1);
	const T zero = T(0);

	if (!equals(data[0], unit)) return false;
	if (!equals(data[5], unit)) return false;
	if (!equals(data[10], unit)) return false;
	if (!equals(data[15], unit)) return false;

	if (!equals(data[2], zero)) return false;
	if (!equals(data[3], zero)) return false;
	if (!equals(data[4], zero)) return false;
	if (!equals(data[6], zero)) return false;
	if (!equals(data[7], zero)) return false;
	if (!equals(data[8], zero)) return false;
	if (!equals(data[9], zero)) return false;
	if (!equals(data[11], zero)) return false;
	if (!equals(data[11], zero)) return false;
	if (!equals(data[11], zero)) return false;
	return equals(data[14], zero);
}

template<typename T>
inline T Matrix4<T>::getTrace() const
{
	return data[0] + data[5] + data[10] + data[15];
}

template<typename T>
inline T Matrix4<T>::getDeterminant() const
{
	// We will use the last row of the matrix
	// Because if the matrix is affine it will be faster

	// Compute det2x2
	const T m22m33 = data[5] * data[10] - data[6] * data[9];
	const T m21m33 = data[4] * data[10] - data[8] * data[6];
	const T m21m32 = data[4] * data[9] - data[8] * data[5];

	if (isAffine())
	{
		// If affine, the last row is full of zero except the last one
		// Return the det of the 3x3
		return data[0] * m22m33 - data[1] * m21m33 + data[2] * m21m32; // 9 mul, 5 add
	}
	else
	{
		// Compute det2x2, each det2x2 is used 2 times for the det3
		const T m21m34 = data[4] * data[11] - data[8] * data[7];
		const T m22m34 = data[5] * data[11] - data[9] * data[7];
		const T m23m34 = data[6] * data[11] - data[10] * data[7];

		// Compute det3x3
		const T a = data[1] * m23m34 - data[2] * m22m34 + data[3] * m22m33;
		const T b = data[0] * m23m34 - data[2] * m21m34 + data[3] * m21m33;
		const T c = data[0] * m22m34 - data[1] * m21m34 + data[3] * m21m32;
		const T d = data[0] * m22m33 - data[1] * m21m33 + data[2] * m21m32;

		// Return the det of the 4x4
		return a - b + c - d; // 24 mul, 17 add
	}
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::inverse(bool* succeeded)
{
	const T det = getDeterminant();
	if (equals(det, T(0))
	{
		if (succeeded != nullptr)
		{
			*succeeded = false;
		}
		return *this;
	}

	const T inv[16];

	inv[0] = data[5] * data[10] * data[15] -
		data[5] * data[11] * data[14] -
		data[9] * data[6] * data[15] +
		data[9] * data[7] * data[14] +
		data[13] * data[6] * data[11] -
		data[13] * data[7] * data[10];

	inv[4] = -data[4] * data[10] * data[15] +
		data[4] * data[11] * data[14] +
		data[8] * data[6] * data[15] -
		data[8] * data[7] * data[14] -
		data[12] * data[6] * data[11] +
		data[12] * data[7] * data[10];

	inv[8] = data[4] * data[9] * data[15] -
		data[4] * data[11] * data[13] -
		data[8] * data[5] * data[15] +
		data[8] * data[7] * data[13] +
		data[12] * data[5] * data[11] -
		data[12] * data[7] * data[9];

	inv[12] = -data[4] * data[9] * data[14] +
		data[4] * data[10] * data[13] +
		data[8] * data[5] * data[14] -
		data[8] * data[6] * data[13] -
		data[12] * data[5] * data[10] +
		data[12] * data[6] * data[9];

	inv[1] = -data[1] * data[10] * data[15] +
		data[1] * data[11] * data[14] +
		data[9] * data[2] * data[15] -
		data[9] * data[3] * data[14] -
		data[13] * data[2] * data[11] +
		data[13] * data[3] * data[10];

	inv[5] = data[0] * data[10] * data[15] -
		data[0] * data[11] * data[14] -
		data[8] * data[2] * data[15] +
		data[8] * data[3] * data[14] +
		data[12] * data[2] * data[11] -
		data[12] * data[3] * data[10];

	inv[9] = -data[0] * data[9] * data[15] +
		data[0] * data[11] * data[13] +
		data[8] * data[1] * data[15] -
		data[8] * data[3] * data[13] -
		data[12] * data[1] * data[11] +
		data[12] * data[3] * data[9];

	inv[13] = data[0] * data[9] * data[14] -
		data[0] * data[10] * data[13] -
		data[8] * data[1] * data[14] +
		data[8] * data[2] * data[13] +
		data[12] * data[1] * data[10] -
		data[12] * data[2] * data[9];

	inv[2] = data[1] * data[6] * data[15] -
		data[1] * data[7] * data[14] -
		data[5] * data[2] * data[15] +
		data[5] * data[3] * data[14] +
		data[13] * data[2] * data[7] -
		data[13] * data[3] * data[6];

	inv[6] = -data[0] * data[6] * data[15] +
		data[0] * data[7] * data[14] +
		data[4] * data[2] * data[15] -
		data[4] * data[3] * data[14] -
		data[12] * data[2] * data[7] +
		data[12] * data[3] * data[6];

	inv[10] = data[0] * data[5] * data[15] -
		data[0] * data[7] * data[13] -
		data[4] * data[1] * data[15] +
		data[4] * data[3] * data[13] +
		data[12] * data[1] * data[7] -
		data[12] * data[3] * data[5];

	inv[14] = -data[0] * data[5] * data[14] +
		data[0] * data[6] * data[13] +
		data[4] * data[1] * data[14] -
		data[4] * data[2] * data[13] -
		data[12] * data[1] * data[6] +
		data[12] * data[2] * data[5];

	inv[3] = -data[1] * data[6] * data[11] +
		data[1] * data[7] * data[10] +
		data[5] * data[2] * data[11] -
		data[5] * data[3] * data[10] -
		data[9] * data[2] * data[7] +
		data[9] * data[3] * data[6];

	inv[7] = data[0] * data[6] * data[11] -
		data[0] * data[7] * data[10] -
		data[4] * data[2] * data[11] +
		data[4] * data[3] * data[10] +
		data[8] * data[2] * data[7] -
		data[8] * data[3] * data[6];

	inv[11] = -data[0] * data[5] * data[11] +
		data[0] * data[7] * data[9] +
		data[4] * data[1] * data[11] -
		data[4] * data[3] * data[9] -
		data[8] * data[1] * data[7] +
		data[8] * data[3] * data[5];

	inv[15] = data[0] * data[5] * data[10] -
		data[0] * data[6] * data[9] -
		data[4] * data[1] * data[10] +
		data[4] * data[2] * data[9] +
		data[8] * data[1] * data[6] -
		data[8] * data[2] * data[5];

	const T invDet = 1 / det;
	for (int i = 0; i < 16; i++)
	{
		inv[i] *= invDet;
	}

	if (succeeded != nullptr)
	{
		*succeeded = true;
	}
	set(inv);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::inversed(bool* succeeded) const
{
	return Matrix4<T>(*this).inverse();
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::transpose()
{
	std::swap(data[1], data[4]);
	std::swap(data[2], data[8]);
	std::swap(data[3], data[12]);
	std::swap(data[6], data[9]);
	std::swap(data[7], data[13]);
	std::swap(data[11], data[14]);
	return *this;
}

template<typename T>
inline Matrix4<T> Matrix4<T>::transposed() const
{
	return Matrix4<T>(*this).transpose();
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::setRotation(const Quaternion<T>& rotation)
{
	Vector3<T> currentScale = getScale();
	Quaternion<T> currentRotation = getRotation();

	// TODO : 
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::setScale(const Vector3<T>& scale)
{
	Vector3<T> currentScale = getScale();
	Quaternion<T> currentRotation = getRotation();

	// TODO : 
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::setTranslation(const Vector3<T>& translation)
{
	data[12] = translation.x;
	data[13] = translation.y;
	data[14] = translation.z;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::applyRotation(const Quaternion<T>& rotation)
{
	// TODO:
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::applyScale(const Vector3<T>& scale)
{
	data[0] *= scale.x;
	data[1] *= scale.x;
	data[2] *= scale.x;
	data[4] *= scale.y;
	data[5] *= scale.y;
	data[6] *= scale.y;
	data[8] *= scale.z;
	data[9] *= scale.z;
	data[10] *= scale.z;
	return *this;
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::applyTranslation(const Vector3<T>& translation)
{
	data[12] += translation.x;
	data[13] += translation.y;
	data[14] += translation.z;
	return *this;
}

template<typename T>
inline Matrix4<T> oe::Matrix4<T>::rotated(const Quaternion<T>& rotation)
{
	return Matrix4<T>(*this).applyRotation(rotation);
}

template<typename T>
inline Matrix4<T> oe::Matrix4<T>::scaled(const Vector3<T>& scale)
{
	return Matrix4<T>(*this).applyScale(scale);
}

template<typename T>
inline Matrix4<T> oe::Matrix4<T>::translated(const Vector3<T>& translation)
{
	return Matrix4<T>(*this).applyTranslation(translation);
}

template<typename T>
inline Matrix4<T> oe::Matrix4<T>::transformed(const Vector3<T>& translation, const Quaternion<T>& rotation)
{
	return Matrix4<T>(*this).applyTransform(translation, rotation);
}

template<typename T>
inline Matrix4<T> oe::Matrix4<T>::transformed(const Vector3<T>& translation, const Quaternion<T>& rotation, const Vector3<T>& scale)
{
	return Matrix4<T>(*this).applyTransform(translation, rotation, scale);
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeRotation(const Quaternion<T>& rotation)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeScale(const Vector3<T>& scale)
{
	return set(scale.x, T(0), T(0), T(0),
		T(0), scale.y, T(0), T(0),
		T(0), T(0), scale.z, T(0),
		T(0), T(0), T(0), T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeTranslation(const Vector3<T>& translation)
{
	return set(T(1), T(0), T(0), T(0),
		T(0), T(1), T(0), T(0),
		T(0), T(0), T(1), T(0),
		translation.x, translation.y, translation.z, T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeTransform(const Vector3<T>& translation, const Quaternion<T>& rotation)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeTransform(const Vector3<T>& translation, const Quaternion<T>& rotation, const Vector3<T>& scale)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeViewMatrix(const Vector3<T>& translation, const Quaternion<T>& rotation)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeLookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeOrtho(const T& left, const T& right, const T& top, const T& bottom, const T& zNear, const T& zFar)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeOrtho(const T& width, const T& height, const T& zNear, const T& zFar)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makePerspective(const T& angle, const T& ratio, const T& zNear, const T& zFar)
{
	// TODO:
	return set(T(1));
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeZero()
{
	return set(zero());
}

template<typename T>
inline Matrix4<T>& Matrix4<T>::makeIdentity()
{
	return set(identity());
}

template<typename T>
inline Matrix4<T> Matrix4<T>::rotation(const Quaternion<T>& rotation)
{
	// TODO : More efficient way ?
	return Matrix4<T>().makeRotation(rotation);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::scale(const Vector3<T>& scale)
{
	// TODO : More efficient way ?
	return Matrix4<T>().makeScale(scale);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::translation(const Vector3<T>& translation)
{
	// TODO : More efficient way ?
	return Matrix4<T>().makeTranslation(translation);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::transform(const Vector3<T>& translation, const Quaternion<T>& rotation)
{
	// TODO : More efficient way ?
	return Matrix4<T>().makeTransform(translation, rotation);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::transform(const Vector3<T>& translation, const Quaternion<T>& rotation, const Vector3<T>& scale)
{
	// TODO : More efficient way ?
	return Matrix4<T>().makeTransform(translation, rotation, scale);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::viewMatrix(const Vector3<T>& translation, const Quaternion<T>& rotation)
{
	// TODO:
	return Matrix4<T>();
}

template<typename T>
inline Matrix4<T> Matrix4<T>::lookAt(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up)
{
	// TODO:
	return Matrix4<T>();
}

template<typename T>
inline Matrix4<T> Matrix4<T>::ortho(const T& left, const T& right, const T& top, const T& bottom, const T& zNear, const T& zFar)
{
	// TODO:
	return Matrix4<T>();
}

template<typename T>
inline Matrix4<T> Matrix4<T>::ortho(const T& width, const T& height, const T& zNear, const T& zFar)
{
	// TODO:
	return Matrix4<T>();
}

template<typename T>
inline Matrix4<T> Matrix4<T>::perspective(const T& angle, const T& ratio, const T& zNear, const T& zFar)
{
	// TODO:
	return Matrix4<T>();
}

template<typename T>
inline Matrix4<T> Matrix4<T>::zero()
{
	static Matrix4<T> zeroM(T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0));
	return zeroM;
}

template<typename T>
inline Matrix4<T> Matrix4<T>::identity()
{
	static Matrix4<T> identityM(T(1), T(0), T(0), T(0),
		T(0), T(1), T(0), T(0),
		T(0), T(0), T(1), T(0),
		T(0), T(0), T(0), T(1));
	return identityM;
}

template<typename T>
Vector3<T> operator*(const Vector3<T>& vector, const Matrix4<T>& matrix)
{
	return matrix.transformVector(vector);
}

template<typename T>
Vector3<T>& operator*=(Vector3<T>& vector, const Matrix4<T>& matrix)
{
	const Vector3<T> result = matrix.transformVector(vector);
	return vector.set(result);
}

typedef Matrix4<F32> Matrix4f;

typedef Matrix4f mat4; // GLSL-like

} // namespace nu

#endif // NU_MATRIX4_HPP