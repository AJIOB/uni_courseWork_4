#pragma once

#include "stdafx.h"

namespace AJIOBStringFuncs
{
	void Invert(std::string& str);

	std::vector<std::string> BreakStringToArrayOfStrings(const std::string& str, const char devider = ' ');
	void BreakStringTo2Strings(const std::string str, std::string& leftResult, std::string& rightResult, const char devider = ' ');
}
