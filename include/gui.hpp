/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** gui
*/

#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>


class Button
{
private:
    Rectangle bounds{};
    std::string label;
    Color baseColor{GRAY};
    Color hoverColor{LIGHTGRAY};
    Color pressColor{DARKGRAY};
    bool _isPressed{false};

public:
    Button() = default;

    void InitButton(Rectangle b, const std::string& txt);
    void InitButton(Rectangle b, const std::string& txt, Color color);
    bool UpdateButton();
    void DrawButton() const;
    bool isPressed() const;
    Rectangle getBounds() const;
    void setPosition(float x, float y);
};

namespace KTANE
{
    enum class GUI_STATE {
        MENU,
        START,
        PLAY,
        WIN,
        LOOSE,
        EXIT
    };

    class Gui {
        
        public:
            Gui();
            ~Gui();

            void initWindow();
            void initCamera();
            void initMenu();
            void initStart();
            void initPlay();
            void initWin();
            void initLoose();

            void run();
            void draw();
            void drawMenu();
            void drawStart();
            void drawPlay();
            void drawWin();
            void drawLoose();
            void pollEvent();
            void changeScreen(enum GUI_STATE screen);
            void drawButton(const std::string& name);
            Button* getButton(const std::string& name);
            GUI_STATE getState() const { return _state; };

        private:

        Camera _cam;
        Vector2 _mouse_pos;
        std::unordered_map<std::string, Button> _buttons;
        GUI_STATE _state;


    };

}
