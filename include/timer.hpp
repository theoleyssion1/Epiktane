/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** timer
*/

#pragma once

#include <chrono>

class Timer {
    public:
        void startTimer(float TimerDuration);
        bool IsTimerFinished();
        float getRemainingTime();
        void stopTimer();
    private:
        float _timerDuration;
        std::chrono::steady_clock::time_point _timerStart;
        bool _isStarting;
        float _remainingTime;
};