#include <gtest/gtest.h>
#include "DBConnector/DBConnector.h"
#include "ClassHierarchy/User.h"

TEST(CheckTestsToWork, Hello)
{
	EXPECT_EQ("Hello", "Hello");
}

TEST(DB_Work, connectToDB)
{
	DBConnector connector;
}

TEST(DB_WorkBEBUGONLY, addUser)
{
	//try
	{
		User usr;
		usr.setLogin("Login");
		usr.SetPassword("Password");
		usr.setPrivelege(UserPriveleges::admin);

		UserPersonalInfo upi;
		upi.setName("MyName");
		upi.setSurname("MySurname");
		upi.setFatherName("MyFatherName");
		upi.setPassportNumber("MyPassportNum");

		usr.setPersonalInfo(upi);

		DBConnector connector;
		connector.Add(usr);
	}
	/*catch(std::exception)
	{
		EXPECT_FALSE(true);
	}*/
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
