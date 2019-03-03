#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Engine *G2D_SFX::_engine = nullptr;

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

bool G2D_SFX::play(int repeat_times, int limit_ms) {
    if (Mix_PlayChannelTimed(_channel, _sound, repeat_times, limit_ms) == -1){
        printf("Error on playing sound. %s\n", Mix_GetError());
        return false;
    }

    return true;
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