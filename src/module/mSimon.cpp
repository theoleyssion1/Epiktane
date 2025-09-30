/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** mSimon
*/
#include "../../include/simon.hpp"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <raylib.h>

namespace KTANE {

Simon::Simon()
{
    this->_win = false;
    this->_error = false;
    this->_inputIndex = 0;
    this->_isShowingSequence = true;
    this->_showTimer = 0.0f;
    this->_showIndex = 0;
    this->_playerTurn = false;
    this->_time = 0;
    this->_colors = {
        { 0, RED },
        { 1, BLUE },
        { 2, GREEN },
        { 3, YELLOW }
    };
    this->_buttons = std::vector<Rectangle>(4, {0, 0, 0, 0});
    std::srand(std::time(nullptr));
}

int Simon::initialize(std::string serial, int battery)
{
    this->_serial = serial;
    this->_battery = battery;
    this->_hasVowel = isVowelInSerial(serial);
    this->start();
    return 0;
}

int Simon::getSerial(std::string serial)
{
    this->_serial = serial;
    this->_hasVowel = isVowelInSerial(serial);
    return 0;
}

int Simon::getBattery(int battery)
{
    this->_battery = battery;
    return 0;
}

int Simon::getTime(int time)
{
    this->_time = time;
    return 0;
}

Color Simon::win()
{
    if (this->_win == true)
        return GREEN;
    return RED;
}

bool Simon::modError()
{
    if (this->_error) {
        this->_error = false;
        return true;
    }
    return false;
}

void Simon::start()
{
    this->reset();
    this->generateNextColor();
}

int Simon::stop()
{
    return 0;
}

void Simon::reset()
{
    this->_error = false;
    this->_inputIndex = 0;
    this->_isShowingSequence = true;
    this->_showIndex = 0;
    this->_showTimer = 0;
    this->_sequence.clear();
    this->_playerTurn = false;
}

void Simon::generateNextColor()
{
    this->_sequence.push_back(std::rand() % 4);
    this->_showIndex = 0;
    this->_isShowingSequence = true;
    this->_showTimer = 0;
    this->_inputIndex = 0;
    this->_playerTurn = false;
    if (this->_sequence.size() > 2)
        this->_win = true;
}

bool Simon::isVowelInSerial(const std::string& serial)
{
    for (char c : serial) {
        if (strchr("AEIOU", toupper(c))) return true;
    }
    return false;
}

bool Simon::checkInput(int colorIndex)
{
    if (this->_sequence.empty()) {
        this->_error = true;
        return false;
    }
    if (this->_inputIndex >= this->_sequence.size()) {
        this->_error = true;
        this->_inputIndex = 0;
        return false;
    }
    if (this->_sequence[this->_inputIndex] == colorIndex) {
        this->_inputIndex++;
        if (this->_inputIndex >= this->_sequence.size()) {
            this->generateNextColor();
        }
        return true;
    } else {
        this->_error = true;
        this->_inputIndex = 0;
        return false;
    }
}

void Simon::updateSequenceDisplay()
{
    if (this->_sequence.empty()) {
        this->_isShowingSequence = false;
        this->_playerTurn = true;
        return;
    }
    this->_showTimer += GetFrameTime();
    if (this->_showTimer >= 0.7f) {
        this->_showTimer = 0;
        this->_showIndex++;
        if (this->_showIndex >= this->_sequence.size()) {
            this->_showIndex = 0;
            this->_isShowingSequence = false;
            this->_playerTurn = true;
        }
    }
}

int Simon::getButtonClicked(Vector2 mouse)
{
    for (int i = 0; i < this->_buttons.size(); ++i) {
        if (CheckCollisionPointRec(mouse, this->_buttons[i])) return i;
    }
    return -1;
}

void Simon::drawButtons(Rectangle rect)
{
    float padding = 12;
    float btnSize = (rect.width - 3 * padding) / 2 - 10;
    Vector2 positions[4] = {
        {rect.x + padding, rect.y + padding + 5},
        {rect.x + 2 * padding + btnSize, rect.y + padding + 5},
        {rect.x + padding, rect.y + 2 * padding + btnSize + 5},
        {rect.x + 2 * padding + btnSize, rect.y + 2 * padding + btnSize + 5}
    };
    Vector2 mouse = GetMousePosition();
    for (int i = 0; i < 4; ++i) {
        Color col = this->_colors[i];
        if (this->_isShowingSequence && !this->_sequence.empty() && this->_sequence[this->_showIndex] == i && this->_win == false) {
            if (this->_showTimer < 0.35f) {
                col = BLACK;
            } else {
                col = Fade(this->_colors[i], 0.3f);
            }
        }
        Rectangle btnRect = {positions[i].x, positions[i].y, btnSize, btnSize};
        this->_buttons[i] = btnRect;
        if (!this->_isShowingSequence && this->_playerTurn && CheckCollisionPointRec(mouse, btnRect) && this->_win == false) {
            col = Fade(WHITE, 0.6f);
        }
        DrawRectangleRec(btnRect, col);
    }
}

void Simon::display(Gui* gui, Rectangle rect) {
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, LIGHTGRAY);
    DrawRectangle(rect.x + rect.width - 30, rect.y + 10, 20, 20, win());
    this->drawButtons(rect);
    if (this->_isShowingSequence && _win == false) {
        this->updateSequenceDisplay();
    }
    if (this->_playerTurn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && _win == false) {
        Vector2 mouse = GetMousePosition();
        int clicked = this->getButtonClicked(mouse);
        if (clicked != -1) {
            this->checkInput(clicked);
        }
    }
}

}
