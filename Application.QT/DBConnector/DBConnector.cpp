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
#include "ClassHierarchy/Transfer.h"

#include "ClassHierarchy/AllExceptions.h"

#define db (*(pool.acquire()))[config["database"]]
#define AJIOB_LOG Logger::get().write

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


DBConnector::DBConnector(String connectTo)
	: config("dbconfig"), pool{mongocxx::uri{config["uri_" + connectTo]}}, isAuthorized(false), privelege(UserPriveleges::none)
{
}


DBConnector::~DBConnector()
{
}

User DBConnector::Authorize(const String& login, const String& password)
{
	AJIOB_LOG("Someone tries to autorize");

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

	AJIOB_LOG("Autorization is successful. Login is " + login);
	return users.front();
}


void DBConnector::Add(User& user)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to add user");

	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	using namespace bsoncxx::builder::stream;

	std::list<User> users;
	Get(users, document{} << "login" << user.getLogin() << finalize, document{} << finalize);
	if (users.size() != 0)
	{
		throw NonUniqueException();
	}

	document document{};
	bsoncxx::document::view_or_value view = document <<
		"login" << user.getLogin() <<
		"password" << user.getCryptedPassword() <<
		"privelege" << UPtoS(user.getPrivelege()) <<
		finalize;

	auto id = Add(config["userAuth"], view);

	UserPersonalInfo pi = user.getPersonalInfo();
	view = document <<
		"_id" << id.get_oid() <<
		"name" << pi.getName() <<
		"surname" << pi.getSurname() <<
		"father_name" << pi.getFatherName() <<
		"passport_number" << pi.getPassportNumber() <<
		finalize;

	Add(config["userPrivateInfo"], view);
	AJIOB_LOG("Adding user is successful");
}

void DBConnector::Get(std::list<User>& users, const bsoncxx::document::view_or_value& authFilter, const bsoncxx::document::view_or_value& privateFilter)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to get users");
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
	AJIOB_LOG("Getting users is successful");
}


void DBConnector::Update(User& user)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to update user");
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
	AJIOB_LOG("Updating user is successful");
}


void DBConnector::Delete(User& user)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to delete user");
	using namespace bsoncxx::builder::stream;

	if (config["userAuth"] == "" || config["userPrivateInfo"] == "")
	{
		throw ConfigException();
	}

	std::list<Transfer> transfers;
	Get(transfers, document{} << "user_id" << user.getId().getObjectID() << finalize);
	if (!transfers.empty())
	{
		throw UserGetOutSomethingException();
	}

	db[config["userAuth"]].delete_one(document{} << "_id" << user.getId().getObjectID() << finalize);
	db[config["userPrivateInfo"]].delete_one(document{} << "_id" << user.getId().getObjectID() << finalize);
	AJIOB_LOG("Deleting user is successful");
}


void DBConnector::Add(Book& book)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to add book");
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
	AJIOB_LOG("Adding book is successful");
}

void DBConnector::Get(std::list<Book>& books, const bsoncxx::document::view_or_value& filter)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to get books");
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
	AJIOB_LOG("Getting books is successful");
}


void DBConnector::Update(Book& book)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to update book");
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

	db[config["books"]].update_one(document{} << "_id" << book.getId().getObjectID() << finalize,
		document{} << "$set" << open_document <<
		concatenate(viewValue) << close_document << 
		finalize
	);
	AJIOB_LOG("Updating book is successful");
}


void DBConnector::Delete(Book& book)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to delete book");
	if (config["books"] == "")
	{
		throw ConfigException();
	}

	using namespace bsoncxx::builder::stream;

	std::list<Transfer> transfers;
	document doc{};
	auto inArray = 
		doc << "copy_id" << open_document <<
		"$in" << open_array;
		
	for (auto bc : book.getCopies())
	{
		inArray = inArray << bc.getId().getObjectID();
	}

	Get(transfers, inArray << close_array << close_document << finalize);
	if (!transfers.empty())
	{
		throw BookGettedOutBySomebodyException();
	}

	db[config["books"]].delete_one(document{} << "_id" << book.getId().getObjectID() << finalize);
	AJIOB_LOG("Deleting book is successful");
}


std::chrono::system_clock::time_point DBConnector::getCurrentTimePoint()
{
	return std::chrono::system_clock::now();
}

DB_ID DBConnector::GiveOutBook(BookCopy& bookCopy, User& user)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to give out book copy");
	if (config["transfers"] == "")
	{
		throw ConfigException();
	}
	if (!isItBookCopyID(bookCopy.getId()))
	{
		throw NotBookCopyIDException();
	}
	if (isCopyArchieved(bookCopy))
	{
		throw AlreadyArchievedException();
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
	AJIOB_LOG("Giving out book copy is successful");
	return DB_ID(id.get_oid().value.to_string());
}


void DBConnector::RenewBookTime(BookCopy& bookCopy)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to renew book copy");
	if (config["transfers"] == "")
	{
		throw ConfigException();
	}
	if (!isItBookCopyID(bookCopy.getId()))
	{
		throw NotBookCopyIDException();
	}
	if (isCopyArchieved(bookCopy))
	{
		throw AlreadyArchievedException();
	}

	if (!isCopyGettedOut(bookCopy))
	{
		throw NotGettedOutException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;

	db[config["transfers"]].update_one(
		document{} <<
		"copy_id" << bookCopy.getId().getObjectID() <<
		"return_date" << open_document <<
		"$exists" << false <<
		close_document <<
		finalize,
		document{} << "$currentDate" << open_document <<
		"last_continue_date" << true <<
		close_document << finalize
	);
	AJIOB_LOG("Renewing book copy is successful");
}


