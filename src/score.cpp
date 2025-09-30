/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** score
*/

#include "../include/score.hpp"
#include <iostream>
#include <fstream>
#include <string>

Score::Score() {}

Score::~Score() {}

void Score::addScore(const std::string &name, int module, int time, int error)
{
    this->_name = name;
    this->_module = module;
    this->_time = time;
    this->_error = error;
    this->_isSaved = true;
    this->writeintoFile();
}

std::string Score::getName() const
{
    return this->_name;
}

int Score::getTime() const
{
    return this->_time;
}

int Score::getModule() const
{
    return this->_module;
}

int Score::getError() const
{
    return this->_error;
}

void Score::writeintoFile()
{
    int min = _time / 60;
    int sec = _time % 60;

    std::ofstream file("Score.txt", std::ios::app);
    if (!file) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    file << _name << "; " << "nbr of modules : "<< _module << "; " << "nbr error : "<< this->_error << "; " << min << "m " << sec << "s" << std::endl;

    file.close();
}