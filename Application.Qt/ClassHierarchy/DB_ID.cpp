///////////////////////////////////////////////////////////
//  DB_ID.cpp
//  Implementation of the Class DB_ID
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_ID.h"


DB_ID::DB_ID(bool isEmpty) : cl_isEmpty(isEmpty)
{
}

DB_ID::DB_ID(const std::string& id) : cl_isEmpty(false), id(id)
{
}

DB_ID::~DB_ID()
{
}

String DB_ID::toString() const
{
	return cl_isEmpty ? "" : id.to_string();
}

bool DB_ID::isEmpty() const
{
	return cl_isEmpty;
}

bsoncxx::oid DB_ID::getObjectID() const
{
	return id;
}

bool DB_ID::operator==(const DB_ID& other) const
{
	if (cl_isEmpty != other.cl_isEmpty)
	{
		return false;
	}

	if (cl_isEmpty == true)
	{
		return true;
	}

	return id == other.id;
}

bool DB_ID::operator!=(const DB_ID& other) const
{
	return !operator==(other);
}
