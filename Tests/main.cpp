#include <cstdio>
#include <iostream>

#include "../Sources/System/Prerequisites.hpp"

int main()
{
	std::string test;

	nu::LogManager::initialize();

	LogInfo(nu::LogChannel::Global, 1, "Test %d", nu::LogManager::getLoggerCount());

	getchar();
	return 0;
}
