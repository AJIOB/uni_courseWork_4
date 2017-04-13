///////////////////////////////////////////////////////////
//  Book.h
//  Implementation of the Class Book
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_18AA30C7_1FD8_4bd2_ADC9_4EECF1F24FC6__INCLUDED_)
#define EA_18AA30C7_1FD8_4bd2_ADC9_4EECF1F24FC6__INCLUDED_

#include "typedefs.h"
#include "DB_ID.h"
#include "ISBNClass.h"
#include "BookCopy.h"
#include "Author.h"

class Book
{
	DB_ID _id;
	ISBNClass ISBN;
	std::list<Author> authors;
	String name;
	li year;
	uli pageCount;
	std::list<BookCopy> copies;

public:
	Book();
	virtual ~Book();

	uli GetNumOfAllCopies() const;
	usi GetNumOfCopiesInLibrary();


	DB_ID getId() const;
	ISBNClass getISBN() const;
	void setISBN(const ISBNClass& isbn);
	std::list<Author> getAuthors() const;
	String getName() const;
	void setName(const String& name);
	li getYear() const;
	void setYear(const li year);
	uli getPageCount() const;
	void setPageCount(const uli pageCount);
	std::list<BookCopy> getCopies() const;
};
#endif // !defined(EA_18AA30C7_1FD8_4bd2_ADC9_4EECF1F24FC6__INCLUDED_)
