#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "gpio.h"
#include "potenciometro.h"
#include "bme_aux.h"
#include "uart.h"
#include "display.h"
#include "logger.h"
#include "pid.h"
#include "driver.h"
#include "reflow.h"
#include "terminal.h"

// #define TEST_LOCAL

void config_input()
{
    int opcao = -1;
    while (opcao != 1 and opcao != 0)
    {
        std::cout << "Digite 0 para usar os valores padrões:\nKP:50\nKI:0.2\nKD:400" << std::endl;
        std::cout << "Digite 1 para configurar os valores" << std::endl;
        scanf(" %d", &opcao);
        switch (opcao)
        {
        case 0:
            return;
        case 1:
            break;
        default:
            std::cout << "Escolha uma opção válida" << std::endl;
            sleep(5);
            system("clear");
            break;
        }
    }

    system("clear");
    double kp, ki, kd;

    std::cout << "Configure os parâmetros do PID" << std::endl;

    std::cout << "Digite a constante de controle proporcional (kp): " << std::endl;
    std::cin >> kp;

    std::cout << "Digite a constante de controle integral (ki): " << std::endl;
    std::cin >> ki;

    std::cout << "Digite a constante de controle derivativo (kd): " << std::endl;
    std::cin >> kd;

    pid_configura_constantes(kp, ki, kd);
    system("clear");
}

void menu(int value = 0)
{

#ifndef TEST_LOCAL

    gpio_desliga_resistencia();
    gpio_desliga_ventoinha();

#endif

    while (1)
    {
        system("clear");
        int opcao = -1;
        std::cout << "Escolha o modo de controle:" << std::endl;
        std::cout << "  1 - Potenciometro" << std::endl;
        std::cout << "  2 - Curva reflow" << std::endl;
        std::cout << "  3 - Terminal" << std::endl;
        std::cout << "  9 - Terminar execução" << std::endl;

        scanf(" %d", &opcao);

        switch (opcao)
        {
        case 1:
            std::cout << "Pressione ctrl + \\ para sair desse modo e voltar ao menu" << std::endl;
            sleep(5);
            potenciometro_controle();
            break;
        case 2:
            std::cout << "Pressione ctrl + \\ para sair desse modo e voltar ao menu" << std::endl;
            sleep(5);
            reflow_controle();
            break;
        case 3:
            std::cout << "Pressione ctrl + \\ para sair desse modo e voltar ao menu" << std::endl;
            sleep(5);
            terminal_controle();
            break;
        case 9:
            return;
            break;
        default:
            std::cout << "Escolha uma opção válida..." << std::endl;
            sleep(5);
            break;
        }
    }
}

void kill_driver(int exit_code)
{
    std::cout << "Encerrando a execução do programa..." << std::endl;

#ifndef TEST_LOCAL

    display_imprime_string("Desligando...");
    gpio_desliga_resistencia();
    gpio_desliga_ventoinha();
    UART_encerra();
    display_imprime_string("Recompilando.");

#endif

    kill_logger();
    exit(std::min(exit_code, 1));
}

void initialize()
{

#ifndef TEST_LOCAL

    display_imprime_string("Carregando...");
    wiringPiSetup();
    UART_configura();
    bme_conecta();

#endif

    signal(SIGINT, kill_driver);
    signal(SIGQUIT, kill_driver);
    init_logger();
    config_input();
    menu();
    kill_driver(0);
}
