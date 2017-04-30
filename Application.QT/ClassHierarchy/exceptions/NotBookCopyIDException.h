#pragma once

#include "MyException.h"

class NotBookCopyIDException : public MyException
{
public:
	NotBookCopyIDException() : MyException("That ID is not BookCopy ID")
	{
	}
};
