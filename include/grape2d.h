#ifndef GRAPE2D_H
#define GRAPE2D_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <string>

class G2D_Engine;
class G2D_Texture;
class G2D_Font;
class G2D_Text;

struct G2D_Color{
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = -1;
};


class G2D_Engine{
    friend class G2D_Texture;

private:
    SDL_Renderer* _renderer;

    // Window
    SDL_Window* _window = nullptr;
    int _window_width;
    int _window_height;

    // FPS
    int real_fps = 0;

    // Error
    bool _debug = false;
    std::string _error = "";
    bool _has_error = false;

    void setError(const char *text, ...);

public:
    G2D_Engine(int width, int height, const char *title, bool debug = false, Uint32 SDL_flags = SDL_RENDERER_ACCELERATED);
    ~G2D_Engine();

    bool hasError();
    const char* getError();

    int getWindowWidth();
    int getWindowHeight();

    int getFPS();

    void start(void (*event)(SDL_Event), void (*loop)(int), void (*render)());
};


class G2D_Texture{
    friend class G2D_Text;

private:
    G2D_Engine *_engine = nullptr;
    SDL_Texture *_texture = nullptr;

    int _width;
    int _height;

    bool loadFromFont(G2D_Font *font, const char *text, G2D_Color color);

public:
    G2D_Texture(G2D_Engine *engine);
    ~G2D_Texture();

    bool loadFromFile(const char *path);
    void free();

    void setColor(G2D_Color color);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(Uint8 alpha);

    void render(int x, int y, SDL_Rect *clip = nullptr);

    int getWidth();
    int getHeight();
};

class G2D_Font{
    friend class G2D_Texture;

private:
    TTF_Font *_font = nullptr;
    std::string _font_name;
    int _size;

public:
    G2D_Font(const char *font_name, int size);
    ~G2D_Font();

    void free();

    void setSize(int size);
};

class G2D_Text{
private:
    G2D_Engine *_engine;
    G2D_Font *_font;
    G2D_Texture *_texture;

    std::string _text;
    G2D_Color _color;

    void reloadTexture();

public:
    G2D_Text(G2D_Engine *engine, G2D_Font *font, const char *text, ...);
    ~G2D_Text();

    void setColor(G2D_Color color);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setAlpha(Uint8 alpha);
    void setText(const char *text, ...);
    void setFont(G2D_Font *font);


    void render(int x, int y);
};


#endif