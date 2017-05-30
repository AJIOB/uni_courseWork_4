#pragma once
#include <exception>
#include <string>

class MyException : public std::exception
{
public:
	MyException();
	MyException(const char* const& errorText);
	MyException(const std::string errorText);
};
