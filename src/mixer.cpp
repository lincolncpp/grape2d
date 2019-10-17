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

void Engine::Mixer::setChannelVolume(int volume, int channel){
    int v = (int)round(((float)volume/100.0f)*MIX_MAX_VOLUME);

    Mix_Volume(channel, v);
}

int Engine::Mixer::getChannelVolume(int channel) {
    int v = (int)round(((float)Mix_Volume(channel, -1)/(float)MIX_MAX_VOLUME)*100);

    return v;
}

void Engine::Mixer::setMaxChannels(int num_channels) {
    if (num_channels < G2D_MIN_CHANNEL) num_channels = G2D_MIN_CHANNEL;
    if (num_channels > G2D_MAX_CHANNEL) num_channels = G2D_MAX_CHANNEL;

    Mix_AllocateChannels(num_channels);
}

void Engine::Mixer::resumeChannel(int channel) {
    Mix_Resume(channel);
}

void Engine::Mixer::pauseChannel(int channel) {
    Mix_Pause(channel);
}

void Engine::Mixer::endChannel(int channel) {
    Mix_HaltChannel(channel);
}

void Engine::Mixer::endChannelTimed(int channel, int time_ms) {
    Mix_ExpireChannel(channel, time_ms);
}

void Engine::Mixer::endChannelFadeOut(int channel, int time_ms) {
    Mix_FadeOutChannel(channel, time_ms);
}

void Engine::Mixer::setPlanning(int channel, int left, int right) {
    if(!Mix_SetPanning(channel, left, right)) {
        printf("Error on set planning. %s\n", Mix_GetError());
    }
}

void Engine::Mixer::setDistance(int channel, int distance) {
    if(!Mix_SetDistance(channel, distance)) {
        printf("Error on set distance. %s\n", Mix_GetError());
    }
}

void Engine::Mixer::setPosition(int channel, int angle, int distance) {
    if(!Mix_SetPosition(channel, angle, distance)) {
        printf("Error on set position. %s\n", Mix_GetError());
    }
}

void Engine::Mixer::removeEffects(int channel) {
    if(!Mix_UnregisterAllEffects(channel)) {
        printf("Error on remove effects. %s\n", Mix_GetError());
    }
}

Music *Engine::Mixer::getPlayingMusic() {
    return _playing_music;
}

void Engine::Mixer::add(Sound *sound, int channel) {
    _sound[channel] = sound;
}

void Engine::Mixer::update() {
    for (int i = 0;i < G2D_MAX_CHANNEL;i++){
        if (_sound[i] != nullptr && _sound[i]->_2d_effect){
            if (Mix_Playing(i)) {
                int sound_x = _sound[i]->getX();
                int sound_y = _sound[i]->getY();
                int cam_x = Engine::instance->camera->getCenterX();
                int cam_y = Engine::instance->camera->getCenterY();

                double a = sound_x - cam_x;
                double b = cam_y - sound_y;
                double distance = sqrt(pow(a, 2) + pow(b, 2));

                double angle = 0;

                if (a == 0 && b > 0) angle = 0;
                else if (a > 0 && b == 0) angle = G2D_PI / 2.0f;
                else if (a == 0 && b < 0) angle = G2D_PI;
                else if (a < 0 && b == 0) angle = 3.0f / 2.0f * G2D_PI;

                else if (a > 0 && b > 0) angle = atan(a / b);
                else if (a > 0 && b < 0) angle = atan(-b / a) + G2D_PI / 2.0f;
                else if (a < 0 && b < 0) angle = atan(-a / -b) + G2D_PI;
                else if (a < 0 && b > 0) angle = atan(b / -a) + 3.0f / 2.0f * G2D_PI;

                angle = angle * 180.0f / G2D_PI;

                if (distance > _max_sound_distance) distance = _max_sound_distance;
                auto d = (int) ((distance / (double) _max_sound_distance) * 255);

                Engine::instance->mixer->setPosition(i, (int) angle, d);
            }
            else{
                _sound[i] = nullptr;
                Engine::instance->mixer->removeEffects(i);
            }
        }
    }
}

void Engine::Mixer::setMaxSoundDistance(int radius) {
    if (radius < 1) radius = 1;

    _max_sound_distance = radius;
}

int Engine::Mixer::getMaxSoundDistance() {
    return _max_sound_distance;
}