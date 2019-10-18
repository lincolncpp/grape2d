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
    for (auto p : _elements){
        Sprite *sprite = p.second;

        sprite->render();
    }
}

void Layer::update(int tick) {
    std::vector<std::pair<int, Sprite*>>refresh;

    for(auto it : _elements){
        int z = it.first;
        Sprite *sprite = it.second;

        sprite->update(tick);

        if (sprite->_z != z) refresh.push_back(it);
    }

    if ((int)refresh.size() > 0){
        for(auto r:refresh){
            _elements.erase(r);
            _elements.insert({r.second->_z, r.second});
        }
    }
}

void Layer::setZ(int value) {
    _z = value;
    Engine::instance->updateLayerZIndex();
}

int Layer::getZ() {
    return _z;
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
    _elements.insert({sprite->_z, sprite});
}