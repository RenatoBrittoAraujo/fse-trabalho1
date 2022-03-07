#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstddef>

#include "logger.h"
#include "driver.h"

Logger::Logger()
{
    if (!this->file.is_open())
    {
        this->file.open("./logs/logs.csv");
    }
}

Logger::~Logger()
{
    file.close();
}

Logger *Logger::get_instance()
{
    if (Logger::_instance == NULL)
    {
        Logger::_instance = new Logger();
    }
    return Logger::_instance;
}

void Logger::log_temperature(float ti, float tr, float te)
{

    this->file << this->get_timestamp() << ", " << ti << ", " << te << ", " << tr << '\n';
}

void Logger::log_message(std::string msg)
{
    if (!file.is_open())
    {
        this->file.open("./logs/logs.csv");
    }
    this->file << this->get_timestamp() << ',' << msg << '\n';
}

std::string Logger::get_timestamp()
{
    time_t time_now;
    time(&time_now);
    std::string timestamp = ctime(&time_now);
    timestamp.pop_back();
    return timestamp;
}
