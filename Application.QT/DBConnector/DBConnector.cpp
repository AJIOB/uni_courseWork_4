///////////////////////////////////////////////////////////
//  DBConnector.cpp
//  Implementation of the Class DBConnector
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "ClassHierarchy/User.h"
#include "DBConnector.h"

#include <mongocxx/exception/bulk_write_exception.hpp>

#include "ClassHierarchy/AllExceptions.h"

bsoncxx::types::value DBConnector::Add(const std::string& collectionName, const bsoncxx::document::view_or_value& document) const
{
	auto collection = db[collectionName];
	mongocxx::stdx::optional<mongocxx::result::insert_one> res;
	try
	{
		res = collection.insert_one(document);
	}
	catch (mongocxx::bulk_write_exception e)
	{
		throw DBOperationCancelledException();
	}

	res->inserted_id();
	if (res->result().inserted_count() == 0)
	{
		throw OperationException();
	}

	return res->inserted_id();
}

DBConnector::DBConnector() : config("dbconfig"), db_uri(config["uri"]), client(db_uri), db(client[config["database"]])
{
}


DBConnector::~DBConnector()
{
}


void DBConnector::Add(User& user) const
{
	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	//todo: using _id
	bsoncxx::builder::stream::document document{};
	document <<
		"login" << user.getLogin() <<
		"password" << user.getCryptedPassword() <<
		"priveleges" << UPtoS(user.getPrivelege()) <<
		bsoncxx::builder::stream::finalize;

	auto id = Add(config["userAuth"], document.view());

	//todo: add second part
}


void DBConnector::Get(std::list<User>& users)
{
}


void DBConnector::Update(User& newUser)
{
}


void DBConnector::Delete(User& user)
{
}


void DBConnector::Add(Book& book)
{
}


void DBConnector::Get(std::list<Book>& books)
{
}


void DBConnector::Update(Book& book)
{
}


void DBConnector::Delete(Book& book)
{
}


DB_ID DBConnector::GiveOutBook(BookCopy& bookCopy, User& user)
{
	//todo
	return DB_ID();
}


bool DBConnector::RenewBookTime(BookCopy& bookCopy)
{
	return false;
}


bool DBConnector::ArchieveBookCopy(BookCopy& bookCopy)
{
	return false;
}


bool DBConnector::ReturnBookCopy(BookCopy& bookCopy)
{
	return false;
}


void DBConnector::Add(Author& author)
{
}


int DBConnector::Get(std::list<Author>& authors)
{
	return 0;
}


void DBConnector::Update(Author& author)
{
}


void DBConnector::Delete(Author& author)
{
}
