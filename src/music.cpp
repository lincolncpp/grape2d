#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Engine *G2D_Music::_engine = nullptr;

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

void G2D_Music::play(bool looping) {
    if (Mix_PlayingMusic()){
        Mix_HaltMusic();
    }

    Mix_PlayMusic(_music, looping?-1:0);
    G2D_Music::_playing_now = this;
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

void G2D_Music::free() {
    if (_music != nullptr) {
        Mix_FreeMusic(_music);
        _music = nullptr;
    }
}