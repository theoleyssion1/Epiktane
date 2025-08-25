/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** buttonModule
*/

#pragma once
#include "gui.hpp"
#include "module.hpp"
#include "timer.hpp"
#include <string>


enum ButtonAction {
    TAP_IMMEDIAT,
    MAINTENIR,
    ACTION_INVALIDE
};

namespace KTANE {

    class ButtonModule : public KTANE::IModule {
        
        public:
            ButtonModule();
            virtual ~ButtonModule() = default;

            int initialize(std::string serial, int battery) override;
            void start() override;
            int stop() override;
            void display(KTANE::Gui *gui, Rectangle rect) override;
            int getSerial(std::string serial) override;
            int getBattery(int battery) override;
            int getTime(int time) override;
            Color win() override;
            bool modError() override;

            ButtonAction resolveButtonLogic();
            void generateButton();
            bool shouldHold();
        private:
            std::string _color;
            std::string _label;
            std::string _serial;
            bool _isHeld;
            bool _solved;
            bool _error;
            bool _buttonInit;
            Button _button;
            int _battery;
            Timer _timer;
            bool _timerStarted = false;
            bool _err = false;
            int _timeLeft = 0;
    };
    
}