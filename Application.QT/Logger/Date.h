#pragma once
#include <chrono>
#include <string>

class Date
{
	bool cl_isEmpty;
	std::chrono::system_clock::time_point cl_time;

public:
	Date(bool empty = true);
	explicit Date(const std::chrono::system_clock::time_point& time);


	bool isEmpty() const;
	std::chrono::system_clock::time_point getTime() const;
	void setTime(const std::chrono::system_clock::time_point& time);

	int getMilliseconds() const;
	std::string toString(bool withMilliseconds = false) const;
};
