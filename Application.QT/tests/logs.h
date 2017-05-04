#pragma once
#include <gtest/gtest.h>
#include "Logger/Logger.h"

TEST(CheckLogs, WriteFromTest)
{
	Logger::get().write("Hello from test");
}
