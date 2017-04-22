#pragma once

#include "MyException.h"

class GuestUpdateException : public MyException
{
public:
	GuestUpdateException() : MyException("You are trying to update guest account")
	{
	}
};
