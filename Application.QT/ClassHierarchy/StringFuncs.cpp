#include "stdafx.h"
#include "StringFuncs.h"

void AJIOBStringFuncs::Invert(std::string& str)
{
	for (int i = 0, j = str.size() - 1; i < j; i++ , j--)
	{
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}

std::vector<std::string> AJIOBStringFuncs::BreakStringToArrayOfStrings(const std::string& str, const char devider)
{
	std::vector<std::string> result;
	std::string buff;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if ((*it) == devider)
		{
			result.push_back(buff);
			buff.clear();
			continue;
		}

		buff.push_back(*it);
	}

	result.push_back(buff);

	return result;
}

void AJIOBStringFuncs::BreakStringTo2Strings(const std::string str, std::string& leftResult, std::string& rightResult, const char devider)
{
	leftResult = "";
	rightResult = "";

	bool isFind = false;

	std::string* writeptr = &leftResult;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if ((*it) == devider && !isFind)
		{
			isFind = true;
			writeptr = &rightResult;
			continue;
		}

		writeptr->push_back(*it);
	}
}
