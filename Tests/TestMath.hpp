#ifndef NU_TESTMATH_HPP
#define NU_TESTMATH_HPP

#include "../Sources/Math/Utilities.hpp"
#include "../Sources/Math/Trigonometry.hpp"
#include "../Sources/Math/Vector2.hpp"
#include "../Sources/Math/Vector3.hpp"
#include "../Sources/Math/Vector4.hpp"
#include "../Sources/Math/Matrix3.hpp"
#include "../Sources/Math/Matrix4.hpp"
#include "../Sources/Math/Quaternion.hpp"
#include "../Sources/Math/Random.hpp"
#include "../Sources/Math/Noise.hpp"
#include "../Sources/Math/AABB.hpp"
#include "../Sources/Math/Plane.hpp"
#include "../Sources/Math/Ray.hpp"
#include "../Sources/Math/Rect.hpp"
#include "../Sources/Math/Sphere.hpp"
#include "../Sources/Math/OBB.hpp"
#include "../Sources/Math/Intersection.hpp"
#include "../Sources/Math/Frustum.hpp"

#include "../Sources/System/UnitTest.hpp"

BEGIN_TEST(Math)
{

TEST("Utilities")
{
	CHECK(nu::floor(2.0f) == 2);
	CHECK(nu::ceil(2.0f) == 2);
	CHECK(nu::floor(2.4f) == 2);
	CHECK(nu::ceil(2.4f) == 3);
	CHECK(nu::floor(-2.7f) == -3);
	CHECK(nu::ceil(-2.7f) == -2);
	CHECK(nu::floor(-2.0f) == -2);
	CHECK(nu::ceil(-2.0f) == -2);
	CHECK(nu::clamp(50, 0, 10) == 10);
	CHECK(nu::clamp(50, 0, 100) == 50);
	CHECK(nu::clamp(50, 100, 1000) == 100);
	CHECK(nu::inRange(50, 0, 100));
	CHECK(nu::equals(50.0000f, 50.0001f, 0.001f));
	// TODO : Improve tests ?
}

TEST("Trigonometry")
{
	CHECK(nu::equals(nu::cos(90.0f), 0.0f));
	CHECK(nu::equals(nu::cos(0.0f), 1.0f));
	CHECK(nu::equals(nu::sin(90.0f), 1.0f));
	CHECK(nu::equals(nu::sin(0.0f), 0.0f));
	CHECK(nu::equals(nu::sqrt(1.0f), 1.0f));
	CHECK(nu::equals(nu::sqrt(4.0f), 2.0f));
	CHECK(nu::equals(nu::sqrt(9.0f), 3.0f));
	CHECK(nu::equals(nu::sqrt(16.0f), 4.0f));
	// TODO : Improve tests
}

TEST("Vector2")
{
	nu::Vector2i vi;
	vi.x = 2;
	vi.y = 3;
	nu::Vector2f vf1(vi);
	nu::Vector2f vf2(vf1);
	CHECK(nu::equals(vf1.x, vf2.x) && nu::equals(vf1.x, 2.f));
	CHECK(nu::equals(vf1.y, vf2.y) && nu::equals(vf1.y, 3.f));
	CHECK(nu::equalsVector(vf1, vf2));
	CHECK(vf1 == vf2);
	nu::Vector2f vf3(4.0f);
	CHECK(nu::equals(vf3.x, 4.f));
	CHECK(nu::equals(vf3.y, 4.f));
	CHECK(nu::equals(vf3[0], 4.f));
	CHECK(nu::equals(vf3(0), 4.f));
	CHECK(vf3 == nu::Vector2f(4.0f, 4.0f));
	CHECK(nu::equalsVector(vf3, nu::Vector2f(4.0f, 4.0f)));
	CHECK(vf1.set(vf2) == vf2);
	CHECK(vf1.set(vi) == nu::Vector2f(vi));
	CHECK(vf1.set(4.0f) == nu::Vector2f(4.0f));
	CHECK(vf1.set(2.0f, 3.0f) == nu::Vector2f(2.0f, 3.0f));
	nu::Vector2f v1(3.0f, 7.0f);
	nu::Vector2f v2(5.0f, 11.0f);
	CHECK(v1 == (+v1));
	CHECK(-(v1.x) == (-v1).x);
	CHECK(-(v1.y) == (-v1).y);
	CHECK(v1 + v2 == nu::Vector2f(8.0f, 18.0f));
	CHECK(v1 - v2 == nu::Vector2f(-2.0f, -4.0f));
	CHECK(v1 * v2 == nu::Vector2f(15.0f, 77.0f));
	CHECK(v1 / v2 == nu::Vector2f(3.0f / 5.0f, 7.0f / 11.0f));
	CHECK(v1 + 2.0f == nu::Vector2f(5.0f, 9.0f));
	CHECK(v1 - 2.0f == nu::Vector2f(1.0f, 5.0f));
	CHECK(v1 * 2.0f == nu::Vector2f(6.0f, 14.0f));
	CHECK(v1 / 2.0f == nu::Vector2f(1.5f, 3.5f));
	CHECK(1.0f - v1 == nu::Vector2f(-2.0f, -6.0f));
	CHECK(1.0f / v1 == nu::Vector2f(1.0f / 3.0f, 1.0f / 7.0f));
	CHECK(!v1.isZero());
	CHECK(nu::Vector2f::zero.isZero());
	v1 += v2;
	v1 -= v2;
	CHECK(v1 == nu::Vector2f(3.0f, 7.0f));
	v1 *= v2;
	v1 /= v2;
	CHECK(v1 == nu::Vector2f(3.0f, 7.0f));
	v1 += 4.0f;
	v1 -= 4.0f;
	CHECK(v1 == nu::Vector2f(3.0f, 7.0f));
	v1 *= 4.0f;
	v1 /= 4.0f;
	CHECK(v1 == nu::Vector2f(3.0f, 7.0f));
	CHECK(v1 < v2);
	CHECK(v2 > v1);
	CHECK(v1 <= v2);
	CHECK(v2 >= v1);
	CHECK(nu::equals(v1.dotProduct(v2), 92.0f));
	CHECK(nu::equals(v2.dotProduct(v1), 92.0f));
	CHECK(nu::equals(nu::Vector2f::dotProduct(v1, v2), 92.0f));
	CHECK(nu::equals(nu::Vector2f::dotProduct(v2, v1), 92.0f));
	CHECK(nu::equals(nu::dot(v1, v2), 92.0f));
	CHECK(nu::equals(nu::dot(v2, v1), 92.0f));
	CHECK(nu::equals(v1.getSquaredLength(), 58.0f));
	CHECK(nu::equals(v2.getSquaredLength(), 146.0f));
	CHECK(nu::equals(v1.getLength(), nu::sqrt(58.0f)));
	CHECK(nu::equals(v2.getLength(), nu::sqrt(146.0f)));
	v1.setLength(3.0f);
	v2.setLength(5.0f);
	CHECK(nu::equals(v1.getLength(), 3.0f));
	CHECK(nu::equals(v2.getLength(), 5.0f, 0.000001f));
	CHECK(nu::equalsVector(v1, nu::Vector2f(9.0f / nu::sqrt(58.0f), 21.0f / nu::sqrt(58.0f)), 0.000001f));
	CHECK(nu::equalsVector(v2, nu::Vector2f(25.000f / nu::sqrt(146.000f), 55.000f / nu::sqrt(146.000f)), 0.000001f));
	v1.normalize();
	v2.normalize();
	CHECK(nu::equalsVector(v1, nu::Vector2f(3.0f / nu::sqrt(58.0f), 7.0f / nu::sqrt(58.0f)), 0.000001f));
	CHECK(nu::equalsVector(v2, nu::Vector2f(5.0f / nu::sqrt(146.000f), 11.0f / nu::sqrt(146.000f)), 0.000001f));
	v1.setPolarAngle(45.0f);
	CHECK(nu::equals(v1.x, nu::sqrt(2.0f) * 0.5f, 0.000001f));
	CHECK(nu::equals(v1.y, nu::sqrt(2.0f) * 0.5f, 0.000001f));
	CHECK(nu::equals(v1.getPolarAngle(), 45.0f));
	v1.setPolarAngle(0.0f);
	CHECK(nu::equals(v1.x, 1.0f, 0.000001f));
	CHECK(nu::equals(v1.y, 0.0f, 0.000001f));
	CHECK(nu::equals(v1.getPolarAngle(), 0.0f));
	v1.rotate(90.0f);
	CHECK(nu::equals(v1.x, 0.0f, 0.000001f));
	CHECK(nu::equals(v1.y, 1.0f, 0.000001f));
	CHECK(nu::equals(v1.getPolarAngle(), 90.0f));
	v1.set(-50.0f, 50.0f);
	v2.set(50.0f, -50.0f);
	CHECK(nu::equalsVector(nu::Vector2f::lerp(v1, v2, 0.0f), v1));
	CHECK(nu::equalsVector(nu::Vector2f::lerp(v1, v2, 0.25f), nu::Vector2f(-25.0f, 25.0f)));
	CHECK(nu::equalsVector(nu::Vector2f::lerp(v1, v2, 0.5f), nu::Vector2f::zero));
	CHECK(nu::equalsVector(nu::Vector2f::lerp(v1, v2, 0.75f), nu::Vector2f(25.0f, -25.0f)));
	CHECK(nu::equalsVector(nu::Vector2f::lerp(v1, v2, 1.0f), v2));
	v1.set(3.0f, 7.0f);
	v2.set(5.0f, 11.0f);
	CHECK(nu::equalsVector(nu::Vector2f::maximum(v1, v2), v2));
	CHECK(nu::equalsVector(v1.maximize(v2), v2));
	CHECK(nu::equalsVector(nu::Vector2f::minimum(nu::Vector2f(3.0f, 7.0f), v2), nu::Vector2f(3.0f, 7.0f)));
	CHECK(nu::equalsVector(v2.minimize(nu::Vector2f(3.0f, 7.0f)), nu::Vector2f(3.0f, 7.0f)));
}

TEST("Vector3")
{
	nu::Vector3f vec;
	// TODO : From Vec2
}

TEST("Vector4")
{
	nu::Vector4f vec;
	// TODO : From Vec2
}

TEST("Matrix3")
{
	nu::Matrix3f mat;

	// Inverse
	nu::Matrix3f invTest(2, 0, -1, 0, 1, 0, 1, 0, 1);
	nu::Matrix3f invResult(1 / 3.f, 0, 1 / 3.f, 0, 1, 0, -1 / 3.f, 0, 2 / 3.f);
	CHECK(invTest.inversed() == invResult);
	CHECK(invTest.inverse() == invResult);
	CHECK(invResult.inversed().inversed() == invResult);

	// Transpose
	nu::Matrix3f transposeTest(0, 1, 2, 3, 4, 5, 6, 7, 8);
	nu::Matrix3f transposeResult(0, 3, 6, 1, 4, 7, 2, 5, 8);
	CHECK(transposeTest.transposed() == transposeResult);
	CHECK(transposeTest.transpose() == transposeResult);
	CHECK(transposeResult.transposed().transposed() == transposeResult);

	// TODO : Improve tests
}

TEST("Matrix4")
{
	nu::Matrix4f mat;

	// Inverse
	nu::Matrix4f invTest(2, 0, -1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1);
	nu::Matrix4f invResult(1 / 3.f, 0, 1 / 3.f, 0, 0, 1, 0, 0, -1 / 3.f, 0, 2 / 3.f, 0, 0, 0, 0, 1);
	CHECK(invTest.inversed() == invResult);
	CHECK(invTest.inverse() == invResult);
	CHECK(invResult.inversed().inversed() == invResult);

	// Transpose
	nu::Matrix4f transposeTest(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	nu::Matrix4f transposeResult(0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15);
	CHECK(transposeTest.transposed() == transposeResult);
	CHECK(transposeTest.transpose() == transposeResult);
	CHECK(transposeResult.transposed().transposed() == transposeResult);

	// TODO : Improve tests
}

TEST("Quaternion")
{
	nu::Quaternionf quat;
	// TODO : Tests
}

TEST("Random")
{
	I32 min = 0;
	I32 max = 100000000;
	I32 times = 10;

	nu::RandomEngine random1(12345);
	nu::RandomEngine random2(345678376);
	nu::RandomEngine random3(12345);

	for (I32 i = 0; i < times; i++)
	{
		I32 n1 = random1.get(min, max);
		I32 n2 = random2.get(min, max);
		I32 n3 = random3.get(min, max);
		I32 n4 = nu::Random::get(min, max);

		CHECK(n1 == n3);
		CHECK(n1 != n2);
		CHECK(n1 != n4);
	}

	// TODO : Improve tests ?
}

TEST("Noise")
{
	nu::Noise noise;
	for (U32 x = 0; x < 100; x++)
	{
		for (U32 y = 0; y < 100; y++)
		{
			noise.getNoise(x * 0.01f, y * 0.01f);
		}
	}

	// TODO : Improve tests ?
}

TEST("AABB")
{
	nu::AABB box;
	// TODO : Tests
}

TEST("Plane")
{
	nu::Plane plane;
	// TODO : Tests
}

TEST("Ray")
{
	nu::Ray ray;
	// TODO : Tests
}

TEST("Rect")
{
	nu::Rectf rect;
	// TODO : Tests
}

TEST("Sphere")
{
	nu::Sphere sphere;
	// TODO : Tests
}

TEST("OBB")
{
	nu::OBB box;
	// TODO : Tests
}

TEST("Intersection")
{
	// TODO : Tests
}

TEST("Frustum")
{
	nu::Frustum frustum;
	// TODO : Tests
}

}
END_TEST;

#endif // NU_TESTMATH_HPP
