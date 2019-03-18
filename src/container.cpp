#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include "../include/grape2d.h"

G2D_Container::G2D_Container() {

}

G2D_Container::~G2D_Container() {

}

void G2D_Container::render() {
}

void G2D_Container::update(int frame) {
}

void G2D_Container::setZIndex(int value) {
    _zindex = value;
    G2D_Engine::instance->updateContainerZIndex();
}

int G2D_Container::getZIndex() {
    return _zindex;
}

void G2D_Container::hide() {
    _visible = false;
}

void G2D_Container::show() {
    _visible = true;
}

void G2D_Container::G2D_Callback::setEventCallback(void (*function)(G2D_Event)) {
    onEvent = function;
}

void G2D_Container::G2D_Callback::setUpdateCallback(void (*function)(), int index) {
    if (index == 0){
        i0Updating = function;
    }
    else{
        i1Updating = function;
    }
}

void G2D_Container::G2D_Callback::setUpdateCallback(void (*function)(int), int index) {
    if (index == 0){
        i0UpdatingArg = function;
    }
    else{
        i1UpdatingArg = function;
    }
}

void G2D_Container::G2D_Callback::setRenderCallback(void (*function)(), int index) {
    if (index == 0){
        i0Rendering = function;
    }
    else{
        i1Rendering = function;
    }
}