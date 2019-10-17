#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

using namespace G2D;

Engine::Camera::Camera() {
    _position.x = Engine::instance->getWindowWidth()/2;
    _position.y = Engine::instance->getWindowHeight()/2;
}

void Engine::Camera::setCenterPosition(int x, int y) {
    _position.x = x;
    _position.y = y;
}

void Engine::Camera::setCenterPosition(Point point) {
    _position = point;
}

void Engine::Camera::setCenterX(int x) {
    _position.x = x;
}

void Engine::Camera::setCenterY(int y) {
    _position.y = y;
}

int Engine::Camera::getCenterX() {
    return _position.x;
}

int Engine::Camera::getCenterY() {
    return _position.y;
}

int Engine::Camera::getCornerX() {
    return _position.x-Engine::instance->getWindowWidth()/2;
}

int Engine::Camera::getCornerY() {
    return _position.y-Engine::instance->getWindowHeight()/2;
}
