///////////////////////////////////////////////////////////
//  DB_ID.cpp
//  Implementation of the Class DB_ID
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB_ID.h"


DB_ID::DB_ID() : isEmpty(true)
{
}

DB_ID::DB_ID(const std::string& id) : isEmpty(true), id(id)
{
}

DB_ID::~DB_ID()
{
}

String DB_ID::toString() const
{
	return isEmpty ? "" : id.to_string();
}