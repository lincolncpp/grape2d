#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <string>

#include "../include/grape2d.h"

G2D_Font::G2D_Font(const char *font_name, int size) {
    _font_name = font_name;
    _size = size;

    _font = TTF_OpenFont(font_name, size);
}

G2D_Font::~G2D_Font() {
    free();
}

void G2D_Font::free() {
    if (_font != nullptr){
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}

void G2D_Font::setSize(int size) {
    free();

    _font = TTF_OpenFont(_font_name.c_str(), size);
}
