#pragma once
#include <chrono>

#include "typedefs.h"

class Date
{
	bool cl_isEmpty;
	std::chrono::system_clock::time_point cl_time;

public:
	Date();
	explicit Date(const std::chrono::system_clock::time_point& time);


	bool isEmpty() const;
	std::chrono::system_clock::time_point getTime() const;
	void setTime(const std::chrono::system_clock::time_point& time);

	String toString() const;
};
