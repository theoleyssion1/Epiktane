/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** ktane
*/

#include "defuser.hpp"
#include "gui.hpp"

#pragma once

class App {
    public:
        App(int argc, char **argv);
        ~App();

        int run();
    private:
        KTANE::Defuser _defuser;
        KTANE::Gui _gui;
    
};