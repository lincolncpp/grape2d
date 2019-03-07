#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#ifdef _WIN32
    #include <math.h>
#endif

#include "../include/grape2d.h"

G2D_Sound::G2D_Sound(const char *path) {
    _sound = Mix_LoadWAV(path);

    if (_sound == nullptr){
        printf("Error on loading sound. %s\n", Mix_GetError());
        return;
    }
}

G2D_Sound::~G2D_Sound() {
    free();
}

void G2D_Sound::setChannel(int channel) {
    _channel = channel;
}

int G2D_Sound::getChannel() {
    return _channel;
}

int G2D_Sound::play(int repeat_times, int limit_ms) {
    int channel = Mix_PlayChannelTimed(_channel, _sound, repeat_times, limit_ms);
    if (channel == -1){
        printf("Error on playing sound. %s\n", Mix_GetError());
    }
    else{
        if (_2d_effect) G2D_Engine::instance->audio->add(this, channel);
    }

    return channel;
}

void G2D_Sound::setPosition(int x, int y) {
    _x = x;
    _y = y;

    _2d_effect = true;
}

void G2D_Sound::setPosition(G2D_Point point) {
    _x = point.x;
    _y = point.y;

    _2d_effect = true;
}

void G2D_Sound::setX(int x) {
    _x = x;

    _2d_effect = true;
}

void G2D_Sound::setY(int y) {
    _y = y;

    _2d_effect = true;
}

int G2D_Sound::getX() {
    return _x;
}

int G2D_Sound::getY() {
    return _y;
}

void G2D_Sound::disable2DEffect() {
    _2d_effect = false;
}

void G2D_Sound::setVolume(int volume){
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    int v = (int)round(((float)volume/100.0f)*MIX_MAX_VOLUME);

    Mix_VolumeChunk(_sound, v);
}

int G2D_Sound::getVolume() {
    int v = (int)round(((float)Mix_VolumeChunk(_sound, -1)/(float)MIX_MAX_VOLUME)*100);

    return v;
}

void G2D_Sound::free() {
    if (_sound != nullptr){
        Mix_FreeChunk(_sound);
        _sound = nullptr;
    }
}
