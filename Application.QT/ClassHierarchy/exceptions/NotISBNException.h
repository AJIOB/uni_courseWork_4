#pragma once

#include "MyException.h"

class NotISBNException : public MyException
{
public:
	NotISBNException() : MyException("This string is not ISBN number")
	{
	}
};
