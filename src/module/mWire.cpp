/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** wire
*/

#include "../../include/wire.hpp"
#include "../../include/defuser.hpp"
#include <cstdlib>
#include <ctime>
#include <raylib.h>

KTANE::Wire::Wire()
{

}

int KTANE::Wire::initialize(std::string serial, int battery)
{
    this->setWires();
    this->setColor();
    this->_err = 0;
    this->_win = 0;
    this->_serial = serial;
    this->_battery = battery;
    return 0;
}

void KTANE::Wire::start()
{

}

int KTANE::Wire::stop()
{
    return 0;
}

int KTANE::Wire::getSerial(std::string serial)
{
    for (int i = serial.length() - 1; i >= 0; --i) {
        if (std::isdigit(serial[i])) {
            this->_serialLastDigit = serial[i] - '0';
            return 0;
        }
    }
    return -1;
}

void KTANE::Wire::setWires()
{
    this->_nbrOfWires = 3 + std::rand() % 4;
}

int KTANE::Wire::getWire()
{
    return this->_nbrOfWires;
}

void KTANE::Wire::setColor() {
    this->_colorOfWires.clear();

    for (int i = 0; i < this->_nbrOfWires; ++i) {
        int tempColor = std::rand() % 5;
        switch (tempColor) {
            case 0: this->_colorOfWires.push_back(RED); break;
            case 1: this->_colorOfWires.push_back(BLUE); break;
            case 2: this->_colorOfWires.push_back(YELLOW); break;
            case 3: this->_colorOfWires.push_back(BLACK); break;
            case 4: this->_colorOfWires.push_back(WHITE); break;
        }
    }
    this->countColor();
}

std::vector<Color> KTANE::Wire::getColor()
{
    return this->_colorOfWires;
}

bool KTANE::Wire::modError()
{
    if (this->_err == true) {
        this->_err = false;
        return true;
    }
    return false;
}

int KTANE::Wire::getLastIndexOfColor(Color target)
{
    for (int i = this->_nbrOfWires - 1; i >= 0; --i) {
        if (this->_colorOfWires[i] == target)
            return i;
    }
    return -1;
}

void KTANE::Wire::countColor()
{
    for (auto color : this->_colorOfWires) {
        if (color.r == RED.r && color.g == RED.g && color.b == RED.b && color.a == RED.a)
            this->_countRed++;
        else if (color.r == BLUE.r && color.g == BLUE.g && color.b == BLUE.b && color.a == BLUE.a)
            this->_countBlue++;
        else if (color.r == YELLOW.r && color.g == YELLOW.g && color.b == YELLOW.b && color.a == YELLOW.a)
            this->_countYellow++;
        else if (color.r == WHITE.r && color.g == WHITE.g && color.b == WHITE.b && color.a == WHITE.a)
            this->_countWhite++;
        else if (color.r == BLACK.r && color.g == BLACK.g && color.b == BLACK.b && color.a == BLACK.a)
            this->_countBlack++;
    }
}

int KTANE::Wire::check_result()
{
    size_t n = this->_nbrOfWires;
    if (n == 3) {
        if (this->_countRed == 0) return 2;
        if (this->_colorOfWires.back() == WHITE) return n;
        if (this->_countBlue > 1) return getLastIndexOfColor(BLUE);
        return 3;
    }
    else if (n == 4) {
        if (this->_countRed > 1 && this->_serialLastDigit % 2 == 1)
            return getLastIndexOfColor(RED);
        if (this->_colorOfWires.back() == YELLOW && this->_countRed == 0)
            return 1;
        if (this->_countBlue == 1)
            return 1;
        if (this->_countYellow > 1)
            return 4;
        return 2;
    }
    else if (n == 5) {
        if (this->_colorOfWires.back() == BLACK && this->_serialLastDigit % 2 == 1)
            return 4;
        if (this->_countRed == 1 && this->_countYellow > 1)
            return 1;
        if (this->_countBlack == 0)
            return 2;
        return 1;
    }
    else if (n == 6) {
        if (this->_countYellow == 0 && this->_serialLastDigit % 2 == 1)
            return 3;
        if (this->_countYellow == 1 && this->_countWhite > 1)
            return 4;
        if (this->_countRed == 0)
            return 6;
        return 4;
    }
    return -1;
}

void KTANE::Wire::update(Rectangle wire, int i)
{
    Vector2 mouse = GetMousePosition();
    bool inside   = CheckCollisionPointRec(mouse, wire);
    if (inside)
        this->_colorOfWires[i] = Fade(this->_colorOfWires[i], 0.3f);
    else
        this->_colorOfWires[i] = Fade(this->_colorOfWires[i], 1.0f);
    if (inside && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->_colorOfWires[i] == LIGHTGRAY)
        return;
    if (inside && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->check_result() - 1 != i) {
        this->_colorOfWires[i] = LIGHTGRAY;
        this->_err = true;
    }
    if (inside && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && this->check_result() - 1 == i) {
        this->_win = true;
        this->_colorOfWires[i] = LIGHTGRAY;
    }
    return;

}

Color KTANE::Wire::win()
{
    if (this->_win == true)
        return GREEN;
    return RED;
}

void KTANE::Wire::display(KTANE::Gui *gui, Rectangle rect)
{
    Rectangle wire{rect.x + 10, rect.y + 10, 120, 15};
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, LIGHTGRAY);
    DrawRectangle(rect.x + rect.width - 30, rect.y + 10, 20, 20, win());
    for (int i = 0; i < this->getWire(); i++) {
        if (this->_win == false)
            update(wire, i);
        DrawRectangle(wire.x, wire.y, wire.width, wire.height, this->_colorOfWires[i]);
        wire.y += 25;
    }
}

int KTANE::Wire::getBattery(int batteries)
{
    return 0;
}
int KTANE::Wire::getTime(int time)
{
    return 0;
}