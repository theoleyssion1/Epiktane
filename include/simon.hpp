/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** simon
*/

#pragma once

#include "module.hpp"
#include <vector>
#include <map>


namespace KTANE {

    class Simon : public IModule {
        public:
            Simon();
            int initialize(std::string serial, int battery) override;
            void start() override;
            int stop() override;
            void display(Gui* gui, Rectangle rect) override;
            int getSerial(std::string serial) override;
            int getBattery(int battery) override;
            int getTime(int time) override;
            Color win() override;
            bool modError() override;
            void generateNextColor();
            bool checkInput(int colorIndex);
            void reset();
            void updateSequenceDisplay();
            bool isVowelInSerial(const std::string& serial);
            void drawButtons(Rectangle rect);
            int getButtonClicked(Vector2 mouse);
    
        private:
            std::string _serial;
            int _battery;
            bool _hasVowel;
            int _stage;
            bool _error;
            int _time;
            float _timer;
            int _inputIndex;
            bool _isShowingSequence;
            float _showTimer;
            size_t _showIndex;
            bool _playerTurn;
            bool _win;
            std::vector<int> _sequence;
            std::vector<Rectangle> _buttons;
            std::map<int, Color> _colors;
            std::map<int, Sound> _sounds;
        };

}