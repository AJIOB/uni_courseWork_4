#define GTEST

#include "DB_Work.h"
#include "Other.h"

int main(int argc, char* argv[])
{
	mongocxx::instance ins{};
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
