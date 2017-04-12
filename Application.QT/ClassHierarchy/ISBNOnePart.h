#pragma once

#include "typedefs.h"

struct ISBNOnePart
{
	uli ISBNpart;
	usi numOfElements;

	ISBNOnePart();

	std::string GetString() const;
	bool SetString(const std::string& num);

	bool operator==(const ISBNOnePart& that) const;
	bool operator!=(const ISBNOnePart& that) const;
	bool operator<(const ISBNOnePart& that) const;
	bool operator>(const ISBNOnePart& that) const;
};
