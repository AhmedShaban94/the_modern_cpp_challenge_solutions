#include "gtest/gtest.h"
#include "problem_01.h"

TEST(firstTest, testFunc)
{
	ASSERT_EQ("Hello World", Chapter01::testFunc()); 
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
