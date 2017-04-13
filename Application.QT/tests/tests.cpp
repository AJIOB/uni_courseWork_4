#include <gtest/gtest.h>
#include "ClassHierarchy/Author.h"
#include "ClassHierarchy/Book.h"
#include "ClassHierarchy/BookCopy.h"
#include "ClassHierarchy/User.h"
#include "DBConnector/DBConnector.h"

TEST(CheckTestsToWork, Hello)
{
	EXPECT_EQ("Hello", "Hello");
}

TEST(DB_Work, connectToDB)
{
	DBConnector connector;
	EXPECT_EQ(true, true);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
