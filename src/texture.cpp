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
        SDL_QueryTexture(_texture, nullptr, nullptr, &_src_width, &_src_height);

        _width = _src_width;
        _height = _src_height;
    }

    return true;
}

bool G2D_Texture::loadFromFont(G2D_Font *font, const char *text, G2D_Color color) {
    free();

    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};

    SDL_Surface *textSurface = TTF_RenderText_Blended(font->_font, text, sdl_color);
    if (textSurface == nullptr){
        _engine->setError("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

        return false;
    }
    else{
        _texture = SDL_CreateTextureFromSurface(_engine->_renderer, textSurface);

        if (_texture == nullptr){
            _engine->setError("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

            return false;
        }
        else{
            _src_width = _width = textSurface->w;
            _src_height = _height = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }

    return true;
}

void G2D_Texture::free() {
    if (_texture != nullptr){
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

void G2D_Texture::setColor(G2D_Color color) {
    SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
    setAlpha(color.a);
}

void G2D_Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void G2D_Texture::setBlendMode(G2D_BlendMode blendMode) {
    SDL_BlendMode blend;
    if (blendMode == G2D_BLENDMODE_NONE)        blend = SDL_BLENDMODE_NONE;
    else if (blendMode == G2D_BLENDMODE_BLEND)  blend = SDL_BLENDMODE_BLEND;
    else if (blendMode == G2D_BLENDMODE_ADD)    blend = SDL_BLENDMODE_ADD;
    else                                        blend = SDL_BLENDMODE_MOD;

    SDL_SetTextureBlendMode(_texture, blend);
}

void G2D_Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

void G2D_Texture::render(int x, int y, G2D_Rect *clip, double angle, G2D_Point *center, bool flip_horizontal, bool flip_vertical) {
    double scale = _engine->_draw_scale;

    SDL_Rect rect = {x, y, int(_width*scale), int(_height*scale)};
    SDL_Rect *clip2 = nullptr;
    SDL_Point *center2 = nullptr;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if (clip != nullptr){
        if (_src_width == _width && _src_height == _height) {
            rect.w = int(clip->w * scale);
            rect.h = int(clip->h * scale);
        }

        clip2 = new SDL_Rect();
        clip2->x = clip->x;
        clip2->y = clip->y;
        clip2->w = clip->w;
        clip2->h = clip->h;
    }

    if (center != nullptr){
        center2 = new SDL_Point();
        center2->x = center->x;
        center2->y = center->y;
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

    SDL_RenderCopyEx(_engine->_renderer, _texture, clip2, &rect, angle, center2, flip);
}


void G2D_Texture::setSize(int width, int height) {
    _width = width;
    _height = height;
}

int G2D_Texture::getSrcWidth() {
    return _src_width;
}

int G2D_Texture::getWidth() {
    return _width;
}

int G2D_Texture::getSrcHeight() {
    return _src_height;
}

int G2D_Texture::getHeight() {
    return _height;
}