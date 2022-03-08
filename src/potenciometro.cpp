#include <unistd.h>

#include "logger.h"
#include "display.h"
#include "bme_aux.h"
#include "uart.h"
#include "gpio.h"
#include "pid.h"

#define TEMP_INTERNA 0xC1
#define TEMP_POTENCIOMETRO 0xC2

void potentiometer_controller()
{
    double ti, tr, te, i = 0;
    Logger *logger = Logger::get_instance();
    for(;;)
    {
        ti = UART_solicita<float>(TEMP_INTERNA);
        i = pid_controle(ti);
        gpio_controle_temperatura(i);

        tr = UART_solicita<float>(TEMP_POTENCIOMETRO);
        pid_atualiza_referencia(tr);

        te = bme_temperatura_atual();
        
        logger->log_temperature(ti, tr, te);


        display_imprime_temp(ti, tr, te, "PID ");
        sleep(1);
    }
}