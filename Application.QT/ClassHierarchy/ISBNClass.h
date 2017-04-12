﻿#pragma once

#include "typedefs.h"

#include "ISBNOnePart.h"

class ISBNClass
{
	AJIOBTypes::ISBNType::ISBNType cl_type;
	ISBNOnePart cl_fields[AJIOB_Const::numOfISBNFields];

	uli CalculateISBN10CheckDigit() const;
	uli CalculateISBN13CheckDigit() const;

	ulli GetAsNumWithoutCheckDigit() const;

	bool ParseString(const std::string&);

public:
	ISBNClass();
	~ISBNClass();

	std::string GetAsString() const;

	bool operator==(const ISBNClass& that) const;
	bool operator!=(const ISBNClass& that) const;
	bool operator>(const ISBNClass& that) const;
	bool operator<(const ISBNClass& that) const;

	ISBNOnePart& operator[](const int index);
	const ISBNOnePart& operator[](const int index) const;
};