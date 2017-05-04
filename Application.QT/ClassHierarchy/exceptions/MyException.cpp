#include "stdafx.h"
#include "MyException.h"

MyException::MyException(): exception()
{
	Logger::get().write("Error. No error text");
}

MyException::MyException(const char* const& errorText): exception(errorText)
{
	Logger::get().write("Error. Error text: " + std::string(errorText));
}

MyException::MyException(const std::string errorText): exception(errorText.c_str())
{
	Logger::get().write("Error. Error text: " + errorText);
}
