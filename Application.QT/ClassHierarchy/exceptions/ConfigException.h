#pragma once

#include "MyException.h"

class ConfigException : public MyException
{
public:
	ConfigException() : MyException("Configuration file error. Maybe it was damaged")
	{
	}
};
