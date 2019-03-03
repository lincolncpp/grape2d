#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Music *G2D_Music::_playing_now = nullptr;

G2D_Music::G2D_Music(const char *path) {
    _music = Mix_LoadMUS(path);

    if (_music == nullptr){
        printf("Error on loading music. %s\n", Mix_GetError());
        return;
    }
}

G2D_Music::~G2D_Music() {
    free();
}

void G2D_Music::updateVolume() {
    if (G2D_Music::_playing_now == this) {
        int v = (int) round(((float)_volume / 100.0f) * MIX_MAX_VOLUME);

        Mix_VolumeMusic(v);
    }
}

int G2D_Music::play(bool looping) {
    int channel = Mix_PlayMusic(_music, looping?-1:0);
    if (channel == -1){
        printf("Error on playing music. %s\n", Mix_GetError());
    }
    else{
        G2D_Music::_playing_now = this;
        updateVolume();
    }

    return channel;
}

int G2D_Music::playFadeIn(bool looping, int effect_time_ms) {
    int channel = Mix_FadeInMusic(_music, looping?-1:0, effect_time_ms);
    if (channel == -1){
        printf("Error on playing music. %s\n", Mix_GetError());
    }
    else{
        G2D_Music::_playing_now = this;
        updateVolume();
    }

    return channel;
}

void G2D_Music::rewind() {
    if (Mix_PlayingMusic() && !Mix_PausedMusic() && G2D_Music::_playing_now == this) {
        Mix_RewindMusic();
    }
}

void G2D_Music::setVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    _volume = volume;

    updateVolume();
}

int G2D_Music::getVolume() {
    return _volume;
}

void G2D_Music::resume() {
    if (Mix_PlayingMusic() && Mix_PausedMusic() && G2D_Music::_playing_now == this){
        Mix_ResumeMusic();
    }
}

void G2D_Music::pause() {
    if (Mix_PlayingMusic() && !Mix_PausedMusic() && G2D_Music::_playing_now == this){
        Mix_PauseMusic();
    }
}

void G2D_Music::stop() {
    if (Mix_PlayingMusic() && G2D_Music::_playing_now == this){
        Mix_HaltMusic();
    }
}

void G2D_Music::stopFadeOut(int effect_time_ms) {
    if (Mix_PlayingMusic() && G2D_Music::_playing_now == this) {
        Mix_FadeOutMusic(effect_time_ms);
    }
}

void G2D_Music::free() {
    if (_music != nullptr) {
        Mix_FreeMusic(_music);
        _music = nullptr;
    }
}