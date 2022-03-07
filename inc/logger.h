#ifndef LOGGER
#define LOGGER

#include <string>

class Logger
{
public:
    Logger();
    ~Logger();
    
    void log_temperature(float TI, float TR, float TE);
    void log_message(std::string mensagem);
    void kill_logger();

    static Logger get_instance();
    static Logger _instance;

private:
    std::ofstream file;
    std::string get_timestamp();
}

#endif