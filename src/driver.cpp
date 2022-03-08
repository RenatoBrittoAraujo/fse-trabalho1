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
    std::string default_mode = "";

    while (default_mode != "yes" && default_mode != "no")
    {
        std::cout << "Would you like to use default values? (yes/no) (KI = 0.2  KP = 43  KD = 500)" << std::endl;
        std::cin >> default_mode;
        if (default_mode != "yes" && default_mode != "no")
        {
            std::cout << "Invalid option, ";
        }
    }

    if (default_mode == "yes")
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

void menu(int value = 0)
{
    for (;;)
    {
        std::cout << "Which control mode would you prefer?" << std::endl;
        std::cout << " - reflow" << std::endl;
        std::cout << " - potentiometer" << std::endl;
        std::cout << " - terminal" << std::endl;

        std::string control_mode;
        std::cin >> control_mode;
        std::cout << "Use CTRL + C to exit." << std::endl;

        if (control_mode == "reflow") {
            reflow_controller();
            continue;
        }

        if (control_mode == "potentiometer") {
            potentiometer_controller();
            continue;
        }

        if (control_mode == "terminal") {
            terminal_controller();
            continue;
        }

        std::cout << "Invalid option, try again" << std::endl;
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
