#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

using namespace G2D;

Text::Text(Font *font, const char *text, ...) {
    _font = font;

    char *msg = nullptr;
    va_list args;
    va_start(args, text);
    vasprintf(&msg, text, args);
    va_end(args);

    _text = text;

    reloadTexture();

    delete msg;
}

Text::~Text() {
    delete _texture;
}

void Text::setColor(Color color) {
    _color = color;

    reloadTexture();
}

void Text::setColor(int red, int green, int blue) {
    _color.r = red;
    _color.g = green;
    _color.b = blue;

    reloadTexture();
}

void Text::setAlpha(int alpha) {
    _color.a = alpha;
    _texture->setAlpha(_color.a);
}

void Text::setText(const char *text, ...) {

    char *msg = nullptr;
    va_list args;
    va_start(args, text);
    free(msg);
    vasprintf(&msg, text, args);
    va_end(args);

    _text = msg;

    reloadTexture();

    delete msg;
}

void Text::setFont(Font *font) {
    _font = font;

    reloadTexture();
}

void Text::setReferential(Referential referential) {
    _referential = referential;

    _texture->setReferential(_referential);
}

void Text::render(int x, int y) {
    _texture->render(x, y);
}


void Text::reloadTexture() {
    if (_texture != nullptr){
        _texture->free();
        delete _texture;
    }
    _texture = new Texture(_font, _text.c_str(), _color);
    _texture->setReferential(_referential);
}
