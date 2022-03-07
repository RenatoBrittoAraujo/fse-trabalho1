#include <unistd.h>

#include "logger.h"
#include "display.h"
#include "bme_aux.h"
#include "uart.h"
#include "gpio.h"
#include "pid.h"

#define TEMP_INTERNA 0xC1
#define TEMP_POTENCIOMETRO 0xC2

void potenciometro_controle()
{
    double ti, tr, te, i = 0;
    Logger *logger = Logger::get_instance();
    while (1)
    {
        ti = UART_solicita<float>(TEMP_INTERNA);

        i = pid_controle(ti);
        gpio_controle_temperatura(i);

        tr = UART_solicita<float>(TEMP_POTENCIOMETRO);

        pid_atualiza_referencia(tr);

        te = bme_temperatura_atual();

        display_imprime_temp(ti, tr, te, "PID ");
        logger->log_temperature(ti, tr, te);

        sleep(1);
    }
}