#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

using namespace G2D;

Font::Font(const char *path, int size) {
    _path = path;
    _size = size;

    loadFont(path, size);
}

Font::~Font() {
    free();
}

void Font::free() {
    if (_font != nullptr){
        TTF_CloseFont(_font);
        _font = nullptr;
    }
}

bool Font::loadFont(const char *path, int size) {
    free();

    _font = TTF_OpenFont(path, size);

    if (_font == nullptr){
        printf("Error on loading font. %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void Font::setSize(int size) {
    loadFont(_path.c_str(), size);
}
