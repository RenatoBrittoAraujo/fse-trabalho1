#include <fstream>
#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <tuple>
#include "driver.h"
#include "gpio.h"
#include "logger.h"
#include "uart.h"
#include "pid.h"
#include "display.h"
#include "bme_aux.h"

#define TEMP_INTERNA 0xC1

std::ifstream file;
std::vector<std::tuple<int, float>> valores;
static int mod;

void reflow_initialize()
{
    file.open("./assets/reflow.csv");
    std::string line, temp, time;
    file >> line;

    while (file >> line)
    {
        std::stringstream ss(line);
        std::getline(ss, time, ',');
        std::getline(ss, temp, '\n');
        valores.push_back(std::make_tuple(stoi(time), stof(temp)));
    }
    file.close();
    std::sort(valores.begin(), valores.end());
    float _t;
    std::tie(mod, _t) = valores.back();
}

bool update_tr(float &TR, int &current_time)
{
    int index = std::upper_bound(valores.begin(), valores.end(), std::make_tuple(current_time % mod, 0.0)) - valores.begin();
    index--;
    int _time;
    std::tie(_time, TR) = valores[index];
    current_time++;
    if (current_time > 3600)
        return false;
    return true;
}

void reflow_controller()
{
    Logger *logger = Logger::get_instance();

    reflow_initialize();
    float TR, TI, TE;
    double intensidade;
    int current_time = 0;

    while (update_tr(TR, current_time))
    {
        TI = UART_solicita<float>(TEMP_INTERNA);
        intensidade = pid_controle(TI);
        gpio_controle_temperatura(intensidade);
        pid_atualiza_referencia(TR);
        TE = bme_temperatura_atual();
        display_imprime_temp(TI, TR, TE, "REFLOW ");
        logger->log_temperature(TI, TR, TE);
        std::string message = "Tempo: " + std::to_string(current_time) + ",TR: " + std::to_string(TR);
        logger->log_temperature(TI, TR, TE);
        sleep(1);
    }
}