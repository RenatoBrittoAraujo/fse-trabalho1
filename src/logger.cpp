#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

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

Logger Logger::get_instance()
{
    if (!Logger::_instance)
    {
        Logger::_instance = Logger();
    }
    return Logger::_instance;
}

void Logger::log_temperature(float TI, float TR, float TE)
{

    file << this->get_timestamp() << ',' << TI << ',' << TR << ',' << TE << '\n';
}

void Logger::log_message(std::string mensagem)
{
    if (!file.is_open())
    {
        file.open("./logs/logs.csv");
    }
    file << this->get_timestamp() << ',' << mensagem << '\n';
}

std::string Logger::get_timestamp()
{
    time_t time_now;
    time(&time_now);
    std::string timestamp = ctime(&time_now);
    timestamp.pop_back();
    return timestamp;
}
