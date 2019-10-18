#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <vector>
#include <algorithm>

#include "../include/grape2d.h"

using namespace G2D;

Engine *Engine::instance = nullptr;

Engine::Engine(int width, int height, const char *title, bool debug, int SDL_flags) {
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
                _renderer = SDL_CreateRenderer(_window, -1, (Uint32)SDL_flags);

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
                        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
                            setError("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                        }
                        else{
                            Engine::instance = this;

                            mixer = new Mixer();
                            Mix_AllocateChannels(100);

                            camera = new Camera();
                        }
                    }
                }
            }
        }
    }
}

Engine::~Engine() {
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

bool Engine::hasError() {
    return _has_error;
}

const char* Engine::getError() {
    return _error.c_str();
}

void Engine::setError(const char *text, ...) {
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

int Engine::getWindowWidth() {
    return _window_width;
}

int Engine::getWindowHeight() {
    return _window_height;
}

int Engine::getFPS() {
    return _real_fps;
}

Event Engine::convertEvent(SDL_Event e) {
    Event e_ = {};

    SDL_GetMouseState(&e_.mouse.x, &e_.mouse.y);
    e_.mouse.x_rel = e_.mouse.x+Engine::instance->camera->getCornerX();
    e_.mouse.y_rel = e_.mouse.y+Engine::instance->camera->getCornerY();

    if (e.type == SDL_MOUSEMOTION){
        e_.type = ET_MOUSEMOVE;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
        e_.type = (e.type == SDL_MOUSEBUTTONDOWN)?ET_MOUSEDOWN:ET_MOUSEUP;

        if (e.button.button == SDL_BUTTON_LEFT) e_.mouse.button = MB_LEFT;
        else if (e.button.button == SDL_BUTTON_MIDDLE) e_.mouse.button = MB_MIDDLE;
        else if (e.button.button == SDL_BUTTON_RIGHT) e_.mouse.button = MB_RIGHT;
    }
    else if (e.type == SDL_MOUSEWHEEL){
        e_.type = ET_MOUSEWHEEL;
        e_.mouse.wheel = e.wheel.y;
    }
    else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
        e_.type = e.type == SDL_KEYDOWN?ET_KEYDOWN:ET_KEYUP;

        e_.keyboard.key= (Keycode)e.key.keysym.sym;
    }

    return e_;
}

void Engine::attachLayer(Layer *layer) {
    if (_layers.empty() || find(_layers.begin(), _layers.end(), layer) == _layers.end()) {
        _layers.push_back(layer);
        updateLayerZIndex();
    }
}


void Engine::updateLayerZIndex() {
    auto compare = [](const Layer *a, const Layer *b) -> bool{
        return a->_z < b->_z;
    };
    sort(_layers.begin(), _layers.end(), compare);
}

void Engine::run() {
    if (_has_error) return;

    bool quit = false;
    SDL_Event e;

    int fps_tick = SDL_GetTicks();
    int frame = 0;
    int main_tick;
    int frame_total = 0;

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

            for (auto layer : _layers){
                if (layer->callback.onEventFunction != nullptr){
                    layer->callback.onEventFunction(convertEvent(e));
                }
            }
        }


        // Logic game loop
        for (auto layer : _layers){
            if (layer->_visible){
                if (layer->callback.onUpdateFunction != nullptr){
                    layer->callback.onUpdateFunction();
                }
                layer->update(main_tick);
            }
        }


        // Render
        SDL_RenderClear(_renderer);
        for (auto layer : _layers){
            if (layer->_visible) {
                if (layer->callback.onRenderFunction != nullptr){
                    layer->callback.onRenderFunction();
                }
                layer->render(); // memory problem here
            }
        }
        SDL_RenderPresent(_renderer);

        // Update timers
        for (auto timer : _timers){
            timer->update(main_tick);
        }

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
