#include <cstdio>
#include <iostream>

#include "TestSystem.hpp"
#include "TestMath.hpp"
#include "TestApplication.hpp"
#include "TestGraphics.hpp"

int main()
{
	RUN_TEST(System);
	RUN_TEST(Math);
	RUN_TEST(Application);
	RUN_TEST(Graphics);

	getchar();
	return 0;
}
