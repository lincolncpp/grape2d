#ifndef GRAPE2D_H
#define GRAPE2D_H

#include <string>

class G2D_Engine{
friend class G2D_Texture;

private:
    SDL_Renderer* _renderer;

    // Window
    SDL_Window* _window = nullptr;
    int _window_width;
    int _window_height;

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

    void start(void (*event)(SDL_Event), void (*loop)(), void (*render)());
};


class G2D_Texture{
private:
    G2D_Engine *_engine = nullptr;
    SDL_Texture *_texture = nullptr;

    int _width;
    int _height;

public:
    G2D_Texture(G2D_Engine *engine);
    ~G2D_Texture();

    bool loadFromFile(const char *path);
    void free();

    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blendMode);
    void setAlpha(Uint8 alpha);

    void render(int x, int y, SDL_Rect *clip = nullptr);

    int getWidth();
    int getHeight();
};


#endif