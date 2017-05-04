#pragma once

#include "DB_ID.h"

class Date;

class Transfer
{
	DB_ID cl_ID;
	DB_ID cl_copyID;
	DB_ID cl_userID;

	Date cl_firstGetDate;
	Date cl_lastContinueDate;
	Date cl_returnDate;

public:
	Transfer(const DB_ID& id, const DB_ID& copyId, const DB_ID& userId, const Date& firstGetDate, const Date& lastContinueDate = Date(), const Date& returnDate = Date());

	DB_ID getId() const;
	DB_ID getCopyId() const;
	DB_ID getUserId() const;
	Date getFirstGetDate() const;
	Date getLastContinueDate() const;
	Date getReturnDate() const;

	bool operator<(const Transfer& that) const;
	bool operator>(const Transfer& that) const;
};
