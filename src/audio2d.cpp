#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

void G2D_Engine::G2D_2DAudio::add(G2D_SFX *sfx, int channel) {
    _sfx2d[channel] = sfx;
}

void G2D_Engine::G2D_2DAudio::update() {
    for (int i = 0;i < G2D_MAX_CHANNEL;i++){
        if (_sfx2d[i] != nullptr && _sfx2d[i]->_sound_2d){
            if (Mix_Playing(i)) {
                int sfx_x = _sfx2d[i]->getX();
                int sfx_y = _sfx2d[i]->getY();
                int cam_x = G2D_Engine::instance->camera->getX();
                int cam_y = G2D_Engine::instance->camera->getY();


                double a = sfx_x - cam_x;
                double b = cam_y - sfx_y;
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
                _sfx2d[i] = nullptr;
                G2D_Engine::instance->mixer->removeEffects(i);
            }
        }
    }
}

void G2D_Engine::G2D_2DAudio::setAudibleRadius(int radius) {
    if (radius < 1) radius = 1;

    _audible_radius = radius;
}

int G2D_Engine::G2D_2DAudio::getAudibleRadius() {
    return _audible_radius;
}