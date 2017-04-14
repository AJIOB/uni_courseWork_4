#pragma once

#include "MyException.h"

class ConfigException : public MyException
{
public:
	ConfigException() : MyException("Ошибка файла конфигурации. Возможно, он быо поврежден")
	{
	}
};
