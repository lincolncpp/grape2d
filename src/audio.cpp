#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#ifdef _WIN32
    #include <math.h>
#endif

#include "../include/grape2d.h"

void G2D_Engine::G2D_Audio::add(G2D_Sound *sound, int channel) {
    _sound[channel] = sound;
}

void G2D_Engine::G2D_Audio::update() {
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

                if (distance > _audible_radius) distance = _audible_radius;
                auto d = (Uint8) ((distance / (double) _audible_radius) * 255);

                G2D_Engine::instance->mixer->setPosition(i, (Sint16) angle, d);
            }
            else{
                _sound[i] = nullptr;
                G2D_Engine::instance->mixer->removeEffects(i);
            }
        }
    }
}

void G2D_Engine::G2D_Audio::setAudibleRadius(int radius) {
    if (radius < 1) radius = 1;

    _audible_radius = radius;
}

int G2D_Engine::G2D_Audio::getAudibleRadius() {
    return _audible_radius;
}
