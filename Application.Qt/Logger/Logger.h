#pragma once
#include <string>
#include <fstream>

class Logger
{
	std::fstream cl_f;
	std::string cl_way;

	static Logger* cl_singleton;

	Logger(const std::string& logWay = "logs.log");
	Logger(const Logger&);
	~Logger();

	bool open();
	void close();

public:
	static Logger& get();

	void write(const std::string& s);
};
