/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** chatbox
*/

#include <raylib.h>
#include <string>

#pragma once

class ChatBox {
    public:
        ChatBox();
        void initChatBox();
        void drawChatBox();
        void handleInput();
        void updateChatBox();
        bool SaveChatBox();
        std::string getSavedName() const;
    private:
        char _name[16]; // 16 characters + null terminator
        int _letterCount;
        Rectangle _textBox;
        bool _mouseOnText;
        int _framesCounter;
        std::string _savedName;
};