void DBConnector::ArchieveBookCopy(BookCopy& bookCopy)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to archieve book copy");
	if (config["books"] == "")
	{
		throw ConfigException();
	}
	if (!isItBookCopyID(bookCopy.getId()))
	{
		throw NotBookCopyIDException();
	}
	if (isCopyArchieved(bookCopy))
	{
		throw AlreadyArchievedException();
	}
	if (isCopyGettedOut(bookCopy))
	{
		throw AlreadyGettedOutException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;

	db[config["books"]].update_one(
		document{} <<
		"copies._id" << bookCopy.getId().getObjectID() << 
		finalize,
		document{} << "$set" << open_document <<
		"copies.$.isArchieved" << true <<
		close_document << finalize
	);

	bookCopy.setIsArchieved(true);
	AJIOB_LOG("Archieving book copy is successful");
}

bool DBConnector::isCopyGettedOut(BookCopy& bookCopy)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to get info about if book copy getted out");
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
	AJIOB_LOG("Giving info about is book copy giving out is successful");
	return cursor.begin() != cursor.end();
}

bool DBConnector::isCopyArchieved(const BookCopy& bookCopy)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to get info about if book copy archieved");
	if (config["books"] == "")
	{
		throw ConfigException();
	}
	if (!isItBookCopyID(bookCopy.getId()))
	{
		throw NotBookCopyIDException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;
	document doc{};

	doc <<
		"copies" << open_document <<
		"$elemMatch" << open_document <<
			"_id" << bookCopy.getId().getObjectID() <<
			"isArchieved" << true <<
		close_document <<
		close_document;

	view_or_value viewValue = doc << finalize;
	mongocxx::cursor cursor = db[config["books"]].find(viewValue);
	AJIOB_LOG("Giving info about is book copy archieved is successful");
	return cursor.begin() != cursor.end();
}

void DBConnector::ReturnBookCopy(BookCopy& bookCopy)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to return book copy");
	if (config["transfers"] == "")
	{
		throw ConfigException();
	}
	if (!isItBookCopyID(bookCopy.getId()))
	{
		throw NotBookCopyIDException();
	}
	if (isCopyArchieved(bookCopy))
	{
		throw AlreadyArchievedException();
	}

	if (!isCopyGettedOut(bookCopy))
	{
		throw NotGettedOutException();
	}

	using namespace bsoncxx::builder::stream;
	using namespace bsoncxx::document;
	using namespace bsoncxx::types;
	
	db[config["transfers"]].update_one(
		document{} << 
			"copy_id" << bookCopy.getId().getObjectID() << 
			"return_date" << open_document <<
				"$exists" << false <<
			close_document <<
		finalize,
		document{} << "$currentDate" << open_document <<
		"return_date" << true <<
		close_document << finalize
	);

	bookCopy.setIsGettedOut(false);
	AJIOB_LOG("Peturning book copy is successful");
}

void DBConnector::Add(Author& author)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to add author");
	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	bsoncxx::builder::stream::document document{};

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
	AJIOB_LOG("Adding author is successful");
}

void DBConnector::Get(std::list<Author>& authors, const bsoncxx::document::view_or_value& filter)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to get authors");
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
		author.setFatherName(doc["father_name"].get_utf8().value.to_string());

		authors.push_back(author);
	}
	AJIOB_LOG("Getting authors is successful");
}


void DBConnector::Update(Author& author)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to update author");
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
	AJIOB_LOG("Updating author is successful");
}


void DBConnector::Delete(Author& author)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to delete author");
	using namespace bsoncxx::builder::stream;

	if (config["authors"] == "")
	{
		throw ConfigException();
	}

	db[config["authors"]].delete_one(document{} << "_id" << author.getId().getObjectID() << finalize);
	AJIOB_LOG("Deleting author is successful");
}

void DBConnector::Get(std::list<Transfer>& transfers, const bsoncxx::document::view_or_value& filter)
{
	AJIOB_LOG(UPtoS(privelege) + " privelege user tries to get transfers");
	using namespace bsoncxx::builder::stream;

	if (config["transfers"] == "")
	{
		throw ConfigException();
	}

	mongocxx::cursor cursor = db[config["transfers"]].find(filter);
	for (auto doc : cursor)
	{
		bsoncxx::document::element element = doc["_id"];
		if (element.type() != bsoncxx::type::k_oid)
		{
			throw OperationException();
		}

		DB_ID ID(doc["_id"].get_oid().value.to_string());
		DB_ID copyID(doc["copy_id"].get_oid().value.to_string());
		DB_ID userID(doc["user_id"].get_oid().value.to_string());

		Date firstGetDate(doc["first_get_date"].get_date());

		Date lastContinueDate;
		if (doc.find("last_continue_date") != doc.end() && doc["last_continue_date"].type() == bsoncxx::type::k_date)
		{
			lastContinueDate = Date(doc["last_continue_date"].get_date());
		}
		Date returnDate;
		if (doc.find("return_date") != doc.end() && doc["return_date"].type() == bsoncxx::type::k_date)
		{
			returnDate = Date(doc["return_date"].get_date());
		}

		transfers.push_back(Transfer(ID, copyID, userID, firstGetDate, lastContinueDate, returnDate));
	}
	AJIOB_LOG("Getting transfers is successful");
}

User DBConnector::LoginAsGuest()
{
	AJIOB_LOG("Someone tries to autorize as guest");
	User u;
	u.setLogin(config["guest_login"]);
	u.setPassword(config["guest_password"]);
	u.setPrivelege(UserPriveleges::guest);
	privelege = u.getPrivelege();
	AJIOB_LOG("Autorization as guest is successful");
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

#undef AJIOB_LOG
#undef db
