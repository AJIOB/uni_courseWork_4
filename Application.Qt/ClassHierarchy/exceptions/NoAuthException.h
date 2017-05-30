#pragma once

#include "MyException.h"

class NoAuthException : public MyException
{
public:
	NoAuthException() : MyException("You are not authorized in database")
	{
	}
};
