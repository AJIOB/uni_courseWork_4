#pragma once

#include "MyException.h"

class AlreadyArchievedException : public MyException
{
public:
	AlreadyArchievedException() : MyException("You are trying to get out copy that already archieved")
	{
	}
};
