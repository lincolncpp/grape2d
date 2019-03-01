#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Engine *G2D_Font::_engine = nullptr;

G2D_Font::G2D_Font(const char *path, int size) {
    _path = path;
    _size = size;

    loadFont(path, size);
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

bool G2D_Font::loadFont(const char *path, int size) {
    free();

    _font = TTF_OpenFont(path, size);

    if (_font == nullptr){
        printf("Error on loading font. %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void G2D_Font::setSize(int size) {
    loadFont(_path.c_str(), size);
}
