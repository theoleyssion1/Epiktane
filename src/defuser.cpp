/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** defuser
*/

#include "../include/defuser.hpp"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <dlfcn.h>
#include "../include/wire.hpp"
#include "../include/buttonModule.hpp"
#include "../include/simon.hpp"
#include "../include/memory.hpp"
#include "../include/morse.hpp"

#define mod_x 100
#define mod_y 100
#define scale 150

namespace KTANE {

    // Constructor initializes the defuser with default values
    Defuser::Defuser(int time, int module, int error)
        : _isActive(false), _errorCount(0), _maxError(error), _nbrModule(module), _time(time), _nbrWin(0), _chatbox(), _score()
    {
        std::srand(std::time(nullptr));

    }

    Defuser::~Defuser()
    {

    }

    // Start the defuser, setting it to active and resetting error count
    void Defuser::start() {
        this->initBomb();
        for (auto& module : this->_module) {
            if (module) {
                module->initialize(this->_serial, this->battery);
            }
        }
        this->_timer.startTimer(this->_time);
    }
    
    // init the bomb with a random serial number and battery count
    void Defuser::initBomb()
    {
        this->_isActive = true;
        this->_errorCount = 0;
        this->_nbrWin = 0;
        this->_status = PROCESS;

        bool hasDigit = false, hasLetter = false;

        while (true) {
            this->_serial.clear();
            hasDigit = false;
            hasLetter = false;

            for (int i = 0; i < 6; ++i) {
                int type = std::rand() % 3;
                char c;
                if (type == 0)
                    c = '0' + std::rand() % 10;
                else if (type == 1)
                    c = 'A' + std::rand() % 26;
                else
                    c = 'a' + std::rand() % 26;
                if (std::isdigit(c))
                    hasDigit = true;
                if (std::isalpha(c))
                    hasLetter = true;
                this->_serial += c;
            }
            if (hasDigit && hasLetter)
                break;
        }
        this->battery = std::rand() % 5;

        this->addModule();
    }

    // Stop the defuser, returning 1 to indicate success and close the process
    int Defuser::stop() {
        return 1;
    }

    // Reset the defuser, setting it to inactive and resetting all attributes
    void Defuser::reset() {
        this->_isActive = false;
        this->_errorCount = 0;
        this->_nbrWin = 0;
        this->_status = STATE::INITIALISED;
    }

    // Add modules to the defuser, randomly choosing between Wire and ButtonModule
    void Defuser::addModule()
    {
    this->_module.clear();

    // Table des modules disponibles
    std::vector<ModuleEntry> moduleTable = {
        {[]() { return new Wire(); }, (_nbrModule + 1) / 2},
        {[]() { return new ButtonModule(); }, (_nbrModule + 1) / 2},
        {[]() { return new Simon(); }, 2},
        {[]() { return new Memory(); }, 2},
        {[]() { return new Morse(); }, 1},
    };

    for (int i = 0; i < this->_nbrModule; ++i) {
        std::vector<int> availableIndices;

        // Filtrer ceux qui peuvent encore être utilisés
        for (int j = 0; j < moduleTable.size(); ++j) {
            if (moduleTable[j].currentCount < moduleTable[j].maxOccurrences) {
                availableIndices.push_back(j);
            }
        }

        if (availableIndices.empty()) {
            break;
        }

        int idx = availableIndices[std::rand() % availableIndices.size()];
        moduleTable[idx].currentCount++;

        this->_module.emplace_back(moduleTable[idx].createFunc());
    }
}


    // Get a module from the defuser, if it exists
    void Defuser::getModule(IModule* module)
    {
        if (module) {
            this->_module.emplace_back(module);
        } else {
            std::cerr << "Failed to create module from module" << std::endl;
        }
    }

