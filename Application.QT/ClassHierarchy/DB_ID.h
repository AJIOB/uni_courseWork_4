///////////////////////////////////////////////////////////
//  DB_ID.h
//  Implementation of the Class DB_ID
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_B7E4D6F3_11D9_4ad5_867C_1DA7D5BAB3A1__INCLUDED_)
#define EA_B7E4D6F3_11D9_4ad5_867C_1DA7D5BAB3A1__INCLUDED_

#include <mongocxx/client.hpp>

#include "typedefs.h"

class DB_ID
{
	bool cl_isEmpty;

	bsoncxx::oid id;

public:
	DB_ID(bool isEmpty = true);
	DB_ID(const std::string& id);
	virtual ~DB_ID();

	String toString() const;
	bool isEmpty() const;

	bsoncxx::oid getObjectID() const;

	bool operator==(const DB_ID& other) const;
	bool operator!=(const DB_ID& other) const;
};
#endif // !defined(EA_B7E4D6F3_11D9_4ad5_867C_1DA7D5BAB3A1__INCLUDED_)
