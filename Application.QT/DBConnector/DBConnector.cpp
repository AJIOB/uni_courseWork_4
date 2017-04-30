///////////////////////////////////////////////////////////
//  DBConnector.cpp
//  Implementation of the Class DBConnector
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include <mongocxx/exception/bulk_write_exception.hpp>
#include <bsoncxx/json.hpp>

#include "DBConnector.h"

#include "ClassHierarchy/DB_ID.h"
#include "ClassHierarchy/User.h"
#include "ClassHierarchy/Author.h"
#include "ClassHierarchy/Book.h"

#include "ClassHierarchy/AllExceptions.h"

#define db (*(pool.acquire()))[config["database"]]

bsoncxx::types::value DBConnector::Add(const std::string& collectionName, const bsoncxx::document::view_or_value& view)
{
	mongocxx::stdx::optional<mongocxx::result::insert_one> res;
	try
	{
		res = db[collectionName].insert_one(view);
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

void DBConnector::CheckAuth() const
{
	if (!isAuthorized)
	{
		throw NoAuthException();
	}
}


DBConnector::DBConnector(bool connectLocally)
	: config("dbconfig"), pool{mongocxx::uri{config[std::string("uri_") + (connectLocally ? "localhost" : "server")]}}, isAuthorized(false), privelege(UserPriveleges::none)
{
}


DBConnector::~DBConnector()
{
}

User DBConnector::Authorize(const String& login, const String& password)
{
	if (login == config["guest_login"] && password == config["guest_password"])
	{
		User u;
		u.setLogin(login);
		u.setPassword(password);
		u.setPrivelege(UserPriveleges::guest);
		return u;
	}

	using namespace bsoncxx::builder::stream;

	User u;
	u.setLogin(login);
	u.setPassword(password);
	document d{};
	d <<
		"login" << u.getLogin() <<
		"password" << u.getCryptedPassword();

	std::list<User> users;
	Get(users, d.view());
	if (users.size() == 0)
	{
		throw NoAuthException();
	}

	isAuthorized = true;
	privelege = users.front().getPrivelege();

	return users.front();
}


void DBConnector::Add(User& user)
{
	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	bsoncxx::builder::stream::document document{};
	/*if (!user.getId().isEmpty())
	{
		document <<
			"_id" << user.getId().getObjectID();
	}*/
	bsoncxx::document::view_or_value view = document <<
		"login" << user.getLogin() <<
		"password" << user.getCryptedPassword() <<
		"privelege" << UPtoS(user.getPrivelege()) <<
		bsoncxx::builder::stream::finalize;

	auto id = Add(config["userAuth"], view);

	UserPersonalInfo pi = user.getPersonalInfo();
	view = document <<
		"_id" << id.get_oid() <<
		"name" << pi.getName() <<
		"surname" << pi.getSurname() <<
		"father_name" << pi.getFatherName() <<
		"passport_number" << pi.getPassportNumber() <<
		bsoncxx::builder::stream::finalize;

	Add(config["userPrivateInfo"], view);
}

void DBConnector::Get(std::list<User>& users, const bsoncxx::document::view_or_value& authFilter, const bsoncxx::document::view_or_value& privateFilter)
{
	using namespace bsoncxx::builder::stream;

	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	std::list<User> buff;

	mongocxx::cursor cursor = db[config["userAuth"]].find(authFilter);
	for (auto doc : cursor)
	{
		bsoncxx::document::element element = doc["_id"];
		if (element.type() != bsoncxx::type::k_oid)
		{
			throw OperationException();
		}

		User user(DB_ID(element.get_oid().value.to_string()), doc["password"].get_utf8().value.to_string());

		user.setLogin(doc["login"].get_utf8().value.to_string());
		user.setPrivelege(StoUP(doc["privelege"].get_utf8().value.to_string()));

		buff.push_back(user);
	}

	cursor = db[config["userPrivateInfo"]].find(privateFilter);
	for (auto doc : cursor)
	{
		bsoncxx::document::element element = doc["_id"];
		if (element.type() != bsoncxx::type::k_oid)
		{
			throw OperationException();
		}

		auto id = element.get_oid().value.to_string();

		auto it = std::find_if(buff.begin(), buff.end(),
		                       [&id](const User& u) -> bool
		                       {
			                       return (u.getId().toString() == id);
		                       }
		);

		if (it == buff.end())
		{
			continue;
		}

		User user = *it;
		buff.erase(it);
		UserPersonalInfo upi;
		upi.setName(doc["name"].get_utf8().value.to_string());
		upi.setSurname(doc["surname"].get_utf8().value.to_string());
		upi.setFatherName(doc["father_name"].get_utf8().value.to_string());
		upi.setPassportNumber(doc["passport_number"].get_utf8().value.to_string());

		user.setPersonalInfo(upi);
		users.push_back(user);
	}
}


void DBConnector::Update(User& user)
{
	using namespace bsoncxx::builder::stream;

	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	if (user.getLogin() == config["guest_login"] || user.getId().isEmpty())
	{
		throw GuestUpdateException();
	}

	db[config["userAuth"]].update_one(document{} << "_id" << user.getId().getObjectID() << finalize,
	                                  document{} << "$set" << open_document <<
	                                  "login" << user.getLogin() <<
	                                  "password" << user.getCryptedPassword() <<
	                                  "privelege" << UPtoS(user.getPrivelege()) <<
	                                  close_document << finalize
	);

	UserPersonalInfo pi = user.getPersonalInfo();
	db[config["userPrivateInfo"]].update_one(document{} << "_id" << user.getId().getObjectID() << finalize,
	                                         document{} << "$set" << open_document <<
	                                         "name" << pi.getName() <<
	                                         "surname" << pi.getSurname() <<
	                                         "father_name" << pi.getFatherName() <<
	                                         "passport_number" << pi.getPassportNumber() <<
	                                         close_document << finalize
	);
}


void DBConnector::Delete(User& user)
{
	using namespace bsoncxx::builder::stream;

	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	db[config["userAuth"]].delete_one(document{} << "_id" << user.getId().getObjectID() << finalize);
	db[config["userPrivateInfo"]].delete_one(document{} << "_id" << user.getId().getObjectID() << finalize);
}


void DBConnector::Add(Book& book)
{
	if (config["books"] == "")
	{
		throw ConfigException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	document doc{};

	doc <<
		"isbn" << book.getISBN().toString() <<
		"name" << book.getName() <<
		"year" << book.getYear() <<
		"page_count" << static_cast<li>(book.getPageCount());

	//write authors
	document arrDoc{};
	auto openedArray = arrDoc <<
		"authors" << open_array;
	for (auto a : book.getAuthors())
	{
		openedArray = openedArray << a.getId().getObjectID();
	}
	auto closedArray = openedArray << close_array;
	doc << concatenate(closedArray << finalize);

	document arrDoc2{};
	openedArray = arrDoc2 <<
		"copies" << open_array;
	for (auto c : book.getCopies())
	{
		openedArray = openedArray << open_document <<
			"_id" << c.getId().getObjectID() <<
			"isArchieved" << c.getIsArchieved() <<
			close_document;
	}
	closedArray = openedArray << close_array;
	view_or_value viewValue = doc << concatenate(closedArray << finalize) << finalize;

	Add(config["books"], viewValue);
}

void DBConnector::Get(std::list<Book>& books, const bsoncxx::document::view_or_value& filter)
{
	using namespace bsoncxx::builder::stream;

	if (config["books"] == "")
	{
		throw ConfigException();
	}

	mongocxx::cursor cursor = db[config["books"]].find(filter);
	for (auto doc : cursor)
	{
		bsoncxx::document::element element = doc["_id"];
		if (element.type() != bsoncxx::type::k_oid)
		{
			throw OperationException();
		}

		Book book(DB_ID(element.get_oid().value.to_string()));

		book.setISBN(ISBNClass(doc["isbn"].get_utf8().value.to_string()));
		book.setName(doc["name"].get_utf8().value.to_string());
		book.setYear(doc["year"].get_int32().value);
		book.setPageCount(doc["page_count"].get_int32().value);

		//copies
		for (auto d : doc["copies"].get_array().value)
		{
			BookCopy copy(d["_id"].get_oid().value.to_string());
			copy.setIsArchieved(d["isArchieved"].get_bool().value);
			copy.setIsGettedOut(isCopyGettedOut(copy));
			book.addCopy(copy);
		}

		//authors
		document req{};
		auto inArray = req << "_id" << open_document << "$in" << open_array;
		for (auto d : doc["authors"].get_array().value)
		{
			inArray = inArray << d.get_oid();
		}
		auto outArray = inArray << close_array << close_document;

		std::list<Author> authors;
		Get(authors, outArray << finalize);
		book.setAuthors(authors);

		books.push_back(book);
	}
}


void DBConnector::Update(Book& book)
{
}


void DBConnector::Delete(Book& book)
{
	using namespace bsoncxx::builder::stream;

	if (config["books"] == "")
	{
		throw ConfigException();
	}

	db[config["books"]].delete_one(document{} << "_id" << book.getId().getObjectID() << finalize);
}


std::chrono::system_clock::time_point DBConnector::getCurrentTimePoint()
{
	return std::chrono::system_clock::time_point(std::chrono::system_clock::now());
}

DB_ID DBConnector::GiveOutBook(BookCopy& bookCopy, User& user)
{
	if (config["transfers"] == "")
	{
		throw ConfigException();
	}
	if (!isItBookCopyID(bookCopy.getId()))
	{
		throw NotBookCopyIDException();
	}
	if (isCopyGettedOut(bookCopy))
	{
		throw AlreadyGettedOutException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;
	document doc{};

	doc <<
		"copy_id" << bookCopy.getId().getObjectID() <<
		"user_id" << user.getId().getObjectID() <<
		"first_get_date" << b_date(getCurrentTimePoint());

	view_or_value viewValue = doc << finalize;

	auto id = Add(config["transfers"], viewValue);
	return DB_ID(id.get_oid().value.to_string());
}


bool DBConnector::RenewBookTime(BookCopy& bookCopy)
{
	return false;
}


bool DBConnector::ArchieveBookCopy(BookCopy& bookCopy)
{
	return false;
}

bool DBConnector::isCopyGettedOut(BookCopy& bookCopy)
{
	if (config["transfers"] == "")
	{
		throw ConfigException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;
	document doc{};

	doc <<
		"copy_id" << bookCopy.getId().getObjectID() <<
		"return_date" << open_document <<
			"$exists" << false <<
		close_document;

	view_or_value viewValue = doc << finalize;
	mongocxx::cursor cursor = db[config["transfers"]].find(viewValue);
	return cursor.begin() != cursor.end();
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
	/*if (!author.getID().isEmpty())
	{
		document <<
			"_id" << author.getID().getObjectID();
	}*/
	bsoncxx::document::view_or_value view = document <<
		"name" << author.getName() <<
		"father_name" << author.getFatherName() <<
		"surname" << author.getSurname() <<
		bsoncxx::builder::stream::finalize;

	std::list<Author> check;
	Get(check, view);

	if (!check.empty())
	{
		throw NonUniqueException();
	}

	Add(config["authors"], view);
}

void DBConnector::Get(std::list<Author>& authors, const bsoncxx::document::view_or_value& filter)
{
	using namespace bsoncxx::builder::stream;

	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	mongocxx::cursor cursor = db[config["authors"]].find(filter);
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
	using namespace bsoncxx::builder::stream;

	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	db[config["authors"]].update_one(document{} << "_id" << author.getId().getObjectID() << finalize,
	                                 document{} << "$set" << open_document <<
	                                 "name" << author.getName() <<
	                                 "surname" << author.getSurname() <<
	                                 close_document << finalize
	);
}


void DBConnector::Delete(Author& author)
{
	using namespace bsoncxx::builder::stream;

	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	db[config["authors"]].delete_one(document{} << "_id" << author.getId().getObjectID() << finalize);
}

User DBConnector::LoginAsGuest() const
{
	User u;
	u.setLogin(config["guest_login"]);
	u.setPassword(config["guest_password"]);
	u.setPrivelege(UserPriveleges::guest);
	return u;
}

bool DBConnector::isItBookCopyID(DB_ID idToCheck)
{
	if (config["books"] == "")
	{
		throw ConfigException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;
	document doc{};

	doc <<
		"copies" << open_document <<
			"$elemMatch" << open_document <<
				"_id" << open_document <<
					"$in" << open_array <<
						idToCheck.getObjectID() <<
					close_array <<
				close_document <<
			close_document <<
		close_document;

	view_or_value viewValue = doc << finalize;
	mongocxx::cursor cursor = db[config["books"]].find(viewValue);
	return cursor.begin() != cursor.end();
}

#undef db
