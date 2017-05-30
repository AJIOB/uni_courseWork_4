#pragma once
#include "MyException.h"

class RangeException : public MyException
{
public:
	RangeException() : MyException("Range exception. Maybe you were swap min an max value")
	{
	}
};
