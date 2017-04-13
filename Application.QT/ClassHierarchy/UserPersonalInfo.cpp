///////////////////////////////////////////////////////////
//  UserPersonalInfo.cpp
//  Implementation of the Class UserPersonalInfo
//  Created on:      13-апр-2017 16:45:59
//  Original author: Alex
///////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserPersonalInfo.h"


UserPersonalInfo::UserPersonalInfo()
{
}


UserPersonalInfo::~UserPersonalInfo()
{
}

String& UserPersonalInfo::getName()
{
	return name;
}

void UserPersonalInfo::setName(const String& name)
{
	this->name = name;
}

String& UserPersonalInfo::getSurname()
{
	return surname;
}

void UserPersonalInfo::setSurname(const String& surname)
{
	this->surname = surname;
}

String& UserPersonalInfo::getFatherName()
{
	return fatherName;
}

void UserPersonalInfo::setFatherName(const String& fatherName)
{
	this->fatherName = fatherName;
}

String& UserPersonalInfo::getPassportNumber()
{
	return passportNumber;
}

void UserPersonalInfo::setPassportNumber(const String& passportNumber)
{
	this->passportNumber = passportNumber;
}
