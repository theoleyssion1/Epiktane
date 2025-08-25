/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** morse
*/

#pragma once
#include <unordered_map>
#include "gui.hpp"
#include "module.hpp"

namespace KTANE {

    class Morse : public IModule {
    private:
        std::string _serial;
        int _batteryCount = 0;
        int _timeLeft = 0;
        bool _solved = false;
        bool _error = false;

        std::string _chosenWord;
        float _targetFrequency;

        float _userFrequency = 3.500f;
        const float _minFrequency = 3.500f;
        const float _maxFrequency = 3.600f;

        float _blinkTimer = 0.0f;
        float _blinkDelay = 0.3f;
        size_t _blinkIndex = 0;
        bool _isBlinking = true;

        std::string morseSequence;
        std::unordered_map<std::string, float> _wordToFreq;
        std::unordered_map<char, std::string> _morseTable;
        std::unordered_map<std::string, Button> _buttons;

        
        public:
        Morse();
        
        int initialize(std::string serial, int battery) override;
        void start() override;
        int stop() override;
        void display(Gui* gui, Rectangle rect) override;
        int getSerial(std::string serial) override;
        int getBattery(int batteries) override;
        int getTime(int time) override;
        Color win() override;
        bool modError() override;
        
        void initMorseTable();
        void chooseRandomWord();
        std::string wordToMorse(const std::string& word);
    };

}
