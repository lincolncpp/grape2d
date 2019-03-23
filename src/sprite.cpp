#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <vector>

#include "../include/grape2d.h"


G2D_Sprite::G2D_Sprite(const char *path, int sprite_width, int sprite_height) {
    _texture = new G2D_Texture(path);

    construct(sprite_width, sprite_height);
}

G2D_Sprite::G2D_Sprite(G2D_Texture *texture, int sprite_width, int sprite_height) {
    _texture = texture;

    construct(sprite_width, sprite_height);
}

void G2D_Sprite::construct(int sprite_width, int sprite_height) {
    _texture->setReferential(G2D_REFERENTIAL_RELATIVE);

    _clip = {0, 0,
             sprite_width>0?sprite_width:_texture->getSrcWidth(),
             sprite_height>0?sprite_height:_texture->getSrcHeight()
    };
}

void G2D_Sprite::update(uint32_t tick) {
    if (_is_animating){
        int frame_index = (int)((float)(tick-_tick_animate)/(_time)*((int)_frames->size()));
        frame_index = frame_index > (int)_frames->size()-1?(int)_frames->size()-1:frame_index;

        setFrame(_frames->at((uint16_t)frame_index));

        if (tick > _tick_animate+_time) _is_animating = false;
    }
}

G2D_Sprite::~G2D_Sprite() {
    if (_texture != nullptr){
        _texture->free();
        delete _texture;
    }

    _container_owner = nullptr;

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

void G2D_Sprite::setReferential(G2D_Referential referential) {
    _texture->setReferential(referential);
}

void G2D_Sprite::render() {
    _texture->render(_position.x, _position.y, &_clip);
}

void G2D_Sprite::setFrame(int frame) {
    int max_frames_w = _texture->_src_width / _clip.w;
    int max_frames_h = _texture->_src_height / _clip.h;

    frame = frame % (max_frames_w*max_frames_h);

    int frame_x = frame % max_frames_w;
    int frame_y = frame / max_frames_w;

    _clip.x = frame_x * _clip.w;
    _clip.y = frame_y * _clip.h;

    _current_frame = (uint16_t)frame;
}

int G2D_Sprite::getFrame() {
    return _current_frame;
}

void G2D_Sprite::animate(std::vector<int> frames, uint32_t time, bool force){
    if (!_is_animating || (_is_animating && force)){
        _tick_animate = SDL_GetTicks();
        _is_animating = true;
        _time = time;

        _frames = new std::vector<int>;
        _frames->assign(frames.begin(), frames.end());
    }
}

void G2D_Sprite::setZIndex(int value) {
    _zindex = (int16_t)value;
    if (_container_owner != nullptr){
        _container_owner->updateSpriteZIndex();
    }
}

int G2D_Sprite::getZIndex() {
    return _zindex;
}
