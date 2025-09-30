/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** mButton
*/

#include "../../include/buttonModule.hpp"
#include <cstdlib>
#include <ctime>
#include <raylib.h>

KTANE::ButtonModule::ButtonModule()
    : _color("red"), _label("PRESS"), _isHeld(false), _solved(false), _error(false), _buttonInit(false), _timerStarted(false), _battery(0)
{
}

int KTANE::ButtonModule::initialize(const std::string serial, int battery) {
    _serial = serial;
    _battery = battery;
    _isHeld = false;
    _solved = false;
    _error = false;
    _buttonInit = false;
    _timerStarted = false;
    generateButton();
    return 0;
}

void KTANE::ButtonModule::generateButton() {
    const std::string colors[] = {"red", "blue", "white", "yellow"};
    const std::string labels[] = {"PRESS", "HOLD", "ABORT", "DETONATE"};
    _color = colors[std::rand() % 4];
    _label = labels[std::rand() % 4];
}

void KTANE::ButtonModule::start() {
    ButtonAction action = resolveButtonLogic();
    if (action == TAP_IMMEDIAT) {
        _solved = true;
    } else if (action == MAINTENIR) {
        _isHeld = true;
    } else {
        _error = true;
    }
}

int KTANE::ButtonModule::stop() {
    return _solved ? 0 : 1;
}

void KTANE::ButtonModule::display(KTANE::Gui *gui, Rectangle rect)
{
    if (!_buttonInit) {
        _button.InitButton(
            Rectangle{rect.x + 30, rect.y + 30, 120, 120},
            _label,
            _color == "red" ? RED :
            _color == "blue" ? BLUE :
            _color == "white" ? WHITE : YELLOW
        );
        _buttonInit = true;
    }
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, LIGHTGRAY);
    DrawRectangle(rect.x + rect.width - 30, rect.y + 10, 20, 20, win());
    _button.UpdateButton();
    if (_button.isPressed() && !_solved && !_isHeld && !_timerStarted) {
        start();
    }
    if (_isHeld) {
        if (!_button.isPressed() && _timerStarted) {
            if (_timer.IsTimerFinished()) {
                _solved = true;
            } else {
                _error = true;
            }
            _timerStarted = false;
        }
    }

    _button.DrawButton();
}

int KTANE::ButtonModule::getSerial(const std::string serial) {
    _serial = serial;
    return 0;
}

int KTANE::ButtonModule::getBattery(int batteries)
{
    _battery = batteries;
    return 0;
}

int KTANE::ButtonModule::getTime(int time)
{
    _timeLeft = time;
    return 0;
}

Color KTANE::ButtonModule::win() {
    return _solved ? GREEN : RED;
}

bool KTANE::ButtonModule::modError()
{
    if (_error) {
        _error = false;
        _isHeld = false;
        return true;
    }
    return false;
}

bool KTANE::ButtonModule::shouldHold() {
    return (_color == "blue" && _label == "ABORT") || (_label == "HOLD");
}

ButtonAction KTANE::ButtonModule::resolveButtonLogic() {

    if (_battery > 1 && _label == "DETONATE") {
        return TAP_IMMEDIAT;
    }
    if (_color == "red" && _label == "HOLD") {
        return TAP_IMMEDIAT;
    }

    if (_color == "blue" && _label == "ABORT") {
        _timer.startTimer(4.0f);
        _timerStarted = true;
        return MAINTENIR;
    }
    if (_color == "white") {
        _timer.startTimer(1.0f);
        _timerStarted = true;
        return MAINTENIR;
    }
    if (_battery > 2) {
        return TAP_IMMEDIAT;
    }
    if (_color == "yellow") {
        _timer.startTimer(5.0f);
        _timerStarted = true;
        return MAINTENIR;
    }

    _timer.startTimer(1.0f);
    _timerStarted = true;
    return MAINTENIR;
}
