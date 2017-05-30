#pragma once

#include "MyException.h"

class DBOperationCancelledException : public MyException
{
public:
	DBOperationCancelledException() : MyException("Error. Operation was cancelled")
	{
	}
};
