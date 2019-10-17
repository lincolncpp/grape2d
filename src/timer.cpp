#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <algorithm>

#include "../include/grape2d.h"

using namespace G2D;

Timer::Timer(int limit, void (*callback)()) {
    _limit = limit;
    _callback = callback;

    if (_limit > 0){
        Engine::instance->_timers.push_back(this);
    }
}

Timer::~Timer() {
    if (_limit > 0){
        Engine::instance->_timers.erase(find(Engine::instance->_timers.begin(), Engine::instance->_timers.end(), this));
    }
}

void Timer::update(int engine_tick) {
    if (!_paused && _started){
        if (engine_tick >= _tick_start + _limit){
            _tick_start += _limit;

            if (_callback != nullptr){
                _callback();
            }
        }
    }
}

void Timer::start() {
    if (!_started) {
        _paused = false;
        _started = true;
        _tick_start = SDL_GetTicks();
    }
}

void Timer::pause() {
    if (!_paused && _started) {
        _tick_pause = SDL_GetTicks();
        _paused = true;
    }
}

void Timer::resume() {
    if (_paused && _started) {
        _tick_start += SDL_GetTicks() - _tick_pause;
        _paused = false;
    }
}

void Timer::stop() {
    if (_started){
        _started = false;
    }
}

void Timer::restart() {
    _started = true;
    _paused = false;
    _tick_start = SDL_GetTicks();
}

void Timer::toggle() {
    if (_paused){
        resume();
    }
    else{
        pause();
    }
}

int Timer::getTime() {
    if (!_started){
        return 0;
    }
    if (_paused){
        return SDL_GetTicks()-_tick_start-(SDL_GetTicks()-_tick_pause);
    }

    return SDL_GetTicks()-_tick_start;
}

bool Timer::isPaused() {
    return _paused;
}

bool Timer::isStarted() {
    return _started;
}