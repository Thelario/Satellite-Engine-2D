#include <chrono>
#include <ctime>
#include <iostream>

#include "Logger.h"

std::string CurrentDateTimeToString()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    localtime_s(&local_tm, &now_time);
    char time_buffer[80];
    std::strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", &local_tm);
    return time_buffer;
}

void Logger::Log(const std::string& message)
{
    std::string date = CurrentDateTimeToString();

    std::cout << "LOG - " << date << " - " << message << std::endl;
}

void Logger::Warning(const std::string& message)
{
    std::string date = CurrentDateTimeToString();

    std::cout << "WARNING - " << date << " - " << message << std::endl;
}

void Logger::Error(const std::string& message)
{
    std::string date = CurrentDateTimeToString();

    std::cout << "ERROR - " << date << " - " << message << std::endl;
}

void Logger::Error(const std::string& message, const char* error)
{
    std::string date = CurrentDateTimeToString();

    std::cout << "ERROR - " << date << " - " << message << ": " << error << std::endl;
}