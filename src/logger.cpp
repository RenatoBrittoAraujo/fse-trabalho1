#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "driver.h"

static std::ofstream arquivo;
static std::string tempo_agora;

void logger_get_tempo()
{
    time_t time_now;
    time(&time_now);
    tempo_agora = ctime(&time_now);
    tempo_agora.pop_back();
}

void logger_inicia()
{
    logger_get_tempo();
    arquivo.open("./logs/logs.csv");
}

void logger_escreve_temp(float TI, float TR, float TE)
{
    logger_get_tempo();
    arquivo << tempo_agora << ',' << TI << ',' << TR << ',' << TE << '\n';
}

void logger_escreve_string(std::string mensagem)
{
    logger_get_tempo();
    arquivo << tempo_agora << ',' << mensagem << '\n';
}

void logger_encerra()
{
    arquivo.close();
}