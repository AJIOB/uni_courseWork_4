#include "stdafx.h"
#include "MyException.h"

MyException::MyException():exception()
{
	//OutputLog("Error. No error text", true);
	//todo: fix
}

MyException::MyException(const char* const& errorText):exception(errorText)
{
	//OutputLog("Error. Error text: " + std::string(errorText), true);
	//todo: fix
}

MyException::MyException(const std::string errorText):exception(errorText.c_str())
{
	//OutputLog("Error. Error text: " + errorText, true);
	//todo: fix
}
