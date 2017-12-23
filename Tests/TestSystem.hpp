#ifndef NU_TESTSYSTEM_HPP
#define NU_TESTSYSTEM_HPP

#include "../Sources/System/Prerequisites.hpp"
#include "../Sources/System/String.hpp"

#include "../Sources/System/UnitTest.hpp"

BEGIN_TEST(System)
{

TEST("Config")
{

}

TEST("DateTime")
{

}

TEST("Enums")
{

}

TEST("Log")
{
	nu::LogManager::initialize();

	CHECK(nu::LogManager::isInitialized());

	LogInfo(nu::LogChannel::Global, 1, "Test %d", nu::LogManager::getLoggerCount());

	nu::FileLogger testLogger("log.txt");

	LogWarning(nu::LogChannel::System, 2, "Test %d", nu::LogManager::getLoggerCount());

	#ifdef NU_COMPILER_MSVC
	nu::VisualStudioLogger logger;
	#endif

	LogError(nu::LogChannel::Math, 3, "Test %d", nu::LogManager::getLoggerCount());
}

TEST("Macros")
{

}

TEST("Platform")
{
	
}

TEST("String")
{
	std::string testToLower = "Test of THE TOLOwer FUNctION";
	nu::toLower(testToLower);
	CHECK(testToLower == "test of the tolower function");
	std::string testToUpper = "Test of THE TOUPper FUNctION";
	nu::toUpper(testToUpper);
	CHECK(testToUpper == "TEST OF THE TOUPPER FUNCTION");

	std::string testSplit1 = "hello,world,itsme";
	std::string testSplit1Res;
	CHECK(nu::split(testSplit1, testSplit1Res, ','));
	CHECK(testSplit1Res == "hello");
	CHECK(testSplit1 == "world,itsme");
	CHECK(nu::split(testSplit1, testSplit1Res, ','));
	CHECK(testSplit1Res == "world");
	CHECK(testSplit1 == "itsme");
	CHECK(!nu::split(testSplit1, testSplit1Res, ','));
	std::string testSplit2 = "hello==world==itsme";
	std::string testSplit2Res;
	CHECK(nu::split(testSplit2, testSplit2Res, "=="));
	CHECK(testSplit2Res == "hello");
	CHECK(testSplit2 == "world==itsme");
	CHECK(nu::split(testSplit2, testSplit2Res, "=="));
	CHECK(testSplit2Res == "world");
	CHECK(testSplit2 == "itsme");
	CHECK(!nu::split(testSplit2, testSplit2Res, "=="));

	std::string testContains = "Hello world !";
	CHECK(nu::contains(testContains, 'd'));
	CHECK(!nu::contains(testContains, 'a'));
	CHECK(nu::contains(testContains, "o w"));
	CHECK(!nu::contains(testContains, "ed"));

	std::string giantString = "This is the test of this function called : limitSize";
	std::string smallString = "Hello !";
	std::string storeString1;
	std::string storeString2;
	CHECK(nu::limitSize(giantString, storeString1, 10));
	CHECK(!nu::limitSize(smallString, storeString2, 10));
	CHECK(storeString1 == "This is th");
	CHECK(storeString2 == "Hello !");
	CHECK(nu::limitSize(giantString, 10));
	CHECK(!nu::limitSize(smallString, 10));
	CHECK(giantString == "This is th");
	CHECK(smallString == "Hello !");

	std::string testTrimWhitespace = "   \t   \t Hello world !   \t   \t   ";
	nu::trimWhitespace(testTrimWhitespace);
	CHECK(testTrimWhitespace == "Hello world !");

	std::string testEmpty = "";
	std::string testNonEmpty = "a";
	CHECK(nu::empty(testEmpty));
	CHECK(!nu::empty(testNonEmpty));

	std::string testBoolString;
	testBoolString = nu::toBoolString(true);
	CHECK(testBoolString == "true");
	testBoolString = nu::toBoolString(false);
	CHECK(testBoolString == "false");

	std::string testToString;
	testToString = nu::toString("test");
	CHECK(testToString == "test");
	testToString = nu::toString(true);
	CHECK(testToString == "1");
	testToString = nu::toString(false);
	CHECK(testToString == "0");
	testToString = nu::toString('c');
	CHECK(testToString == "c");
	testToString = nu::toString(2.3f);
	CHECK(testToString == "2.3");
	testToString = nu::toString(234);
	CHECK(testToString == "234");
	testToString = nu::toString(-234);
	CHECK(testToString == "-234");

	std::string testFromString = nu::fromString<std::string>("test");
	CHECK(testFromString == "test");
	bool testFromStringBool = nu::fromString<bool>("true");
	CHECK(testFromStringBool == true);
	testFromStringBool = nu::fromString<bool>("false");
	CHECK(testFromStringBool == false);
	testFromStringBool = nu::fromString<bool>("1");
	CHECK(testFromStringBool == true);
	testFromStringBool = nu::fromString<bool>("0");
	CHECK(testFromStringBool == false);
	testFromStringBool = nu::fromString<bool>("x");
	CHECK(testFromStringBool == false);
	char testFromStringChar = nu::fromString<char>("t");
	CHECK(testFromStringChar == 't');
	F32 testFromStringF32 = nu::fromString<F32>("2.3");
	CHECK(testFromStringF32 == 2.3f);
	U32 testFromStringU32 = nu::fromString<U32>("234");
	CHECK(testFromStringU32 == 234);
	I32 testFromStringI32 = nu::fromString<I32>("-234");
	CHECK(testFromStringI32 == -234);

	nu::StringId id1 = nu::StringId::hash("Test", false);
	nu::StringId id2 = nu::StringId::hash("Test2", true);
	nu::StringId id3;

	U32 hRuntime = nu::StringId::hashRuntime("Test");
	U32 hCompile = nu::StringId::hashCompile("Test");

	CHECK(hRuntime == hCompile);

	CHECK(id1.isValid());
	CHECK(id2.isValid());
	CHECK(!id3.isValid());

	CHECK(id1 == hRuntime);
	CHECK(id1 == hCompile);

	CHECK(id1 != id2);
	CHECK(id1 != id3);
	CHECK(id2 != id3);

	CHECK(!id1.isStored());
	CHECK(id2.isStored());

	std::string testStorage;
	CHECK(!id1.getString(testStorage));
	CHECK(id2.getString(testStorage));
}

TEST("Time")
{

}

}
END_TEST;

#endif // NU_TESTSYSTEM_HPP
