#pragma once

#include <string>
#include <map>
#include <fstream>

namespace AJIOB
{
	class ConfigClass;
}

class AJIOB::ConfigClass
{
	const std::string cl_fileName;
	static const std::string cl_folder;// = "config\\";
	static const std::string cl_extension;// = ".ini";

	std::map<std::string, std::string> cl_configData;

	bool LoadData();

	//block for copying class
	ConfigClass(const ConfigClass&)
	{
	}

public:

	ConfigClass(const std::string& fileName = "default");

	std::string GetFileName() const;

	//return value by key. If cannot find key, return empty string
	std::string Get(const std::string& key) const;
	std::string operator[](const std::string& key) const;
};
