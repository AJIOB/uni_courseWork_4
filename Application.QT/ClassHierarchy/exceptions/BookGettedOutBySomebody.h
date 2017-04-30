#pragma once

#include "MyException.h"

class BookGettedOutBySomebody : public MyException
{
public:
	BookGettedOutBySomebody() : MyException("Book was already getted out somebody. Try to archieve all it's copies")
	{
	}
};