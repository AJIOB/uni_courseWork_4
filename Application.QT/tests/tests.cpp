#include <gtest/gtest.h>

TEST(CheckTestsToWork, Hello)
{
	EXPECT_EQ("Hello", "Hello");
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
