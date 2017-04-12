#pragma once
#include "MyException.h"

class RangeException : public MyException
{
public:
	RangeException() : MyException("Ошибка промежутка. Возможно, вы перепутали местами минимальное и максимальное значение")
	{
	}
};
