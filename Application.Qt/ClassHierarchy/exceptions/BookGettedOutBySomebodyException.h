#pragma once

#include "MyException.h"

class BookGettedOutBySomebodyException : public MyException
{
public:
	BookGettedOutBySomebodyException() : MyException("Book was already getted out somebody. Try to archieve all it's copies")
	{
	}
};