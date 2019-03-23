#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Text::G2D_Text(G2D_Font *font, const char *text, ...) {
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

G2D_Text::~G2D_Text() {
    delete _texture;
}

void G2D_Text::setColor(G2D_Color color) {
    _color = color;

    reloadTexture();
}

void G2D_Text::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    _color.r = red;
    _color.g = green;
    _color.b = blue;

    reloadTexture();
}

void G2D_Text::setAlpha(uint8_t alpha) {
    _color.a = alpha;
    _texture->setAlpha(_color.a);
}

void G2D_Text::setText(const char *text, ...) {

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

void G2D_Text::setFont(G2D_Font *font) {
    _font = font;

    reloadTexture();
}

void G2D_Text::setReferential(G2D_Referential referential) {
    _referential = referential;

    _texture->setReferential(_referential);
}

void G2D_Text::render(int x, int y) {
    _texture->render(x, y);
}


void G2D_Text::reloadTexture() {
    if (_texture != nullptr){
        _texture->free();
        delete _texture;
    }
    _texture = new G2D_Texture(_font, _text.c_str(), _color);
    _texture->setReferential(_referential);
}
