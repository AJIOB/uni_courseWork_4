#include "stdafx.h"
#include "Date.h"

Date::Date(bool empty)
	: cl_isEmpty(empty)
{
	if (!empty)
	{
		cl_time = std::chrono::system_clock::now();
	}
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

int Date::getMilliseconds() const
{
	using namespace std::chrono;
	return (duration_cast<milliseconds>(cl_time.time_since_epoch()).count() - duration_cast<seconds> (cl_time.time_since_epoch()).count() * 1000);
}

std::string Date::toString(bool withMilliseconds) const
{
	if (cl_isEmpty)
	{
		return std::string();
	}
	
	auto in_time_t = std::chrono::system_clock::to_time_t(cl_time);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	if (withMilliseconds)
	{
		ss << "." << getMilliseconds();
	}
	return ss.str();
}
