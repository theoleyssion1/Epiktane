/*
** EPITECH PROJECT, 2025
** Epi-KTANE
** File description:
** timer
*/

#include "../include/timer.hpp"

// Start the timer
void Timer::startTimer(float TimerDuration) {
    this->_timerDuration = TimerDuration;
    this->_timerStart = std::chrono::steady_clock::now();
    this->_isStarting = true;
}

// check if the timer is finished
bool Timer::IsTimerFinished() {
    if (!this->_isStarting)
        return true;

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - this->_timerStart;

    if (elapsed.count() >= this->_timerDuration) {
        this->_isStarting = false;
        return true;
    }
    return false;
}

// Get the remaining time in seconds
float Timer::getRemainingTime() {
    if (!this->_isStarting) return this->_remainingTime;

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = now - this->_timerStart;

    this->_remainingTime = this->_timerDuration - elapsed.count();
    return this->_remainingTime;
}

void Timer::stopTimer() {
    this->_isStarting = false;
}