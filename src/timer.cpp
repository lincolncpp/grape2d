#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <algorithm>

#include "../include/grape2d.h"

G2D_Timer::G2D_Timer(int limit, void (*callback)()) {
    _limit = limit;
    _callback = callback;

    if (_limit > 0){
        G2D_Engine::instance->_timers.push_back(this);
    }
}

G2D_Timer::~G2D_Timer() {
    if (_limit > 0){
        G2D_Engine::instance->_timers.erase(find(G2D_Engine::instance->_timers.begin(), G2D_Engine::instance->_timers.end(), this));
    }
}

void G2D_Timer::update(int engine_tick) {
    if (!_paused && _started){
        if (engine_tick >= _tick_start + _limit){
            _tick_start += _limit;

            if (_callback != nullptr){
                _callback();
            }
        }
    }
}

void G2D_Timer::start() {
    if (!_started) {
        _paused = false;
        _started = true;
        _tick_start = SDL_GetTicks();
    }
}

void G2D_Timer::pause() {
    if (!_paused && _started) {
        _tick_pause = SDL_GetTicks();
        _paused = true;
    }
}

void G2D_Timer::resume() {
    if (_paused && _started) {
        _tick_start += SDL_GetTicks() - _tick_pause;
        _paused = false;
    }
}

void G2D_Timer::stop() {
    if (_started){
        _started = false;
    }
}

void G2D_Timer::restart() {
    _started = true;
    _paused = false;
    _tick_start = SDL_GetTicks();
}

void G2D_Timer::toggle() {
    if (_paused){
        resume();
    }
    else{
        pause();
    }
}

int G2D_Timer::getTime() {
    if (!_started){
        return 0;
    }
    if (_paused){
        return SDL_GetTicks()-_tick_start-(SDL_GetTicks()-_tick_pause);
    }

    return SDL_GetTicks()-_tick_start;
}

bool G2D_Timer::isPaused() {
    return _paused;
}

bool G2D_Timer::isStarted() {
    return _started;
}