#pragma once

#include <gtest/gtest.h>
#include "DBConnector/DBConnector.h"
#include "ClassHierarchy/User.h"
#include "ClassHierarchy/Author.h"
#include "ClassHierarchy/Book.h"

TEST(DB_Work, connectToDB)
{
	DBConnector connector;
}

TEST(DB_Work, addUser)
{
	User usr;
	usr.setLogin("Login");
	usr.setPassword("Password");
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

TEST(DB_Work, addUserToServer)
{
	User usr;
	usr.setLogin("Login");
	usr.setPassword("Password");
	usr.setPrivelege(UserPriveleges::admin);

	UserPersonalInfo upi;
	upi.setName("MyName");
	upi.setSurname("MySurname");
	upi.setFatherName("MyFatherName");
	upi.setPassportNumber("MyPassportNum");

	usr.setPersonalInfo(upi);

	DBConnector connector("server");
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

TEST(DB_Work, getFilteredAuthors)
{
	DBConnector connector;
	std::list<Author> authors;
	bsoncxx::builder::stream::document d{};
	d << "Name" << "Alex";

	connector.Get(authors, d.view());
	EXPECT_EQ(authors.size(), 0);

	authors.clear();
	d.clear();
	d << "name" <<
		bsoncxx::builder::stream::open_document <<
		"$exists" << true <<
		bsoncxx::builder::stream::close_document;

	connector.Get(authors, d.view());
	EXPECT_TRUE(authors.size() > 0);
}

TEST(DB_Work, addBook)
{
	Book book(DB_ID(), 3);
	book.setName("MyName");
	book.setYear(2016);
	book.setPageCount(456);

	std::list<Author> authors;
	authors.push_back(Author(DB_ID("58ff6cd3eb758c200c00645b")));
	book.setAuthors(authors);

	ISBNClass isbn;
	EXPECT_TRUE(isbn.ParseString("5-85273-056-4"));
	book.setISBN(isbn);

	DBConnector connector;
	connector.Add(book);
}
