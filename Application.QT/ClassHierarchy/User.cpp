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


bool User::isPasswordCorrect(const String& password) const
{
	HashClass hash;
	return (cryptedPassword == hash(password));

}

bool User::SetPassword(const String& oldPassword, const String& newPassword)
{
	if (!isPasswordCorrect(oldPassword))
	{
		return false;
	}

	HashClass hash;
	cryptedPassword = hash(newPassword);
	return true;
}

void User::ResetPassword()
{
	HashClass hash;
	cryptedPassword = hash(login);
}

DB_ID User::getId() const
{
	return _id;
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
