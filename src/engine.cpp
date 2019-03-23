#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <vector>
#include <algorithm>

#include "../include/grape2d.h"

G2D_Engine *G2D_Engine::instance = nullptr;

G2D_Engine::G2D_Engine(uint16_t width, uint16_t height, const char *title, bool debug, uint32_t SDL_flags) {
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

    delete mixer;
    delete camera;

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

    delete msg;

    if (_debug){
        printf("%s\n", _error.c_str());
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

G2D_Event G2D_Engine::convertEvent(SDL_Event e) {
    G2D_Event e_ = {};

    SDL_GetMouseState(&e_.mouse.x, &e_.mouse.y);
    e_.mouse.x_rel = e_.mouse.x+G2D_Engine::instance->camera->getCornerX();
    e_.mouse.y_rel = e_.mouse.y+G2D_Engine::instance->camera->getCornerY();

    if (e.type == SDL_MOUSEMOTION){
        e_.type = G2D_EVENTTYPE_MOUSEMOVE;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
        e_.type = (e.type == SDL_MOUSEBUTTONDOWN)?G2D_EVENTTYPE_MOUSEDOWN:G2D_EVENTTYPE_MOUSEUP;

        if (e.button.button == SDL_BUTTON_LEFT) e_.mouse.button = G2D_MOUSEBUTTON_LEFT;
        else if (e.button.button == SDL_BUTTON_MIDDLE) e_.mouse.button = G2D_MOUSEBUTTON_MIDDLE;
        else if (e.button.button == SDL_BUTTON_RIGHT) e_.mouse.button = G2D_MOUSEBUTTON_RIGHT;
    }
    else if (e.type == SDL_MOUSEWHEEL){
        e_.type = G2D_EVENTTYPE_MOUSEWHEEL;
        e_.mouse.wheel = (Uint8)e.wheel.y;
    }
    else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
        e_.type = e.type == SDL_KEYDOWN?G2D_EVENTTYPE_KEYDOWN:G2D_EVENTTYPE_KEYUP;

        e_.key.keycode = (G2D_Keycode)e.key.keysym.sym;
    }

    return e_;
}

void G2D_Engine::attachContainer(G2D_Container *container) {
    if (_containers.empty() || find(_containers.begin(), _containers.end(), container) == _containers.end()) {
        _containers.push_back(container);
        updateContainerZIndex();
    }
}


void G2D_Engine::updateContainerZIndex() {
    auto compare = [](const G2D_Container *a, const G2D_Container *b) -> bool{
        return a->_zindex < b->_zindex;
    };
    sort(_containers.begin(), _containers.end(), compare);
}

void G2D_Engine::run() {
    if (_has_error) return;

    bool quit = false;
    SDL_Event e;

    uint32_t fps_tick = SDL_GetTicks();
    uint16_t frame = 0;
    uint32_t main_tick;
    uint32_t frame_total = 0;

    // Main loop
    while (!quit) {
        main_tick = SDL_GetTicks();

        // Sound effect update (Ambient 2D)
        if (frame_total % 20 == 0){
            mixer->update();

            //SDL_Delay(10);
        }

        // Input handle event
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
            }

            for (auto container : _containers){
                if (container->callback.onEventFunction != nullptr){
                    container->callback.onEventFunction(convertEvent(e));
                }
            }
        }


        // Logic game loop
        for (auto container : _containers){
            if (container->_visible){
                if (container->callback.onUpdateFunction != nullptr){
                    container->callback.onUpdateFunction();
                }
                container->update(main_tick);
            }
        }


        // Render
        SDL_RenderClear(_renderer);
        for (auto container : _containers){
            if (container->_visible) {
                if (container->callback.onRenderFunction != nullptr){
                    container->callback.onRenderFunction();
                }
                container->render(); // memory problem here
            }
        }
        SDL_RenderPresent(_renderer);

        // FPS count
        frame++;
        frame_total++;
        if (main_tick > fps_tick+1000){
            fps_tick = main_tick;
            _real_fps = frame;

            frame = 0;
        }
    }
}
