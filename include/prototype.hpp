/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** prototype
*/

#pragma once

#include "defuser.hpp"

#define screenWidth 1920
#define screenHeight 1080

int checkifgui(int argc, char **argv);
int parsingtime(char **argv);
int parsingmodule(char **argv);
int parsingerror(char **argv);
KTANE::Defuser initDefuser(char **argv);
