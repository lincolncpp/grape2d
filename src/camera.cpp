#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Engine::G2D_Camera::G2D_Camera() {
    _x = G2D_Engine::instance->getWindowWidth()/2;
    _y = G2D_Engine::instance->getWindowHeight()/2;
}

void G2D_Engine::G2D_Camera::setPosition(int x, int y) {
    _x = x;
    _y = y;
}

void G2D_Engine::G2D_Camera::setX(int x) {
    _x = x;
}

void G2D_Engine::G2D_Camera::setY(int y) {
    _y = y;
}

int G2D_Engine::G2D_Camera::getX() {
    return _x;
}

int G2D_Engine::G2D_Camera::getY() {
    return _y;
}

int G2D_Engine::G2D_Camera::getDrawXAdd() {
    return _x-G2D_Engine::instance->getWindowWidth()/2;
}

int G2D_Engine::G2D_Camera::getDrawYAdd() {
    return _y-G2D_Engine::instance->getWindowHeight()/2;
}