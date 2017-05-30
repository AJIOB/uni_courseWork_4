#include "stdafx.h"
#include "Transfer.h"

Transfer::Transfer(const DB_ID& id, const DB_ID& copyId, const DB_ID& userId, const Date& firstGetDate, const Date& lastContinueDate, const Date& returnDate)
	: cl_ID(id),
	cl_copyID(copyId),
	cl_userID(userId),
	cl_firstGetDate(firstGetDate),
	cl_lastContinueDate(lastContinueDate),
	cl_returnDate(returnDate)
{
}

DB_ID Transfer::getId() const
{
	return cl_ID;
}

DB_ID Transfer::getCopyId() const
{
	return cl_copyID;
}

DB_ID Transfer::getUserId() const
{
	return cl_userID;
}

Date Transfer::getFirstGetDate() const
{
	return cl_firstGetDate;
}

Date Transfer::getLastContinueDate() const
{
	return cl_lastContinueDate;
}

Date Transfer::getReturnDate() const
{
	return cl_returnDate;
}

bool Transfer::operator<(const Transfer& that) const
{
	return cl_ID.toString() < that.cl_ID.toString();
}

bool Transfer::operator>(const Transfer& that) const
{
	return cl_ID.toString() > that.cl_ID.toString();
}
