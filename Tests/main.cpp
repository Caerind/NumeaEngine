#include <cstdio>
#include <iostream>

#include "TestSystem.hpp"
#include "TestMath.hpp"
#include "TestApplication.hpp"

int main()
{
	RUN_TEST(System);
	RUN_TEST(Math);
	RUN_TEST(Application);

	getchar();
	return 0;
}
