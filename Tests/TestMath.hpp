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

#include "../Sources/System/UnitTest.hpp"

BEGIN_TEST(Math)
{

TEST("Utilities")
{
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


	nu::Matrix3f m(0, 1, 2, 3, 4, 5, 6, 7, 8);
	
	ECHO("m(1, 0) = %f, (r,c)", m(1, 0));
	ECHO("m(0, 1) = %f, (r,c)", m(0, 1));


}

TEST("Matrix4")
{
	nu::Matrix4f mat;
}

TEST("Quaternion")
{
	nu::Quaternionf quat;

}

}
END_TEST;

#endif // NU_TESTMATH_HPP
