#include <cstdio>
#include <iostream>

#include "TestSystem.hpp"
#include "TestMath.hpp"

int main()
{
	RUN_TEST(System);
	RUN_TEST(Math);

	getchar();
	return 0;
}
