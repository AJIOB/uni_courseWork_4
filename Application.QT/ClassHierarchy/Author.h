///////////////////////////////////////////////////////////
//  Author.h
//  Implementation of the Class Author
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_93F468CD_D51D_4b2f_A90E_4DE9CCC66E66__INCLUDED_)
#define EA_93F468CD_D51D_4b2f_A90E_4DE9CCC66E66__INCLUDED_

#include "typedefs.h"
#include "DB_ID.h"

class Author
{
	DB_ID _id;
	String name;
	String surname;
	String fatherName;

public:
	explicit Author(const DB_ID& id = DB_ID());
	virtual ~Author();

	String getName() const;
	void setName(String name);
	String getSurname() const;
	void setSurname(String surname);
	DB_ID getId() const;
	String getFatherName() const;
	void setFatherName(const String& fatherName);

	bool operator==(const Author& that) const;
};
#endif // !defined(EA_93F468CD_D51D_4b2f_A90E_4DE9CCC66E66__INCLUDED_)
