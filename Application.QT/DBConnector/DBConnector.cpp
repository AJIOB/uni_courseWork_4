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


bsoncxx::types::value DBConnector::Add(const std::string& collectionName, bsoncxx::document::view_or_value& view) const
{
	auto collection = db[collectionName];
	mongocxx::stdx::optional<mongocxx::result::insert_one> res;
	try
	{
		res = collection.insert_one(view);
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

DBConnector::DBConnector() : config("dbconfig"), client(mongocxx::uri{config["uri"]}), db(client[config["database"]])
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

	//todo: using _id
	bsoncxx::builder::stream::document document{};
	bsoncxx::document::view_or_value view = document <<
		"login" << user.getLogin() <<
		"password" << user.getCryptedPassword() <<
		"priveleges" << UPtoS(user.getPrivelege()) <<
		bsoncxx::builder::stream::finalize;

	Add(config["userAuth"], view);

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


void DBConnector::Add(Author& author) const
{
	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	bsoncxx::builder::stream::document document{};
	if (!author.getID().isEmpty())
	{
		document <<
			"_id" << author.getID().get();
	}

	bsoncxx::document::view_or_value view = document <<
		"name" << author.getName() <<
		"surname" << author.getSurname() <<
		bsoncxx::builder::stream::finalize;

	Add(config["authors"], view);
}


void DBConnector::Get(std::list<Author>& authors) const
{
	using namespace bsoncxx::builder::stream;

	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	mongocxx::cursor cursor = db[config["authors"]].find(document{}.view());
	for (auto doc : cursor)
	{
		bsoncxx::document::element element = doc["_id"];
		if (element.type() != bsoncxx::type::k_oid)
		{
			throw OperationException();
		}

		Author author(DB_ID(element.get_oid().value.to_string()));

		author.setName(doc["name"].get_utf8().value.to_string());
		author.setSurname(doc["surname"].get_utf8().value.to_string());

		authors.push_back(author);
	}
}


void DBConnector::Update(Author& author)
{
}


void DBConnector::Delete(Author& author)
{
}
