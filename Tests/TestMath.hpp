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
	CHECK(nu::equals(50.0000f, 50.0001f, 0.01f));
}

TEST("Trigonometry")
{
	CHECK(nu::equals(nu::cos(90.0f), 0.0f));
	CHECK(nu::equals(nu::cos(0.0f), 1.0f));
	CHECK(nu::equals(nu::sin(90.0f), 1.0f));
	CHECK(nu::equals(nu::sin(0.0f), 0.0f));
}

TEST("Vector2")
{
	nu::Vector2f vec;
}

TEST("Vector3")
{
	nu::Vector3f vec;
}

TEST("Vector4")
{
	nu::Vector4f vec;
}

TEST("Matrix3")
{
	nu::Matrix3f mat;
}

TEST("Matrix4")
{
	nu::Matrix4f mat;
}

TEST("Quaternion")
{
	nu::Quaternionf quat;
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
}

}
END_TEST;

#endif // NU_TESTMATH_HPP
