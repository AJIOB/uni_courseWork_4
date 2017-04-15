///////////////////////////////////////////////////////////
//  DBConnector.cpp
//  Implementation of the Class DBConnector
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include <mongocxx/exception/bulk_write_exception.hpp>
#include <bsoncxx/json.hpp>

#include "DBConnector.h"

#include "ClassHierarchy/User.h"
#include "ClassHierarchy/Author.h"

#include "ClassHierarchy/AllExceptions.h"

//static DBConnector::inst{};
/*
bsoncxx::types::value DBConnector::Add(const std::string& collectionName, bsoncxx::builder::stream::document* document) const
{
	auto collection = db[collectionName];
	mongocxx::stdx::optional<mongocxx::result::insert_one> res;
	try
	{
		res = collection.insert_one(document->view());
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
*/
DBConnector::DBConnector() : config("dbconfig"), client(mongocxx::uri{ config["uri"] }), db(client[config["database"]])
{
	//config("dbconfig");
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

	bsoncxx::builder::stream::document document{};
	bsoncxx::document::view_or_value view = document <<
		"login" << user.getLogin() <<
		"password" << user.getCryptedPassword() <<
		"priveleges" << UPtoS(user.getPrivelege()) <<
		bsoncxx::builder::stream::finalize;

	auto collection = db[config["userAuth"]];
	mongocxx::stdx::optional<mongocxx::result::insert_one> res;
	try
	{
		res = collection.insert_one(view);
	}
	catch (mongocxx::bulk_write_exception e)
	{
		throw DBOperationCancelledException();
	}

	if (res->result().inserted_count() == 0)
	{
		throw OperationException();
	}


	//return res->inserted_id();

	//todo: using _id

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
	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	bsoncxx::builder::stream::document document{};
	bsoncxx::document::view_or_value view = document <<
		"name" << author.getName() <<
		"surname" << author.getSurname() <<
		bsoncxx::builder::stream::finalize;

	auto collection = db[config["authors"]];
	mongocxx::stdx::optional<mongocxx::result::insert_one> res;
	try
	{
		res = collection.insert_one(view);
	}
	catch (mongocxx::bulk_write_exception e)
	{
		throw DBOperationCancelledException();
	}

	if (res->result().inserted_count() == 0)
	{
		throw OperationException();
	}
}


void DBConnector::Get(std::list<Author>& authors)
{
	using namespace bsoncxx::builder::stream;

	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	auto collection = db[config["authors"]];
	mongocxx::cursor cursor = collection.find(document{} << finalize);
	for (auto doc : cursor) {
		bsoncxx::to_json(doc);
	}
}


void DBConnector::Update(Author& author)
{
}


void DBConnector::Delete(Author& author)
{
}
