/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** wire
*/

#pragma once
#include "module.hpp"
#include "gui.hpp"
#include <raylib.h>
#include <vector>

namespace KTANE {

    class Wire : public IModule {
        public:
            Wire();
            int initialize(std::string serial, int battery) override;
            void start() override;
            int stop() override;
            Color win() override;
            int getSerial(std::string serial) override;
            int getBattery(int batteries) override;
            int getTime(int time) override;
            void display(Gui *gui, Rectangle rect) override;
            bool modError() override;
            
            int check_result();
            void setWires();
            int getWire();
            void setColor();
            void countColor();
            
            std::vector<Color> getColor();
            void update(Rectangle wire, int i);
            
            int correctWire();
            int getLastIndexOfColor(Color target);
        private:
            int _serialLastDigit;
            int _nbrOfWires;
            std::vector<Color> _colorOfWires;
            bool _err;
            bool _win;
            int _countRed, _countBlue, _countYellow, _countWhite, _countBlack;
            std::string _serial;
            int _battery;
    };
}

