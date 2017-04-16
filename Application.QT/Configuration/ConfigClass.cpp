#include "ConfigClass.h"

//init static const
const std::string AJIOB::ConfigClass::cl_folder = "config\\";
const std::string AJIOB::ConfigClass::cl_extension = ".ini";

bool AJIOB::ConfigClass::LoadData()
{
	std::fstream f;
	f.open(cl_folder + cl_fileName + cl_extension, std::ios::in | std::ios::ate);

	if (!f)
	{
		return false;
	}

	unsigned maxSize = static_cast<unsigned>(f.tellg()) + 2;
	char* tmpS = new(std::nothrow) char[maxSize];
	if (!tmpS)
	{
		f.close();
		return false;
	}

	std::pair<std::string, std::string> pairToLoadFromFile;

	bool res = true;

	//set flag to start pos to read
	f.seekg(0);
	while (f)
	{
		//read & save key
		f.getline(tmpS, maxSize, '=');
		if (!f)
		{
			break;
		}

		std::string s(tmpS);

		//delete '\n' at the end
		while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == '='))
			s.pop_back();

		//delete \r && \n at the beginning of the line
		while (!s.empty() && (s.front() == '\n' || s.front() == '\r'))
			s.erase(0, 1);

		if (s.empty())
		{
			continue;
		}

		pairToLoadFromFile.first = s;

		//read & save value
		f.getline(tmpS, maxSize);
		if (!f)
		{
			res = false;
			break;
		}

		s = std::string(tmpS);

		//delete '\n' at the end
		while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == '='))
			s.pop_back();

		pairToLoadFromFile.second = s;

		cl_configData.insert(pairToLoadFromFile);
	}

	//free memory & close the file
	delete[] tmpS;
	f.close();
	return res;
}

AJIOB::ConfigClass::ConfigClass(const std::string& fileName) : cl_fileName(fileName)
{
	LoadData();
}

std::string AJIOB::ConfigClass::GetFileName() const
{
	return cl_fileName;
}

std::string AJIOB::ConfigClass::Get(const std::string& key) const
{
	auto resIt = cl_configData.find(key);
	if (resIt == cl_configData.end())
	{
		return std::string();
	}

	return resIt->second;
}

std::string AJIOB::ConfigClass::operator[](const std::string& key) const
{
	return Get(key);
}
