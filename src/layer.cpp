#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <algorithm>

#include "../include/grape2d.h"

using namespace G2D;

Layer::Layer() {

}

Layer::~Layer() {

}

void Layer::render() {
    for (auto sprite : _elements){
        sprite->render();
    }
}

void Layer::update(int tick) {
    for (auto sprite: _elements){
        sprite->update(tick);
    }
}

void Layer::setZIndex(int value) {
    _zindex = value;
    Engine::instance->updateLayerZIndex();
}

int Layer::getZIndex() {
    return _zindex;
}

void Layer::hide() {
    _visible = false;
}

void Layer::show() {
    _visible = true;
}

void Layer::Callback::onEvent(void (*function)(Event)) {
    onEventFunction = function;
}

void Layer::Callback::onUpdate(void (*function)()) {
    onUpdateFunction = function;
}


void Layer::Callback::onRender(void (*function)()) {
    onRenderFunction = function;
}

void Layer::attach(Sprite *sprite) {
    if (sprite->_layer_owner == nullptr) {
        if (_elements.empty() || find(_elements.begin(), _elements.end(), sprite) == _elements.end()) {
            sprite->_layer_owner = this;
            _elements.push_back(sprite);
            updateSpriteZIndex();
        }
    }
}

void Layer::updateSpriteZIndex() {
    auto compare = [](const Sprite *a, const Sprite *b) -> bool{
        return a->_zindex < b->_zindex;
    };
    sort(_elements.begin(), _elements.end(), compare);
}