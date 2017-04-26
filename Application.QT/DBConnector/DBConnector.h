///////////////////////////////////////////////////////////
//  DBConnector.h
//  Implementation of the Class DBConnector
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_C9B1BA3E_E86D_454b_A78D_68365533B1BE__INCLUDED_)
#define EA_C9B1BA3E_E86D_454b_A78D_68365533B1BE__INCLUDED_

#define DB_START mongocxx::instance inst{};

#include <list>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/pool.hpp>

#include "Configuration/ConfigClass.h"
#include "ClassHierarchy/typedefs.h"

class Author;
class BookCopy;
class Book;
class User;
class DB_ID;
enum class UserPriveleges;

class DBConnector
{
	AJIOB::ConfigClass config;

	mongocxx::pool pool;

	bsoncxx::types::value Add(const std::string& collectionName, const bsoncxx::document::view_or_value& view);

	bool isAuthorized;
	UserPriveleges privelege;

	void CheckAuth() const;

public:
	DBConnector(bool connectLocally = true);
	virtual ~DBConnector();

	User Authorize(const String& login, const String& password);
	User LoginAsGuest() const;

	void Add(User& user);
	void Get(std::list<User>& users, bsoncxx::document::view& authFilter = bsoncxx::builder::stream::document{}.view(), const bsoncxx::document::view_or_value& privateFilter = bsoncxx::builder::stream::document{}.view());
	void Update(User& user);
	void Delete(User& user);
	void Add(Book& book);
	void Get(std::list<Book>& books, bsoncxx::document::view& filter = bsoncxx::builder::stream::document{}.view());
	void Update(Book& book);
	void Delete(Book& book);
	DB_ID GiveOutBook(BookCopy& bookCopy, User& user);
	bool RenewBookTime(BookCopy& bookCopy);
	bool ArchieveBookCopy(BookCopy& bookCopy);
	bool ReturnBookCopy(BookCopy& bookCopy);
	void Add(Author& author);
	void Get(std::list<Author>& authors, const bsoncxx::document::view_or_value& filter = bsoncxx::builder::stream::document{}.view());
	void Update(Author& author);
	void Delete(Author& author);
};
#endif // !defined(EA_C9B1BA3E_E86D_454b_A78D_68365533B1BE__INCLUDED_)
