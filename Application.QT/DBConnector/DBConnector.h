///////////////////////////////////////////////////////////
//  DBConnector.h
//  Implementation of the Class DBConnector
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_C9B1BA3E_E86D_454b_A78D_68365533B1BE__INCLUDED_)
#define EA_C9B1BA3E_E86D_454b_A78D_68365533B1BE__INCLUDED_

#define GTEST_LOCAL

#include <list>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>

#include "ClassHierarchy/DB_ID.h"
#include "Configuration/ConfigClass.h"

class Author;
class BookCopy;
class Book;
class User;

class DBConnector
{
	AJIOB::ConfigClass config;

#if !defined(GTEST) && !defined(GTEST_LOCAL)
	mongocxx::instance inst;
#elif defined(GTEST) && !defined(GTEST_LOCAL)
#error Please, define GTEST_LOCAL
#endif

	mongocxx::client client;
	mongocxx::database db;

	//bsoncxx::types::value Add(const std::string& collectionName, bsoncxx::builder::stream::document* document) const;

public:
	DBConnector();
	virtual ~DBConnector();

	void Add(User& user) const;
	void Get(std::list<User>& users);
	void Update(User& newUser);
	void Delete(User& user);
	void Add(Book& book);
	void Get(std::list<Book>& books);
	void Update(Book& book);
	void Delete(Book& book);
	DB_ID GiveOutBook(BookCopy& bookCopy, User& user);
	bool RenewBookTime(BookCopy& bookCopy);
	bool ArchieveBookCopy(BookCopy& bookCopy);
	bool ReturnBookCopy(BookCopy& bookCopy);
	void Add(Author& author);
	void Get(std::list<Author>& authors);
	void Update(Author& author);
	void Delete(Author& author);
};
#endif // !defined(EA_C9B1BA3E_E86D_454b_A78D_68365533B1BE__INCLUDED_)