///////////////////////////////////////////////////////////
//  UserPersonalInfo.h
//  Implementation of the Class UserPersonalInfo
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_38CCD27E_B5D1_4aa7_8DEF_155B9E9D3708__INCLUDED_)
#define EA_38CCD27E_B5D1_4aa7_8DEF_155B9E9D3708__INCLUDED_

#include "typedefs.h"

class UserPersonalInfo
{
public:
	UserPersonalInfo();
	virtual ~UserPersonalInfo();

	String& getName();
	void setName(const String& name);
	String& getSurname();
	void setSurname(const String& surname);
	String& getFatherName();
	void setFatherName(const String& fatherName);
	String& getPassportNumber();
	void setPassportNumber(const String& passportNumber);

private:
	String name;
	String surname;
	String fatherName;
	String passportNumber;
};
#endif // !defined(EA_38CCD27E_B5D1_4aa7_8DEF_155B9E9D3708__INCLUDED_)
