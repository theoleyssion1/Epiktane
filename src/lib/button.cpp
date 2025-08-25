/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** button
*/
#include "../../include/gui.hpp"

void Button::InitButton(Rectangle b, const std::string& txt)
{
    this->bounds     = b;
    this->label      = txt;
    this->baseColor  = GRAY;
    this->hoverColor = LIGHTGRAY;
    this->pressColor = DARKGRAY;
}

void Button::InitButton(Rectangle b, const std::string& txt, Color color)
{
    this->bounds     = b;
    this->label      = txt;
    this->baseColor  = color;
    this->hoverColor = LIGHTGRAY;
    this->pressColor = DARKGRAY;
}

bool Button::UpdateButton()
{
    Vector2 mouse = GetMousePosition();
    bool inside   = CheckCollisionPointRec(mouse, bounds);

    if (inside && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        this->_isPressed = true;
        return true;
    }
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        this->_isPressed = false;
    }
    return false;
}

void Button::DrawButton() const
{
    Vector2 mouse = GetMousePosition();
    bool inside   = CheckCollisionPointRec(mouse, bounds);
    const int fontSize = 20;
    Color color = baseColor;

    if (inside) {
        color = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? this->pressColor : this->hoverColor;
    }

    DrawRectangleRec(this->bounds, color);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), label.c_str(), fontSize, 1);
    DrawText(this->label.c_str(), this->bounds.x + (this->bounds.width  - textSize.x) / 2, this->bounds.y + (this->bounds.height - textSize.y) / 2, fontSize, BLACK);
}

bool Button::isPressed() const
{
    return this->_isPressed;
}

Rectangle Button::getBounds() const
{
    return this->bounds;
}

void Button::setPosition(float x, float y)
{
    this->bounds.x = x;
    this->bounds.y = y;
}
