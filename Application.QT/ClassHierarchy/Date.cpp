#include "stdafx.h"
#include "Date.h"

Date::Date()
	: cl_isEmpty(true)
{
}

Date::Date(const std::chrono::system_clock::time_point& time)
	: cl_isEmpty(false), cl_time(time)
{
}

bool Date::isEmpty() const
{
	return cl_isEmpty;
}

std::chrono::system_clock::time_point Date::getTime() const
{
	return cl_isEmpty ? std::chrono::system_clock::time_point() : cl_time;
}

void Date::setTime(const std::chrono::system_clock::time_point& time)
{
	cl_time = time;
	cl_isEmpty = false;
}

String Date::toString() const
{
	if (cl_isEmpty)
	{
		return String();
	}

	auto in_time_t = std::chrono::system_clock::to_time_t(cl_time);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	return ss.str();
}
