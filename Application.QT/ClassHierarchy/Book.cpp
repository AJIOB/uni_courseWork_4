///////////////////////////////////////////////////////////
//  Book.cpp
//  Implementation of the Class Book
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Book.h"

Book::Book(const DB_ID& id, const uli& copiesNum) : _id(id), year(0), pageCount(0)
{
	for (uli i = 0; i < copiesNum; ++i)
	{
		copies.push_back(BookCopy());
	}
}

Book::~Book()
{
}


uli Book::GetNumOfAllCopies() const
{
	return copies.size();
}


usi Book::GetNumOfCopiesInLibrary()
{
	return std::count_if(copies.begin(), copies.end(),
	                     [](const BookCopy& copy)
	                     {
		                     return (!copy.getIsArchieved() && !copy.getIsGettedOut());
	                     });
}

DB_ID Book::getId() const
{
	return _id;
}


ISBNClass Book::getISBN() const
{
	return ISBN;
}

void Book::setISBN(const ISBNClass& isbn)
{
	ISBN = isbn;
}

std::list<Author> Book::getAuthors() const
{
	return authors;
}

void Book::setAuthors(const std::list<Author>& authors)
{
	this->authors = authors;
}

String Book::getName() const
{
	return name;
}

void Book::setName(const String& name)
{
	this->name = name;
}

li Book::getYear() const
{
	return year;
}

void Book::setYear(const li year)
{
	this->year = year;
}

uli Book::getPageCount() const
{
	return pageCount;
}

void Book::setPageCount(const uli pageCount)
{
	this->pageCount = pageCount;
}

std::list<BookCopy> Book::getCopies() const
{
	return copies;
}

void Book::addCopy(const BookCopy& copy)
{
	copies.push_back(copy);
}

std::string Book::getAuthorsAsString() const
{
	return getAuthorsAsString(authors);
}

std::string Book::getAuthorsAsString(const std::list<Author>& authors)
{
	std::string res;

	for (auto a : authors)
	{
		res += a.getSurname() + ", ";
	}

	if (!res.empty())
	{
		//last ", " symbols
		res.pop_back();
		res.pop_back();
	}

	return res;
}
