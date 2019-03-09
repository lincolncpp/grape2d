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
}

G2D_Text::~G2D_Text() {
    delete _texture;
}

void G2D_Text::setColor(G2D_Color color) {
    _color = color;

    reloadTexture();
}

void G2D_Text::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    _color.r = red;
    _color.g = green;
    _color.b = blue;

    reloadTexture();
}

void G2D_Text::setAlpha(Uint8 alpha) {
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
}

void G2D_Text::setFont(G2D_Font *font) {
    _font = font;

    reloadTexture();
}

void G2D_Text::render(int x, int y) {
    _texture->render(x, y);
}

void G2D_Text::renderHUD(int x, int y) {
    _texture->renderHUD(x, y);
}

void G2D_Text::reloadTexture() {
    _texture = new G2D_Texture(_font, _text.c_str(), _color);
}
