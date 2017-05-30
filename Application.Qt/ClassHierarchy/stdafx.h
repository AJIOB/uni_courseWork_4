// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
#include <sstream>

#include "typedefs.h"

#include "ISBNType.h"
#include "Constants.h"

#include "AllExceptions.h"

#include "HashFuncs/hash/sha3.h"

#include "Logger/Date.h"
#include "Logger/Logger.h"

typedef SHA3 HashClass;
