#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#ifdef _WIN32
    #include <math.h>
#endif

#include "../include/grape2d.h"

void G2D_Engine::G2D_Mixer::setChannelVolume(int volume, int channel){
    int v = (int)round(((float)volume/100.0f)*MIX_MAX_VOLUME);

    Mix_Volume(channel, v);
}

int G2D_Engine::G2D_Mixer::getChannelVolume(int channel) {
    int v = (int)round(((float)Mix_Volume(channel, -1)/(float)MIX_MAX_VOLUME)*100);

    return v;
}

void G2D_Engine::G2D_Mixer::setMaxChannels(int num_channels) {
    if (num_channels < G2D_MIN_CHANNEL) num_channels = G2D_MIN_CHANNEL;
    if (num_channels > G2D_MAX_CHANNEL) num_channels = G2D_MAX_CHANNEL;

    Mix_AllocateChannels(num_channels);
}

void G2D_Engine::G2D_Mixer::resumeChannel(int channel) {
    Mix_Resume(channel);
}

void G2D_Engine::G2D_Mixer::pauseChannel(int channel) {
    Mix_Pause(channel);
}

void G2D_Engine::G2D_Mixer::endChannel(int channel) {
    Mix_HaltChannel(channel);
}

void G2D_Engine::G2D_Mixer::endChannelTimed(int channel, int time_ms) {
    Mix_ExpireChannel(channel, time_ms);
}

void G2D_Engine::G2D_Mixer::endChannelFadeOut(int channel, int time_ms) {
    Mix_FadeOutChannel(channel, time_ms);
}

void G2D_Engine::G2D_Mixer::setPlanning(int channel, Uint8 left, Uint8 right) {
    if(!Mix_SetPanning(channel, left, right)) {
        printf("Error on set planning. %s\n", Mix_GetError());
    }
}

void G2D_Engine::G2D_Mixer::setDistance(int channel, Uint8 distance) {
    if(!Mix_SetDistance(channel, distance)) {
        printf("Error on set distance. %s\n", Mix_GetError());
    }
}

void G2D_Engine::G2D_Mixer::setPosition(int channel, Sint16 angle, Uint8 distance) {
    if(!Mix_SetPosition(channel, angle, distance)) {
        printf("Error on set position. %s\n", Mix_GetError());
    }
}

void G2D_Engine::G2D_Mixer::removeEffects(int channel) {
    if(!Mix_UnregisterAllEffects(channel)) {
        printf("Error on remove effects. %s\n", Mix_GetError());
    }
}

void G2D_Engine::G2D_Mixer::add(G2D_Sound *sound, int channel) {
    _sound[channel] = sound;
}

void G2D_Engine::G2D_Mixer::update() {
    for (int i = 0;i < G2D_MAX_CHANNEL;i++){
        if (_sound[i] != nullptr && _sound[i]->_2d_effect){
            if (Mix_Playing(i)) {
                int sound_x = _sound[i]->getX();
                int sound_y = _sound[i]->getY();
                int cam_x = G2D_Engine::instance->camera->getCenterX();
                int cam_y = G2D_Engine::instance->camera->getCenterY();


                double a = sound_x - cam_x;
                double b = cam_y - sound_y;
                double distance = sqrt(pow(a, 2) + pow(b, 2));

                double angle = 0;

                if (a == 0 && b > 0) angle = 0;
                else if (a > 0 && b == 0) angle = PI / 2.0f;
                else if (a == 0 && b < 0) angle = PI;
                else if (a < 0 && b == 0) angle = 3.0f / 2.0f * PI;

                else if (a > 0 && b > 0) angle = atan(a / b);
                else if (a > 0 && b < 0) angle = atan(-b / a) + PI / 2.0f;
                else if (a < 0 && b < 0) angle = atan(-a / -b) + PI;
                else if (a < 0 && b > 0) angle = atan(b / -a) + 3.0f / 2.0f * PI;

                angle = angle * 180.0f / PI;

                if (distance > _max_sound_distance) distance = _max_sound_distance;
                auto d = (Uint8) ((distance / (double) _max_sound_distance) * 255);

                G2D_Engine::instance->mixer->setPosition(i, (Sint16) angle, d);
            }
            else{
                _sound[i] = nullptr;
                G2D_Engine::instance->mixer->removeEffects(i);
            }
        }
    }
}

void G2D_Engine::G2D_Mixer::setMaxSoundDistance(int radius) {
    if (radius < 1) radius = 1;

    _max_sound_distance = radius;
}

int G2D_Engine::G2D_Mixer::getMaxSoundDistance() {
    return _max_sound_distance;
}

