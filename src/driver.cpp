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

void config_input()
{
    std::string option = "";

    while (option != "yes" && option != "no")
    {
        std::cout << "Would you like to use default values?: (KI = 0.2  KP = 43  KD = 500)" << std::endl;
        std::cin << option;
        if (option != "yes" && option != "no")
        {
            std::cout << "Invalid option, ";
        }
    }

    if (option == "yes")
    {
        return;
    }

    double kp, ki, kd;
    std::cout << "Value for KI: ";
    std::cin >> ki;

    std::cout << "Value for KD: ";
    std::cin >> kd;

    std::cout << "Value for KP: ";
    std::cin >> kp;

    set_params(ki, kp, kd);
}

void

    void
    menu(int value = 0)
{
    for (;;)
    {
        system("clear");

        std::cout << "Which control mode would you prefer?" << std::endl;
        std::cout << " - reflow" << std::endl;
        std::cout << " - potentiometer" << std::endl;
        std::cout << " - terminal" << std::endl;

        std::string opcao = -1;
        std::cin >> opcao;
        std::cout << "Use CTRL + C to exit." << std::endl;

        switch (opcao)
        {
        case "reflow":
            reflow_controller();
            break;
        case "potentiometer":
            potentiometer_controller();
            break;
        case "terminal":
            terminal_controller();
            break;
        default:
            std::cout << "Invalid option, try again" << std::endl;
            break;
        }
    }
}

void kill_driver(int exit_code)
{
    std::cout << "Exiting..." << std::endl;
    Logger *logger = Logger::get_instance();

    logger->~Logger();
    exit(std::min(exit_code, 1));
}

void initialize()
{
    signal(SIGINT, kill_driver);
    signal(SIGQUIT, kill_driver);
    config_input();
    menu();
    kill_driver(0);
}
