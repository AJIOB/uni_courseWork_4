#include "stdafx.h"
#include "Logger.h"
#include "Date.h"

Logger* Logger::cl_singleton = nullptr;

Logger::Logger(const std::string& logWay) : cl_way(logWay)
{
}

Logger::Logger(const Logger&)
{
}

Logger::~Logger()
{
	if (cl_singleton)
	{
		delete cl_singleton;
	}
}

bool Logger::open()
{
	cl_f.open(cl_way, std::ios::out | std::ios::app);
	return static_cast<bool>(cl_f);
}

void Logger::close()
{
	cl_f.close();
}

Logger& Logger::get()
{
	if (!cl_singleton)
	{
		cl_singleton = new Logger;
	}

	return *cl_singleton;
}

void Logger::write(const std::string& s)
{
	if (!open())
	{
		return;
	}

	cl_f << Date(false).toString(true) << ": " << s << std::endl;

	close();
}
