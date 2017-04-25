///////////////////////////////////////////////////////////
//  Author.cpp
//  Implementation of the Class Author
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Author.h"


Author::Author(const DB_ID& id) : _id(id)
{
}

Author::~Author()
{
}


String Author::getName() const
{
	return name;
}


void Author::setName(String name)
{
	this->name = name;
}


String Author::getSurname() const
{
	return surname;
}


void Author::setSurname(String surname)
{
	this->surname = surname;
}


DB_ID Author::getId() const
{
	return _id;
}


String Author::getFatherName() const
{
	return fatherName;
}


void Author::setFatherName(const String& fatherName)
{
	this->fatherName = fatherName;
}
