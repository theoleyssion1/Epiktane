/*
** EPITECH PROJECT, 2025
** epiktane [WSL : Ubuntu]
** File description:
** score
*/

#pragma once

#include <string>

class Score {
    public:
        Score();
        ~Score();
        void addScore(const std::string &name, int module, int time, int error);
        void setScore(int score);
        int getScore() const;
        std::string getName() const;
        int getTime() const;
        int getModule() const;
        int getError() const;
        void writeintoFile();
    private:
        int _score{0};
        std::string _name;
        int _time{0};
        int _module{0};
        int _error{0};
};