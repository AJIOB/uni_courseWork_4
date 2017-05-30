///////////////////////////////////////////////////////////
//  User.h
//  Implementation of the Class User
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#if !defined(EA_07E2DE28_F0E8_4507_B76A_97E0D85C2F89__INCLUDED_)
#define EA_07E2DE28_F0E8_4507_B76A_97E0D85C2F89__INCLUDED_

#include "typedefs.h"
#include "DB_ID.h"
#include "UserPersonalInfo.h"
#include "UserPriveleges.h"

class User
{
public:
	explicit User(const DB_ID& id = DB_ID(), const String& cryptedPassword = "");
	virtual ~User();

	bool isPasswordCorrect(const String& password) const;
	bool setPassword(const String& newPassword, const String& oldPassword = "");
	void resetPassword();

	DB_ID getId() const;
	String getLogin() const;
	void setLogin(const String& login);
	String getCryptedPassword() const;
	UserPriveleges getPrivelege() const;
	void setPrivelege(const UserPriveleges privelege);
	UserPersonalInfo getPersonalInfo() const;
	void setPersonalInfo(const UserPersonalInfo& personalInfo);
private:
	DB_ID _id;
	String login;
	String cryptedPassword;
	UserPriveleges privelege;
	UserPersonalInfo personalInfo;
};
#endif // !defined(EA_07E2DE28_F0E8_4507_B76A_97E0D85C2F89__INCLUDED_)
