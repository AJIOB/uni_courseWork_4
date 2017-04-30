#pragma once

#include "MyException.h"

class NotGettedOutException : public MyException
{
public:
	NotGettedOutException() : MyException("You are trying to return copy that not already getted out")
	{
	}
};
