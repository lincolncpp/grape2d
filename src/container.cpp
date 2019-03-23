#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <algorithm>

#include "../include/grape2d.h"

G2D_Container::G2D_Container() {

}

G2D_Container::~G2D_Container() {

}

void G2D_Container::render() {
    for (auto sprite : _elements){
        sprite->render();
    }
}

void G2D_Container::update(uint32_t tick) {
    for (auto sprite: _elements){
        sprite->update(tick);
    }
}

void G2D_Container::setZIndex(int16_t value) {
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

void G2D_Container::G2D_Callback::onEvent(void (*function)(G2D_Event)) {
    onEventFunction = function;
}

void G2D_Container::G2D_Callback::onUpdate(void (*function)()) {
    onUpdateFunction = function;
}


void G2D_Container::G2D_Callback::onRender(void (*function)()) {
    onRenderFunction = function;
}

void G2D_Container::attach(G2D_Sprite *sprite) {
    if (sprite->_container_owner == nullptr) {
        if (_elements.empty() || find(_elements.begin(), _elements.end(), sprite) == _elements.end()) {
            sprite->_container_owner = this;
            _elements.push_back(sprite);
            updateSpriteZIndex();
        }
    }
}

void G2D_Container::updateSpriteZIndex() {
    auto compare = [](const G2D_Sprite *a, const G2D_Sprite *b) -> bool{
        return a->_zindex < b->_zindex;
    };
    sort(_elements.begin(), _elements.end(), compare);
}