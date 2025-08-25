/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** defuser
*/

#pragma once

#include "module.hpp"
#include "score.hpp"
#include "timer.hpp"
#include "chatbox.hpp"
#include <memory>
#include <string>
#include <vector>
#include <functional>

struct ModuleEntry {
    std::function<KTANE::IModule*()> createFunc;
    int maxOccurrences;
    int currentCount = 0;
};

namespace KTANE {

    enum STATE {
        INITIALISED = 0,
        PROCESS = 1,
        DEFUSED = 2,
        EXPLOSED = 3
    };

    // Defuser class that implements the IModule interface
    // This class manages the defuser's state, including starting, stopping, resetting,
    // and handling errors. It also manages the number of modules and the maximum number of errors
    // allowed before the defuser is considered failed.
    class Defuser {
    public:
        Defuser(int time, int module, int error);
        ~Defuser();

        void start();
        void startgui();
        int stop();
        void reset();
        
        void getModule(IModule *module);
        void addModule();
        
        int run();
        void pollEvent();
        void display(Gui *gui);

        bool isActive();

        void checkError();
        int getErrorCount() const;
        void setErrorCount(int count);
        void addErrorCount();

        void setMaxError(int count);
        int getMaxError() const;

        int setNbrModule(int count);
        int getNbrModule() const;

        int setTimer(float time);
        float getTimer();

        std::vector<std::string> getNameOfModules();
        std::string formatTime(float time);
        int isBombDefused();
        int nbrOfModuleWin();
        STATE getState();
        void initBomb();


    private:
        bool _isActive;

        Timer _timer;
        float _time;

        int _errorCount;
        int _maxError;

        int _nbrModule;
        int _nbrWin;

        STATE _status;
        std::vector<std::unique_ptr<KTANE::IModule>> _module;
        std::vector<std::string> _listOfModule;

        std::string _serial;
        int battery;
        ChatBox _chatbox;
        Score _score;
    };

}

inline bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}