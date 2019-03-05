#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#include "../include/grape2d.h"

G2D_Engine *G2D_Engine::instance = nullptr;

G2D_Engine::G2D_Engine(int width, int height, const char *title, bool debug, Uint32 SDL_flags) {
    _debug = debug;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        setError("SDL could not initialize! SDL_Error: %s", SDL_GetError());
    }
    else {
        // Create Window
        _window_width = width;
        _window_height = height;

        _window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _window_width, _window_height, SDL_WINDOW_SHOWN);
        if(_window == nullptr) {
            setError("Window could not be created! SDL_Error: %s", SDL_GetError());
        }
        else {
            // Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;

            if(!(IMG_Init(imgFlags)  & imgFlags)){
                setError("SDL_image could not initialize! SDL_image Error: %s", IMG_GetError());
            }
            else {
                // Creating renderer
                _renderer = SDL_CreateRenderer(_window, -1, SDL_flags);

                if(_renderer == nullptr){
                    setError("Renderer could not be created! SDL Error: %s", SDL_GetError());
                }
                else{
                    SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);

                    // Initialize SDL_ttf
                    if(TTF_Init() == -1) {
                        setError("SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError());
                    }
                    else{
                        //Initialize SDL_mixer
                        if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
                            setError("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                        }
                        else{
                            G2D_Engine::instance = this;

                            mixer = new G2D_Mixer();
                            Mix_AllocateChannels(100);

                            camera = new G2D_Camera();

                            audio = new G2D_Audio();
                        }
                    }
                }
            }
        }
    }
}

G2D_Engine::~G2D_Engine() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);

    _window = nullptr;
    _renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();
}

bool G2D_Engine::hasError() {
    return _has_error;
}

const char* G2D_Engine::getError() {
    return _error.c_str();
}

void G2D_Engine::setError(const char *text, ...) {
    char *msg = nullptr;

    va_list args;
    va_start(args, text);
    vasprintf(&msg, text, args);
    va_end(args);

    _error = msg;
    _has_error = true;

    if (_debug){
        printf("%s\n", msg);
    }
}

int G2D_Engine::getWindowWidth() {
    return _window_width;
}

int G2D_Engine::getWindowHeight() {
    return _window_height;
}

int G2D_Engine::getFPS() {
    return _real_fps;
}

G2D_Event G2D_Engine::convertSDLEventtoG2DEvent(SDL_Event e) {
    G2D_Event ge = {};

    // Setting mouse x, y
    SDL_GetMouseState(&ge.mouse_x, &ge.mouse_y);

    // Setting mouse state
    if (e.type == SDL_MOUSEMOTION)          ge.mouse_state = G2D_MOUSEMOVE;
    else if (e.type == SDL_MOUSEBUTTONDOWN) ge.mouse_state = G2D_MOUSEDOWN;
    else if (e.type == SDL_MOUSEBUTTONUP)   ge.mouse_state = G2D_MOUSEUP;

    ge.key_state = SDL_GetKeyboardState(nullptr);

    return ge;
}

void G2D_Engine::start(void (*event)(G2D_Event), void (*loop)(Uint32), void (*render)()) {
    if (_has_error) return;
    if (render == nullptr) return;

    bool quit = false;
    SDL_Event e;

    Uint32 tick = SDL_GetTicks();
    int frame = 0;
    Uint32 framei = 0;

    // Main loop
    while (!quit) {

        // Sound effect update (Ambient 2D)
        if (framei % 20 == 0){
            audio->update();
        }

        // Input handle event
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            }

            if (event != nullptr){
                event(convertSDLEventtoG2DEvent(e));
            }
        }

        // Logic game loop
        if (loop != nullptr){
            loop(framei);
        }

        // Render
        SDL_RenderClear(_renderer);
        render();
        SDL_RenderPresent(_renderer);

        // FPS count
        frame++;
        framei++;
        Uint32 current_tick = SDL_GetTicks();
        if (current_tick > tick+1000){
            tick = current_tick;
            _real_fps = frame;

            frame = 0;
        }
    }
}