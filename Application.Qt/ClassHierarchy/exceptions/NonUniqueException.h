#pragma once

#include "MyException.h"

class NonUniqueException : public MyException
{
public:
	NonUniqueException() : MyException("You are try to create element that already exist in database")
	{
	}
};
