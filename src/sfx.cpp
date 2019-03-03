#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_SFX::G2D_SFX(const char *path) {
    _sound = Mix_LoadWAV(path);

    if (_sound == nullptr){
        printf("Error on loading sound. %s\n", Mix_GetError());
        return;
    }
}

G2D_SFX::~G2D_SFX() {
    free();
}

void G2D_SFX::setChannel(int channel) {
    _channel = channel;
}

int G2D_SFX::getChannel() {
    return _channel;
}

int G2D_SFX::play(int repeat_times, int limit_ms) {
    int channel = Mix_PlayChannelTimed(_channel, _sound, repeat_times, limit_ms);
    if (channel == -1){
        printf("Error on playing sound. %s\n", Mix_GetError());
    }
    else{
        if (_sound_2d) G2D_Engine::instance->audio2d->add(this, channel);
    }

    return channel;
}

void G2D_SFX::sound2D(bool state) {
    _sound_2d = state;
}

void G2D_SFX::setPosition(int x, int y) {
    _x = x;
    _y = y;
}

void G2D_SFX::setX(int x) {
    _x = x;
}

void G2D_SFX::setY(int y) {
    _y = y;
}

int G2D_SFX::getX() {
    return _x;
}

int G2D_SFX::getY() {
    return _y;
}

void G2D_SFX::setVolume(int volume){
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    int v = (int)round(((float)volume/100.0f)*MIX_MAX_VOLUME);

    Mix_VolumeChunk(_sound, v);
}

int G2D_SFX::getVolume() {
    int v = (int)round(((float)Mix_VolumeChunk(_sound, -1)/(float)MIX_MAX_VOLUME)*100);

    return v;
}

void G2D_SFX::free() {
    if (_sound != nullptr){
        Mix_FreeChunk(_sound);
        _sound = nullptr;
    }
}