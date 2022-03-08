#include <stdio.h>
#include "pid.h"

double saida_medida, sinal_de_controle;
double reference = 0.0;
double kp = 0.0;
double ki = 0.0;
double kd = 0.0;
int T = 1.0;
unsigned long last_time;
double error_total, previous_error = 0.0;
int signal_MAX = 100.0;
int signal_MIN = -100.0;

void set_params(double user_ki, double user_kp, double user_kd)
{
    kp = user_kp;
    ki = user_ki;
    kd = user_kd;
}

void pid_atualiza_referencia(float referencia_)
{
    reference = (double)referencia_;
}

double pid_controle(double saida_medida)
{
    double error = reference - saida_medida;

    error_total += error; // Acumula o error (Termo Integral)

    if (error_total >= signal_MAX)
    {
        error_total = signal_MAX;
    }
    else if (error_total <= signal_MIN)
    {
        error_total = signal_MIN;
    }

    double delta_error =
        error - previous_error; // Diferença entre os erros (Termo Derivativo)

    sinal_de_controle = kp * error + (ki * T) * error_total +
                        (kd / T) * delta_error; // PID calcula sinal de controle

    if (sinal_de_controle >= signal_MAX)
    {
        sinal_de_controle = signal_MAX;
    }
    else if (sinal_de_controle <= signal_MIN)
    {
        sinal_de_controle = signal_MIN;
    }

    previous_error = error;

    return sinal_de_controle;
}
