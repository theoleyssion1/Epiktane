/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** memory
*/

#pragma once
#include "raylib.h"
#include <string>
#include <array>
#include "module.hpp"

namespace KTANE {

    class Memory : public IModule {
    public:
        Memory();
        ~Memory() override = default;

        int initialize(std::string serial, int battery) override;
        void start() override;
        int stop() override;

        void display(Gui *gui, Rectangle rect) override;

        int getSerial(std::string serial) override;
        int getBattery(int batteries) override;
        int getTime(int time) override;

        Color win() override;
        bool modError() override;

        void generateStage();
        void processInput(int pressedPosition);
        void nextStage();

    private:
        int stage;
        bool solved;
        bool error;

        int displayNumber;
        std::array<int, 4> buttonLabels;
        std::array<int, 5> positionsPressed;
        std::array<int, 5> labelsPressed;

        std::string serial;
        int battery;

    };

}
