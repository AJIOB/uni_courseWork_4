///////////////////////////////////////////////////////////
//  User.cpp
//  Implementation of the Class User
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "User.h"


User::User(): privelege(guest)
{
}


User::~User()
{
}


bool User::CheckPassword(const String& password) const
{
	return (this->cryptedPassword == password);
}

bool User::SetPassword(const String& oldPassword, const String& newPassword)
{
	//todo
	return false;
}

void User::ResetPassword()
{
	//todo
}

DB_ID User::getId() const
{
	return _id;
}

void User::setId(const DB_ID& dbId)
{
	_id = dbId;
}

String User::getLogin() const
{
	return login;
}

void User::setLogin(const String& login)
{
	this->login = login;
}

String User::getCryptedPassword() const
{
	return cryptedPassword;
}

void User::setCryptedPassword(const String& cryptedPassword)
{
	this->cryptedPassword = cryptedPassword;
}

UserPriveleges User::getPrivelege() const
{
	return privelege;
}

void User::setPrivelege(const UserPriveleges privelege)
{
	this->privelege = privelege;
}

UserPersonalInfo User::getPersonalInfo() const
{
	return personalInfo;
}

void User::setPersonalInfo(const UserPersonalInfo& personalInfo)
{
	this->personalInfo = personalInfo;
}
