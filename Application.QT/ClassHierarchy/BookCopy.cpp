///////////////////////////////////////////////////////////
//  BookCopy.cpp
//  Implementation of the Class BookCopy
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BookCopy.h"

BookCopy::BookCopy(const DB_ID& id) : _id(id), isArchieved(false), isGettedOut(false)
{
}

BookCopy::~BookCopy()
{
}

DB_ID BookCopy::getId() const
{
	return _id;
}

bool BookCopy::getIsArchieved() const
{
	return isArchieved;
}

void BookCopy::setIsArchieved(const bool isArchieved)
{
	this->isArchieved = isArchieved;
}

bool BookCopy::getIsGettedOut() const
{
	return isGettedOut;
}

void BookCopy::setIsGettedOut(const bool isGettedOut)
{
	this->isGettedOut = isGettedOut;
}
