#ifndef LOG_H_
#define LOG_H_

#include <string>

void log_temperature(float TI, float TR, float TE);
void log_message(std::string mensagem);
void kill_logger();
void init_logger();

#endif