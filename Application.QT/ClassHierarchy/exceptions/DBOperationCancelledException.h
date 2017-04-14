#pragma once

#include "MyException.h"

class DBOperationCancelledException : public MyException
{
public:
	DBOperationCancelledException() : MyException("Ошибка. Была произведена отмена операции")
	{
	}
};
