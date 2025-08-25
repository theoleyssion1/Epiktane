/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** ktane
*/

#include "../include/ktane.hpp"
#include "../include/prototype.hpp"
#include <raylib.h>


App::App(int argc, char **argv)
:    _defuser(initDefuser(argv)),
    _gui()
{
    this->run();
}

App::~App()
{
}

int App::run()
{
    while(!WindowShouldClose()) {
        this->_gui.draw();
        this->_gui.pollEvent();
        if (this->_gui.getState() == KTANE::GUI_STATE::START) {
            this->_defuser.display(&_gui);
        }
        if (this->_gui.getState() == KTANE::GUI_STATE::PLAY) {
            if (this->_defuser.isActive() == false) {
                this->_defuser.start();
            }
            this->_defuser.pollEvent();
            if (this->_defuser.getState() == KTANE::STATE::DEFUSED) {
                this->_gui.changeScreen(KTANE::GUI_STATE::WIN);
            } else if (this->_defuser.getState() == KTANE::STATE::EXPLOSED) {
                this->_gui.changeScreen(KTANE::GUI_STATE::LOOSE);
            }
            this->_defuser.display(&_gui);
        } else if (this->_gui.getState() == KTANE::GUI_STATE::WIN) {
            this->_defuser.stop();
            this->_gui.drawWin();
            this->_defuser.display(&_gui);
        } else if (this->_gui.getState() == KTANE::GUI_STATE::MENU) {
            this->_defuser.reset();
        } else if (this->_gui.getState() == KTANE::GUI_STATE::WIN) {
            this->_defuser.stop();
        }
    }
    return 0;
}
