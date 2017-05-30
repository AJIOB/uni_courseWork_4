///////////////////////////////////////////////////////////
//  BookCopy.h
//  Implementation of the Class BookCopy
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_4D6EE6BF_8C67_4ae1_B478_3F2596E6BD78__INCLUDED_)
#define EA_4D6EE6BF_8C67_4ae1_B478_3F2596E6BD78__INCLUDED_

#include "DB_ID.h"

class BookCopy
{
	DB_ID _id;
	bool isArchieved;
	bool isGettedOut;

public:
	explicit BookCopy(const DB_ID& id = DB_ID());
	virtual ~BookCopy();

	DB_ID getId() const;
	bool getIsArchieved() const;
	void setIsArchieved(const bool isArchieved);
	bool getIsGettedOut() const;
	void setIsGettedOut(const bool isGettedOut);
};
#endif // !defined(EA_4D6EE6BF_8C67_4ae1_B478_3F2596E6BD78__INCLUDED_)
