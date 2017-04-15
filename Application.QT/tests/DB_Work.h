#pragma once

#include <gtest/gtest.h>
#include "DBConnector/DBConnector.h"
#include "ClassHierarchy/User.h"
#include "ClassHierarchy/Author.h"

TEST(DB_Work, connectToDB)
{
	DBConnector connector;
}

TEST(DB_Work, addUser)
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

TEST(DB_Work, addAuthor)
{
	Author usr;
	usr.setName("MyName");
	usr.setSurname("MySurname");

	DBConnector connector;
	connector.Add(usr);
}

TEST(DB_Work, getAuthors)
{
	DBConnector connector;
	std::list<Author> authors;
	connector.Get(authors);
}
