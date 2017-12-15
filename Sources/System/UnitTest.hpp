#ifndef NU_UNITTEST_HPP
#define NU_UNITTEST_HPP

#include <cstdio> // Printf
#include <vector> // Vector

#include "Prerequisites.hpp"

#define RUN_TEST(name) Test##name();

#define BEGIN_TEST(name) void Test##name() { nu::UnitTest unitTest(#name);
#define END_TEST unitTest.print(); }

#define TEST(title) unitTest.start(title);
#define ECHO(format, ...) printf("[%s] ", unitTest.getTitle()); printf(format, __VA_ARGS__); printf("\n");
#define CHECK(expr) unitTest.check(expr, #expr, __FILE__, __LINE__);

namespace nu
{

class UnitTest
{
	public:
		UnitTest(char* name);
		~UnitTest();

		void start(char* title);

		void check(bool passed, const char* expr, const char* file, I32 line);

		void print();

		char* getName();
		char* getTitle();

	private:
		struct Test
		{
			Test(char* pTitle);

			char* title;
			U32 passed;
			U32 failed;
		};

		char* mName;
		char* mCurrentTitle;
		std::vector<Test> mTests;
};

} // namespace nu

#endif // NU_UNITTEST_HPP
