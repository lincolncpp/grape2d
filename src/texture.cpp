#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

using namespace G2D;

Texture::~Texture() {
    free();
}

Texture::Texture(const char *path) {
    free();

    // Loading from file
    _texture = IMG_LoadTexture(Engine::instance->_renderer, path);

    if (_texture == nullptr){
        printf("Error on loading texture. %s\n", IMG_GetError());
        return;
    }

    // Getting texture dimensions
    int real_width, real_height;
    SDL_QueryTexture(_texture, nullptr, nullptr, &real_width, &real_height);

    _width = _src_width = (int)real_width;
    _height = _src_height = (int)real_height;
}

Texture::Texture(Font *font, const char *text, Color color) {
    free();

    SDL_Color sdl_color = {(Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a};

    SDL_Surface *textSurface = TTF_RenderText_Blended(font->_font, text, sdl_color);
    if (textSurface == nullptr){
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else{
        _texture = SDL_CreateTextureFromSurface(Engine::instance->_renderer, textSurface);

        if (_texture == nullptr){
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

        }
        else{
            _src_width = _width = textSurface->w;
            _src_height = _height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }
}

void Texture::free() {
    if (_texture != nullptr){
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

void Texture::setColor(Color color) {
    SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
    setAlpha(color.a);
}

void Texture::setColor(int red, int green, int blue) {
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void Texture::setBlendMode(BlendMode blendMode) {
    SDL_BlendMode blend;
    if (blendMode == BM_NONE)        blend = SDL_BLENDMODE_NONE;
    else if (blendMode == BM_BLEND)  blend = SDL_BLENDMODE_BLEND;
    else if (blendMode == BM_ADD)    blend = SDL_BLENDMODE_ADD;
    else                                        blend = SDL_BLENDMODE_MOD;

    SDL_SetTextureBlendMode(_texture, blend);
}

void Texture::setAlpha(int alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

void Texture::setReferential(Referential referential) {
    _referential = referential;
}

void Texture::render(int x, int y, Rect *clip, double angle, Point *center, bool flip_horizontal, bool flip_vertical) {
    SDL_Rect rect = {x, y, _width, _height};
    SDL_Rect clip2 = {0, 0, _width, _height};
    SDL_Point center2 = {0, 0};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (_referential == R_RELATIVE){
        rect.x = x-Engine::instance->camera->getCornerX();
        rect.y = y-Engine::instance->camera->getCornerY();
    }

    if (clip != nullptr){
        if (_src_width == _width && _src_height == _height) {
            rect.w = clip->w;
            rect.h = clip->h;
        }

        clip2.x = clip->x;
        clip2.y = clip->y;
        clip2.w = clip->w;
        clip2.h = clip->h;
    }

    if (center != nullptr){
        center2.x = center->x;
        center2.y = center->y;
    }

    if (flip_horizontal && flip_vertical){
        flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    }
    else if (flip_horizontal){
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (flip_vertical){
        flip = SDL_FLIP_VERTICAL;
    }

    SDL_RenderCopyEx(Engine::instance->_renderer, _texture, &clip2, &rect, angle, &center2, flip);
}


void Texture::setSize(int width, int height) {
    _width = (int)width;
    _height = (int)height;
}

int Texture::getSrcWidth() {
    return _src_width;
}

int Texture::getWidth() {
    return _width;
}

int Texture::getSrcHeight() {
    return _src_height;
}

int Texture::getHeight() {
    return _height;
}
