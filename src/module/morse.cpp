/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** morse
*/

#include "../../include/morse.hpp"
#include <ctime>
#include <random>
#include <cmath>
#include <raylib.h>
#include <vector>
#include <algorithm> // For std::clamp

namespace KTANE {

    Morse::Morse() {
        initMorseTable();
        _wordToFreq = {
            {"shell", 3.505f}, {"halls", 3.515f}, {"slick", 3.520f},
            {"trick", 3.530f}, {"boxes", 3.535f}, {"leaks", 3.540f},
            {"strobe", 3.545f}, {"bistro", 3.550f}, {"flick", 3.555f},
            {"bombes", 3.565f}, {"break", 3.570f}, {"brick", 3.575f},
            {"steak", 3.580f}, {"sting", 3.590f}, {"vector", 3.595f},
            {"beats", 3.600f}
        };
    }

    void Morse::initMorseTable() {
        _morseTable = {
            {'a', ".-"},   {'b', "-..."}, {'c', "-.-."}, {'d', "-.."},  {'e', "."},
            {'f', "..-."}, {'g', "--."},  {'h', "...."}, {'i', ".."},   {'j', ".---"},
            {'k', "-.-"},  {'l', ".-.."}, {'m', "--"},   {'n', "-."},   {'o', "---"},
            {'p', ".--."}, {'q', "--.-"}, {'r', ".-."},  {'s', "..."},  {'t', "-"},
            {'u', "..-"},  {'v', "...-"}, {'w', ".--"},  {'x', "-..-"}, {'y', "-.--"},
            {'z', "--.."}
        };
    }

    std::string Morse::wordToMorse(const std::string& word) {
        std::string morse;
        for (char c : word) {
            char lower = std::tolower(c);
            morse += _morseTable[lower] + " ";
        }
        return morse;
    }

    void Morse::chooseRandomWord() {
        std::vector<std::string> words;
        for (const auto& pair : _wordToFreq) {
            words.push_back(pair.first);
        }
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, words.size() - 1);
        _chosenWord = words[dist(rng)];
        _targetFrequency = _wordToFreq[_chosenWord];
        morseSequence = wordToMorse(_chosenWord);
        _blinkIndex = 0;
        _blinkTimer = 0.0f;
    }

    int Morse::initialize(std::string serial_, int battery_) {
        _serial = serial_;
        _batteryCount = battery_;
        chooseRandomWord();
        return 1;
    }

    void Morse::start() {
        // Placeholder
    }

    int Morse::stop() {
        return _solved ? 1 : 0;
    }

    int Morse::getSerial(std::string serial_) {
        _serial = serial_;
        return 1;
    }

    int Morse::getBattery(int batteries) {
        _batteryCount = batteries;
        return _batteryCount;
    }

    int Morse::getTime(int time) {
        _timeLeft = time;
        return time;
    }

    Color Morse::win() {
        return _solved ? GREEN : RED;
    }

    bool Morse::modError() {
        if (_error) {
            _error = false;
            return true;
        }
        return _error;
    }

    void Morse::display(Gui* gui, Rectangle rect) {

        if (_buttons.empty()) {
             Button button;
            button.InitButton(Rectangle{rect.x + 10, rect.y + 150, 20, 20}, "-");
            _buttons.insert({"-", button});
            button.InitButton(Rectangle{rect.x + 140, rect.y + 150, 20, 20}, "+");
            _buttons.insert({"+", button});
            button.InitButton(Rectangle{rect.x + 45, rect.y + 150, 80, 20}, "confirm");
            _buttons.insert({"val", button});
        }
        DrawRectangleRec(rect, LIGHTGRAY);
        DrawRectangle(rect.x + rect.width - 30, rect.y + 10, 20, 20, win());

        _blinkTimer += GetFrameTime();
        if (_blinkTimer > _blinkDelay) {
            _blinkTimer = -0.2f;
            _blinkIndex = (_blinkIndex + 1) % morseSequence.size();
        }

        char currentSymbol = morseSequence[_blinkIndex];
        Color flashColor = (currentSymbol == '.') ? YELLOW : (currentSymbol == '-') ? ORANGE : BLACK;

        DrawCircle(rect.x + 30, rect.y + 30, 15, flashColor);

        if (this->_buttons.at("+").UpdateButton() && !_solved) _userFrequency += 0.005f;
        if (this->_buttons.at("-").UpdateButton() && !_solved) _userFrequency -= 0.005f;
        _userFrequency = std::clamp(_userFrequency, _minFrequency, _maxFrequency);
        DrawText(TextFormat("F: %.3f MHz", _userFrequency), rect.x + 20, rect.y + 80, 20, WHITE);
        this->_buttons.at("+").DrawButton();
        this->_buttons.at("-").DrawButton();
        this->_buttons.at("val").DrawButton();
        // Check solution
        if (this->_buttons.at("val").UpdateButton() && !_solved){
            if (fabs(_userFrequency - _targetFrequency) < 0.0001f) {
                _solved = true;
            } else {
                _error = true; 
            
            }
        }
    }

}
