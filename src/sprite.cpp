#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Sprite::G2D_Sprite(const char *path, int sprite_width, int sprite_height) {
    _texture = new G2D_Texture(path);
    _sprite_width = sprite_width;
    _sprite_height = sprite_height;
}

G2D_Sprite::G2D_Sprite(G2D_Texture *texture, int sprite_width, int sprite_height) {
    _texture = texture;
    _sprite_width = sprite_width;
    _sprite_height = sprite_height;
}

G2D_Sprite::~G2D_Sprite() {
    if (_texture != nullptr){
        _texture->free();
    }
}

G2D_Texture *G2D_Sprite::getTexture() {
    return _texture;
}

void G2D_Sprite::setPosition(int x, int y) {
    _position.x = x;
    _position.y = y;
}

void G2D_Sprite::setPosition(G2D_Point point) {
    _position = point;
}

void G2D_Sprite::setX(int x) {
    _position.x = x;
}

int G2D_Sprite::getX() {
    return _position.x;
}

void G2D_Sprite::setY(int y) {
    _position.y = y;
}

int G2D_Sprite::getY() {
    return _position.y;
}

void G2D_Sprite::render() {
    _texture->render(_position.x, _position.y);
}

void G2D_Sprite::setZIndex(int value) {
    _zindex = value;
    if (_container_owner != nullptr){
        _container_owner->updateSpriteZIndex();
    }
}

int G2D_Sprite::getZIndex() {
    return _zindex;
}