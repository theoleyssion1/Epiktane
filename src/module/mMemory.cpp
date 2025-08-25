/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** mMemory
*/

#include "../../include/memory.hpp"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <raylib.h>

namespace KTANE {

    Memory::Memory() : stage(0), solved(false), error(false), displayNumber(0), battery(0) {
        std::srand(std::time(nullptr));
    }

    int Memory::initialize(std::string serial, int battery) {
        this->serial = serial;
        this->battery = battery;
        nextStage();
        return 0;
    }

    int Memory::getSerial(std::string serial) {
        this->serial = serial;
        return 0;
    }

    int Memory::getBattery(int battery) {
        this->battery = battery;
        return 0;
    }

    int Memory::getTime(int time) {
        return time;
    }

    void Memory::start() {
        stage = 0;
        solved = false;
        error = false;
        nextStage();
    }

    int Memory::stop() {
        return solved ? 1 : 0;
    }

    Color Memory::win()
    {
        return solved ? GREEN : RED;
    }

    bool Memory::modError()
    {
        if (error) {
            error = false;
            return true;
        }
        return false;
    }

    void Memory::nextStage()
{
    if (stage >= 3) {
        solved = true;
        return;
    }

    displayNumber = std::rand() % 4 + 1;

    buttonLabels = {1, 2, 3, 4};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(buttonLabels.begin(), buttonLabels.end(), g);
}


void Memory::processInput(int pressedPosition)
{
    int pressedLabel = buttonLabels[pressedPosition];

    switch (stage) {
        case 0:
            switch (displayNumber) {
                case 1:
                case 2:
                    if (pressedPosition != 1) { error = true; return; }
                    break;
                case 3:
                    if (pressedPosition != 2) { error = true; return; }
                    break;
                case 4:
                    if (pressedPosition != 3) { error = true; return; }
                    break;
            }
            break;
        case 1:
            switch (displayNumber) {
                case 1:
                    if (pressedLabel != 4) { error = true; return; }
                    break;
                case 2:
                case 4:
                    if (pressedPosition != positionsPressed[0]) { error = true; return; }
                    break;
                case 3:
                    if (pressedPosition != 0) { error = true; return; }
                    break;
            }
            break;
        case 2:
            switch (displayNumber) {
                case 1:
                    if (pressedLabel != labelsPressed[1]) { error = true; return; }
                    break;
                case 2:
                    if (pressedLabel != labelsPressed[0]) { error = true; return; }
                    break;
                case 3:
                    if (pressedPosition != 2) { error = true; return; }
                    break;
                case 4:
                    if (pressedLabel != 4) { error = true; return; }
                    break;
            }
            break;

        default:
            error = true;
            return;
    }
    positionsPressed[stage] = pressedPosition;
    labelsPressed[stage] = pressedLabel;
    stage++;
    if (stage >= 3) {
        solved = true;
    } else {
        nextStage();
    }
}

    void Memory::display(Gui *gui, Rectangle rect) {
        DrawRectangleRec(rect, LIGHTGRAY);
        DrawRectangle(rect.x + 120, rect.y + 10, 20, 20, win());
        DrawText(std::to_string(displayNumber).c_str(), rect.x + rect.width / 2 - 20, rect.y + 22, 40, RAYWHITE);
        for (int i = 0; i < 4; ++i) {
            Rectangle btn = {rect.x + 20 + i * 30, rect.y + 80, 20, 20};
            DrawRectangleRec(btn, DARKGRAY);
            DrawText(std::to_string(buttonLabels[i]).c_str(), btn.x, btn.y + 20, 20, BLACK);
            if(CheckCollisionPointRec(GetMousePosition(), btn)) {
                DrawRectangleRec(btn, WHITE);
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), btn)) {
                if (!solved && !error)
                    processInput(i);
            }
        }
    }

}
