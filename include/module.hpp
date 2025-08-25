/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** main
*/

#pragma once

#include "gui.hpp"
#include <string>

namespace KTANE {

    // Interface for modules in the KTANE game
    // Each module must implement the IModule interface
    class IModule {
    public:
        virtual ~IModule() = default;

        // Initialize the module with a serial number and battery count
        virtual int initialize(std::string serial, int battery) = 0;

        // Start the module, typically called when the defuser starts
        virtual void start() = 0;

        // Stop the module, typically called when the defuser stops
        virtual int stop() = 0;

        // For displaying the module in the GUI
        virtual void display(Gui *gui, Rectangle rect) = 0;

        // Get the serial number of the module
        virtual int getSerial(std::string serial) = 0;

        // Get the battery count for the module
        virtual int getBattery(int batteries) = 0;

        // Get the time left for the module
        virtual int getTime(int time) = 0;

        // Check if the module has been solved 
        virtual Color win() = 0;

        // Check if the module has an error
        virtual bool modError() = 0;
    };


}
