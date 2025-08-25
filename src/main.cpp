/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** main
*/

#include "../include/ktane.hpp"
#include "../include/prototype.hpp"
#include <iostream>

int main(int argc, char **argv)
{

    int temp = checkifgui(argc, argv);
    if (temp == 84) {
        std::cout << "USAGE\n\t./epi_ktane -t <int> -m <int> -e <int> <-g>\n" <<
        "\t-t : time in seconds" <<
        "\t-m : number of modules" <<
        "\t-e : number of errors" <<
        "\t-g : graphical interface" << std::endl;
        return 84;
    }

    App app(argc, argv);
    return 0;
}
