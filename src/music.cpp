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

Music::Music(const char *path) {
    _music = Mix_LoadMUS(path);

    if (_music == nullptr){
        printf("Error on loading music. %s\n", Mix_GetError());
        return;
    }
}

Music::~Music() {
    free();
}

void Music::updateVolume() {
    if (Engine::instance->mixer->_playing_music == this) {
        int v = (int) round(((float)_volume / 100.0f) * MIX_MAX_VOLUME);

        Mix_VolumeMusic(v);
    }
}

int Music::play(bool looping) {
    int channel = Mix_PlayMusic(_music, looping?-1:0);
    if (channel == -1){
        printf("Error on playing music. %s\n", Mix_GetError());
    }
    else{
        Engine::instance->mixer->_playing_music = this;
        updateVolume();
    }

    return channel;
}

int Music::playFadeIn(bool looping, int time) {
    int channel = Mix_FadeInMusic(_music, looping?-1:0, time);
    if (channel == -1){
        printf("Error on playing music. %s\n", Mix_GetError());
    }
    else{
        Engine::instance->mixer->_playing_music = this;
        updateVolume();
    }

    return channel;
}

void Music::rewind() {
    if (Mix_PlayingMusic() && !Mix_PausedMusic() && Engine::instance->mixer->_playing_music == this) {
        Mix_RewindMusic();
    }
}

void Music::setVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    _volume = (int)volume;

    updateVolume();
}

int Music::getVolume() {
    return _volume;
}

void Music::resume() {
    if (Mix_PlayingMusic() && Mix_PausedMusic() && Engine::instance->mixer->_playing_music == this){
        Mix_ResumeMusic();
    }
}

void Music::pause() {
    if (Mix_PlayingMusic() && !Mix_PausedMusic() && Engine::instance->mixer->_playing_music == this){
        Mix_PauseMusic();
    }
}

void Music::stop() {
    if (Mix_PlayingMusic() && Engine::instance->mixer->_playing_music == this){
        Mix_HaltMusic();
    }
}

void Music::stopFadeOut(int effect_time_ms) {
    if (Mix_PlayingMusic() && Engine::instance->mixer->_playing_music == this) {
        Mix_FadeOutMusic(effect_time_ms);
    }
}

void Music::free() {
    if (_music != nullptr) {
        Mix_FreeMusic(_music);
        _music = nullptr;
    }
}
