/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** gui
*/

#include "../../include/gui.hpp"
#include <raylib.h>
#define NUM_FRAMES  3
#define screenWidth 1200
#define screenHeight 800


namespace KTANE {

Gui::Gui() : _state(GUI_STATE::MENU)
{
    this->initWindow();
    this->initCamera();
    this->initMenu();
}

Gui::~Gui()
{
    CloseWindow();
}

void Gui::initWindow()
{
    InitWindow(screenWidth, screenHeight, "EPI-KTANE");
    SetTargetFPS(60);
}

void Gui::initCamera()
{

}

void Gui::initMenu()
{
    if (!this->_buttons.empty()) {
        this->_buttons.clear();
    }
    Button button;
    button.InitButton(Rectangle{500, 400, 200, 100}, "Play");

    this->_buttons.emplace("Start", std::move(button));
}

void Gui::initStart()
{
    if (!this->_buttons.empty()) {
        this->_buttons.clear();
    }
    Button button;
    button.InitButton(Rectangle{300, 200, 200, 50}, "+");
    this->_buttons.emplace("Perr", std::move(button));
    button.InitButton(Rectangle{300, 400, 200, 50}, "-");
    this->_buttons.emplace("Merr", std::move(button));
    button.InitButton(Rectangle{600, 200, 200, 50}, "+");
    this->_buttons.emplace("Pmod", std::move(button));
    button.InitButton(Rectangle{600, 400, 200, 50}, "-");
    this->_buttons.emplace("Mmod", std::move(button));
    button.InitButton(Rectangle{900, 200, 200, 50}, "+");
    this->_buttons.emplace("Ptime", std::move(button));
    button.InitButton(Rectangle{900, 400, 200, 50}, "-");
    this->_buttons.emplace("Mtime", std::move(button));
    button.InitButton(Rectangle{(float(screenWidth) / 2), 600, 200, 100}, "START");
    this->_buttons.emplace("Play", std::move(button));
}

void Gui::initPlay()
{
    if (!this->_buttons.empty()) {
        this->_buttons.clear();
    }
    Button button;
    button.InitButton(Rectangle{1100, 20, 50, 50}, "Back");
    
    this->_buttons.emplace("BackToMenu", std::move(button));
}

void Gui::initWin()
{
    if (!this->_buttons.empty()) {
        this->_buttons.clear();
    }
    Button button;
    button.InitButton(Rectangle{500, 500, 200, 100}, "Back To Menu");
    
    this->_buttons.emplace("BackToMenu", std::move(button));
}

void Gui::initLoose()
{
    if (!this->_buttons.empty()) {
        this->_buttons.clear();
    }
    Button button;
    button.InitButton(Rectangle{500, 300, 200, 100}, "Back To Menu");
    
    this->_buttons.emplace("BackToMenu", std::move(button));
}

void Gui::changeScreen(enum GUI_STATE screen)
{
    if (screen == GUI_STATE::MENU) {
        this->initMenu();
        this->_state = GUI_STATE::MENU;
        return;
    }
    if (screen == GUI_STATE::START) {
        this->initStart();
        this->_state = GUI_STATE::START;
        return;
    }
    if (screen == GUI_STATE::PLAY) {
        this->initPlay();
        this->_state = GUI_STATE::PLAY;
        return;
    }
    if (screen == GUI_STATE::WIN) {
        this->initWin();
        this->_state = GUI_STATE::WIN;
        return;
    }
    if (screen == GUI_STATE::LOOSE) {
        this->initLoose();
        this->_state = GUI_STATE::LOOSE;
        return;
    }
}

Button* Gui::getButton(const std::string& name)
{
    auto it = this->_buttons.find(name);
    if (it != _buttons.end())
        return &(it->second);
    return nullptr;
}

    void Gui::run() {
    
        while (!WindowShouldClose()) {

            this->draw();
            this->pollEvent();
        }
    }

    void Gui::pollEvent()
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (auto& button : this->_buttons) {
                if (button.second.UpdateButton()) {
                    if (button.first == "Play") {
                        this->changeScreen(GUI_STATE::PLAY);
                        return;
                    } else if (button.first == "Start") {
                        this->changeScreen(GUI_STATE::START);
                        return;
                    } else if (button.first == "BackToMenu") {
                        this->changeScreen(GUI_STATE::MENU);
                        return;
                    }
                }
            }
        }
    }

    void Gui::drawButton(const std::string& name)
    {
        auto it = this->_buttons.find(name);
        if (it != _buttons.end()) {
            it->second.DrawButton();
        }
    }

    void Gui::draw()
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (this->_state == GUI_STATE::MENU) {
            this->drawMenu();
        } else if (this->_state == GUI_STATE::START) {
            this->drawStart();
        } else if (this->_state == GUI_STATE::PLAY) {
            this->drawPlay();
        } else if (this->_state == GUI_STATE::WIN) {
            this->drawWin();
        } else if (this->_state == GUI_STATE::LOOSE) {
            this->drawLoose();
        }

        EndDrawing();
    }

    void Gui::drawMenu()
    {
        DrawText("Epi-KTANE", 475, 50, 50, BLACK);
        this->drawButton("Start");
    }

    void Gui::drawPlay()
    {
        this->drawButton("BackToMenu");
    }

    void Gui::drawWin()
    {
        this->drawButton("BackToMenu");
    }

    void Gui::drawLoose()
    {
        DrawText("You Loose!", 500, 200, 40, BLACK);
        this->drawButton("BackToMenu");
    }

    void Gui::drawStart()
    {
        DrawText("Nbr Error", 300, 150, 40, BLACK);
        this->drawButton("Perr");
        this->drawButton("Merr");
        
        DrawText("Nbr Module", 600, 150, 40, BLACK);
        this->drawButton("Pmod");
        this->drawButton("Mmod");
        
        DrawText("Time", 950, 150, 40, BLACK);
        this->drawButton("Ptime");
        this->drawButton("Mtime");

        this->drawButton("Play");
    }
}
