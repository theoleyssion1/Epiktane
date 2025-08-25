/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** chatbox
*/
#include "../include/chatbox.hpp"

#define MAX_INPUT_CHARS 15

ChatBox::ChatBox()
{
    this->initChatBox();
}

bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();
    if ((key >= 32) && (key <= 126)) keyPressed = true;
    return keyPressed;
}

void ChatBox::initChatBox()
{
    this->_letterCount = 0;
    this->_textBox = { 500, 400, 225, 50 };
    this->_mouseOnText = false;
    this->_framesCounter = 0;
    this->_name[0] = '\0';
}

void ChatBox::drawChatBox()
{
    if (CheckCollisionPointRec(GetMousePosition(), this->_textBox)) {
        this->_mouseOnText = true;
    } else {
        this->_mouseOnText = false;
    }

    if (this->_mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (this->_letterCount < 16)) {
                this->_name[this->_letterCount] = (char)key;
                this->_name[this->_letterCount + 1] = '\0';
                this->_letterCount++;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            this->_letterCount--;
            if (this->_letterCount < 0) this->_letterCount = 0;
            this->_name[this->_letterCount] = '\0';
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (this->_mouseOnText) {
        this->_framesCounter++;
    } else {
        this->_framesCounter = 0;
    }

    DrawText("Enter your pseudo", 500, 370, 20, GRAY);
    DrawRectangleRec(this->_textBox, LIGHTGRAY);
    if (this->_mouseOnText)
        DrawRectangleLines((int)this->_textBox.x, (int)this->_textBox.y, (int)this->_textBox.width, (int)this->_textBox.height, RED);
    else
        DrawRectangleLines((int)this->_textBox.x, (int)this->_textBox.y, (int)this->_textBox.width, (int)this->_textBox.height, DARKGRAY);
    
    DrawText(this->_name, (int)this->_textBox.x + 5, (int)this->_textBox.y + 15, 25, MAROON);
    
    if (this->_mouseOnText && this->_letterCount < 16) {
        if (((this->_framesCounter / 20) % 2) == 0)
            DrawText("_", (int)this->_textBox.x + 8 + MeasureText(this->_name, 25), (int)this->_textBox.y + 10, 40, MAROON);
    }
}

void ChatBox::handleInput()
{
    if (IsAnyKeyPressed()) {
        this->updateChatBox();
    }
}

void ChatBox::updateChatBox()
{
    if (CheckCollisionPointRec(GetMousePosition(), this->_textBox)) {
        this->_mouseOnText = true;
    } else {
        this->_mouseOnText = false;
    }

    if (this->_mouseOnText) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (this->_letterCount < 16)) {
                this->_name[this->_letterCount] = (char)key;
                this->_name[this->_letterCount + 1] = '\0';
                this->_letterCount++;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            this->_letterCount--;
            if (this->_letterCount < 0) this->_letterCount = 0;
            this->_name[this->_letterCount] = '\0';
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}

bool ChatBox::SaveChatBox()
{
    if (IsKeyPressed(KEY_ENTER)) {
        this->_savedName = std::string(this->_name);
        return true;
    }
    return false;
}

std::string ChatBox::getSavedName() const
{
    if (this->_savedName.empty()) {
        return std::string(this->_name);
    }
    return this->_savedName;
}