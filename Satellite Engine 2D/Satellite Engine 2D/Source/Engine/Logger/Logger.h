#pragma once

#include <string>

class Logger
{
	public:
		static void Log(const std::string& message);
		static void Warning(const std::string& message);
		static void Error(const std::string& message);
		static void Error(const std::string& message, const char* error);
};
