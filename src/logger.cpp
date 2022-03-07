#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "driver.h"

std::ofstream file;

std::string get_timestamp()
{
    time_t time_now;
    time(&time_now);
    std::string timestamp = ctime(&time_now);
    timestamp.pop_back();
    return timestamp;
}

void init_logger()
{
    file.open("./logs/logs.csv");
}

void log_temperature(float TI, float TR, float TE)
{
    file << get_timestamp() << ',' << TI << ',' << TR << ',' << TE << '\n';
}

void log_message(std::string mensagem)
{
    file << get_timestamp() << ',' << mensagem << '\n';
}

void kill_logger()
{
    file.close();
}