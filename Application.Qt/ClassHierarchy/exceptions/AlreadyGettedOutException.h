#pragma once

#include "MyException.h"

class AlreadyGettedOutException : public MyException
{
public:
	AlreadyGettedOutException() : MyException("You are trying to get out copy that already getted out")
	{
	}
};
