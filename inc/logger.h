#ifndef LOGGER
#define LOGGER

#include <string>
#include <fstream>
#include <cstddef>

class Logger
{
public:

    Logger();
    ~Logger();
    
    void log_temperature(float ti, float tr, float te);
    void log_message(std::string msg);

    static Logger *get_instance();
    static Logger *_instance;

private:

    std::ofstream file;
    std::string get_timestamp();
};

#endif