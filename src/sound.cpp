#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#ifdef _WIN32
    #include <math.h>
#endif

#include "../include/grape2d.h"

using namespace G2D;

Sound::Sound(const char *path) {
    _sound = Mix_LoadWAV(path);

    if (_sound == nullptr){
        printf("Error on loading sound. %s\n", Mix_GetError());
        return;
    }
}

Sound::~Sound() {
    free();
}

void Sound::setChannel(int channel) {
    _channel = channel;
}

int Sound::getChannel() {
    return _channel;
}

int Sound::play(int repeat_times, int limit_ms) {
    int channel = Mix_PlayChannelTimed(_channel, _sound, repeat_times, limit_ms);
    if (channel == -1){
        printf("Error on playing sound. %s\n", Mix_GetError());
    }
    Engine::instance->mixer->add(this, channel);

    return channel;
}

void Sound::setPosition(int x, int y) {
    _position.x = x;
    _position.y = y;

    _2d_effect = true;
}

void Sound::setPosition(Point point) {
    _position = point;
    _2d_effect = true;
}

void Sound::setX(int x) {
    _position.x = x;

    _2d_effect = true;
}

void Sound::setY(int y) {
    _position.y = y;

    _2d_effect = true;
}

int Sound::getX() {
    return _position.x;
}

int Sound::getY() {
    return _position.y;
}

void Sound::disable2DEffect() {
    _2d_effect = false;
}

void Sound::setVolume(int volume){
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    int v = (int)round(((float)volume/100.0f)*MIX_MAX_VOLUME);

    Mix_VolumeChunk(_sound, v);
}

int Sound::getVolume() {
    int v = (int)round(((float)Mix_VolumeChunk(_sound, -1)/(float)MIX_MAX_VOLUME)*100);

    return v;
}

void Sound::free() {
    if (_sound != nullptr){
        Mix_FreeChunk(_sound);
        delete _sound;
    }
}