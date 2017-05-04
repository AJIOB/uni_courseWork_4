#define GTEST

#include "DB_Work.h"
#include "Other.h"
#include "logs.h"

int main(int argc, char* argv[])
{
	DB_START
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
