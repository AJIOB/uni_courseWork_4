///////////////////////////////////////////////////////////
//  DB_ID.cpp
//  Implementation of the Class DB_ID
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_ID.h"


DB_ID::DB_ID() : cl_isEmpty(true)
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

bsoncxx::oid DB_ID::get() const
{
	return id;
}
