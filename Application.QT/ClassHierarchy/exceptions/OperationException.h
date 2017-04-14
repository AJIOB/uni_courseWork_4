#pragma once

#include "MyException.h"

class OperationException : public MyException
{
public:
	OperationException() : MyException("Ошибка выполнения операции")
	{
	}
};