    // Display the defuser, checking the state and displaying the modules
    void Defuser::display(Gui *gui)
    {

        if (gui->getState() == KTANE::GUI_STATE::START) {
            DrawText(TextFormat("%i", this->_maxError), 320, 300, 40, BLACK);
            DrawText(TextFormat("%i", this->_nbrModule), 630, 300, 40, BLACK);
            DrawText(formatTime(this->_time).c_str(), 900, 300, 40, BLACK);
            if (gui->getButton("Perr")->UpdateButton() == true) {
                this->setMaxError(this->getMaxError() + 1);
            }
            if (gui->getButton("Merr")->UpdateButton() == true) {
                if (this->getMaxError() > 0)
                    this->setMaxError(this->getMaxError() - 1);
            }
            if (gui->getButton("Pmod")->UpdateButton() == true) {
                this->setNbrModule(this->getNbrModule() + 1);
            }
            if (gui->getButton("Mmod")->UpdateButton() == true) {
                this->setNbrModule(this->getNbrModule() - 1);
            }
            if (gui->getButton("Ptime")->UpdateButton() == true) {
                this->setTimer(this->getTimer() + 10);
            }
            if (gui->getButton("Mtime")->UpdateButton() == true) {
                this->setTimer(this->getTimer() - 10);
            }
            return;
        }
        
        if (gui->getState() == KTANE::GUI_STATE::PLAY) {
            float x = mod_x, y = mod_y;
            int i = 0;
            DrawRectangle(mod_x, mod_y, scale, scale, LIGHTGRAY);
            DrawText(TextFormat("Error : %i/%i", this->getErrorCount(), this->getMaxError()), mod_x + 5, mod_y + 5, 20, BLACK);
            DrawText(this->formatTime(this->_timer.getRemainingTime()).c_str(), mod_x + 30, mod_y + 50, 30, BLACK);
            DrawText(TextFormat("Serial : %s", this->_serial.c_str()), 0, 20, 20, BLACK);
            DrawText(TextFormat("Battery : %i", this->battery), 0, 40, 20, BLACK);
            for (const auto& module : this->_module) {
                x += 160;
                if (i == 5) {
                    x = mod_x;
                    y += 160;
                }
                if (module) {
                    module->display(gui, Rectangle{x, y, scale, scale});
                }
                i++;
            }
            checkError();
            return;
        }
        if (gui->getState() == KTANE::GUI_STATE::WIN) {
            DrawText("You win!", 500, 200, 40, GREEN);
            DrawText(TextFormat("Modules solved: %i \n Time remaining: %s", this->_nbrModule,
                this->formatTime(this->_timer.getRemainingTime()).c_str()), 500, 240, 20, BLACK);
                this->_chatbox.drawChatBox();
                if (this->_chatbox.SaveChatBox() == true) {
                    DrawText("Pseudo Saved", 560, 460, 20, GREEN);
                    this->_score.addScore(this->_chatbox.getSavedName(), this->_nbrModule, this->_timer.getRemainingTime(), this->_errorCount);
                }
            return;
        }
    }

    // Change the nbr of error if module send an error
    void Defuser::checkError()
    {
        for (const auto& module : this->_module) {
            if (module && module->modError() == true) {
                this->addErrorCount();
            }
        }
        if (this->_errorCount == this->_maxError)
            this->_status = EXPLOSED;
    }

    // Get the current error count
    int Defuser::getErrorCount() const {
        return this->_errorCount;
    }
    
    // Set the error count
    void Defuser::setErrorCount(int count) {
        this->_errorCount = count;
    }

    // Add to the error count
    void Defuser::addErrorCount() {
        this->_errorCount++;
    }

    // Set the maximum number of errors allowed
    void Defuser::setMaxError(int count) {
        this->_maxError = count;
    }

    // Get the maximum number of errors allowed
    int Defuser::getMaxError() const {
        return this->_maxError;
    }

    // Set the number of modules in the defuser
    int Defuser::setNbrModule(int count) {
        if (count < 2 || count > 10) {
            return -1;
        }
        this->_nbrModule = count;
        return 0;
    }

    // Get the number of modules in the defuser
    int Defuser::getNbrModule() const {
        return this->_nbrModule;
    }

    // Set the timer for the defuser
    int Defuser::setTimer(float time)
    {
        this->_time = time;
        return 0;
    }

    // Get the current timer value
    float Defuser::getTimer()
    {
        return this->_time;
    }

    // Check the bomb's state
    int Defuser::isBombDefused()
    {
        if (this->_status == STATE::PROCESS)
            return 1;
        else if (this->_status == STATE::DEFUSED)
            return 2;
        else if (this->_status == STATE::EXPLOSED)
            return 3;
        return -1;
    }

    //formating time remaining in string 
    std::string Defuser::formatTime(float time) {
        int totalSeconds = static_cast<int>(time);
        int minutes = totalSeconds / 60;
        int secs = totalSeconds % 60;
    
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << minutes
            << ":" << std::setfill('0') << std::setw(2) << secs;
    
        return oss.str();
    }

    // Get the names of the modules in the defuser
    std::vector<std::string> Defuser::getNameOfModules()
    {
        return this->_listOfModule;
    }

    // Check if the defuser is currently active
    bool Defuser::isActive()
    {
        return this->_isActive;
    }

    // Check the number of modules that have been successfully defused
    int Defuser::nbrOfModuleWin()
    {
        int temp = 0;
        for (int i = 0; i != this->_nbrModule; i++) {
            if (this->_module[i] && this->_module[i]->win() == GREEN)
            temp++;
        }
        if (temp > this->_nbrWin)
            this->_nbrWin = temp;
        if (this->_nbrWin == this->_nbrModule)
            this->_status = STATE::DEFUSED;
    
        return this->_nbrWin;
    }

    // Get the current state of the defuser
    STATE Defuser::getState()
    {
        return this->_status;
    }


    //poll event
    void Defuser::pollEvent()
    {
        nbrOfModuleWin();
        if (this->_timer.IsTimerFinished() == true) {
            this->_isActive = false;
            this->_status = STATE::EXPLOSED;        
        }
        int i = isBombDefused();

        if (i != 1) {
            if (i == 2) {
                this->_isActive = false;
                this->_timer.stopTimer();
                this->_chatbox.initChatBox();
                return;
            }
            if (i == 3) {
                this->_isActive = false;
                return;
            }
        }
    }

}
