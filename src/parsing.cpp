/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** parsing
*/

#include "../include/defuser.hpp"
#include <string>

int checkifgui(int argc, char **argv)
{
    if (argc < 7 || argc > 8)
        return 84;
    for(int i = 0; argv; i++) {
        if (argv[i] == NULL)
            return 0;
        std::string temp = argv[i];
        if (temp.compare("-g") == 0)
            return 1;
    }
    return 0;
}

// Parse the time from the command line arguments
int parsingtime(char **argv)
{
    int time;
    for(int i = 0; argv; i++) {
        std::string temp = argv[i];
        if (temp.compare("-t") == 0) {
            time = std::stoi(argv[i + 1]);
            if (time > 3600)
                return 3600;
            return time;
        }
    }
    return -1;
}

// Parse the number of modules from the command line arguments
int parsingmodule(char **argv)
{
    int mod;
    for(int i = 0; argv; i++) {
        std::string temp = argv[i];
        if (temp.compare("-m") == 0) {
            mod = std::stoi(argv[i + 1]);
            if (mod > 11)
                return 11;
            return mod;
        }
    }
    return -1;
}

// Parse the maximum number of errors allowed
int parsingerror(char **argv)
{
    int error;
    for(int i = 0; argv; i++) {
        std::string temp = argv[i];
        if (temp.compare("-e") == 0) {
            error = std::stoi(argv[i + 1]);
            return error;
        }
    }
    return -1;
}

// Initialize the defuser with the parsed arguments
KTANE::Defuser initDefuser(char **argv)
{
    int time = parsingtime(argv);
    int module = parsingmodule(argv);
    int error = parsingerror(argv);
        if (time <=0)
            time = 60;
        if (module <=0)
            module = 3;
        if (error <=0)
            error = 3;
    return KTANE::Defuser(time, module, error);
}
