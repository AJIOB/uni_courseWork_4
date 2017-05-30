#pragma once

#include "MyException.h"

class UserGetOutSomethingException : public MyException
{
public:
	UserGetOutSomethingException() : MyException("User already get out something")
	{
	}
};
