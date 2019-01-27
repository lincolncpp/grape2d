#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <string>

#include "../include/grape2d.h"

G2D_Texture::G2D_Texture(G2D_Engine *engine) {
    _engine = engine;
}

G2D_Texture::~G2D_Texture() {
    free();
}

bool G2D_Texture::loadFromFile(const char *path) {
    free();

    // Loading from file
    _texture = IMG_LoadTexture(_engine->_renderer, path);

    if (_texture == nullptr){
        _engine->setError("Error on loading texture from file '%s'", path);
        return false;
    }
    else{
        // Getting texture dimensions
        SDL_QueryTexture(_texture, nullptr, nullptr, &_width, &_height);
        return true;
    }
}

void G2D_Texture::free() {
    if (_texture != nullptr){
        SDL_DestroyTexture(_texture);
    }
}

void G2D_Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void G2D_Texture::setBlendMode(SDL_BlendMode blendMode) {
    SDL_SetTextureBlendMode(_texture, blendMode);
}

void G2D_Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

void G2D_Texture::render(int x, int y, SDL_Rect *clip) {
    SDL_Rect rect = {x, y, _width, _height};

    if (clip != nullptr){
        rect.w = clip->w;
        rect.h = clip->h;
    }

    SDL_RenderCopy(_engine->_renderer, _texture, clip, &rect);

}

int G2D_Texture::getWidth() {
    return _width;
}

int G2D_Texture::getHeight() {
    return _height;
}