///////////////////////////////////////////////////////////
//  DBConnector.cpp
//  Implementation of the Class DBConnector
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////


#include "DBConnector.h"


DBConnector::DBConnector() : config("dbconfig"), db_uri(config["uri"]), client(db_uri)
{
}


DBConnector::~DBConnector()
{
}


void DBConnector::Add(User& user)
{
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
