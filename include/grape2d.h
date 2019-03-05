#ifndef GRAPE2D_H
#define GRAPE2D_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

#define G2D_MIN_CHANNEL 2
#define G2D_MAX_CHANNEL 10000

#define G2D_DEFAULT_AUDIBLE_RADIUS 1000

#define PI 3.14159265

class G2D_Engine;
class G2D_Texture;
class G2D_Font;
class G2D_Text;
class G2D_Music;
class G2D_Sound;


// G2D Color struct
struct G2D_Color{
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = 255;
};

// G2D Rect struct
struct G2D_Rect{
    int x;
    int y;
    int w;
    int h;
};

// G2D Point struct
struct G2D_Point{
    int x;
    int y;
};

// G2D BlendMode struct
enum G2D_BlendMode{
    G2D_BLENDMODE_NONE,
    G2D_BLENDMODE_BLEND,
    G2D_BLENDMODE_ADD,
    G2D_BLENDMODE_MOD
};

// G2D Event struct
enum G2D_MouseState{
    G2D_MOUSEDOWN,
    G2D_MOUSEUP,
    G2D_MOUSEMOVE
};
struct G2D_Event{
    G2D_MouseState mouse_state;
    int mouse_x;
    int mouse_y;

    const Uint8* key_state;
};

class G2D_Engine{
    friend class G2D_Texture;
    friend class G2D_Sound;
    friend class G2D_Music;
    friend class G2D_Text;
    friend class G2D_Font;

private:
    static G2D_Engine *instance;

    // Mixer
    class G2D_Mixer{
    public:
        void setChannelVolume(int volume, int channel = -1);
        int getChannelVolume(int channel = -1);

        void setMaxChannels(int num_channels);

        void resumeChannel(int channel = -1);
        void pauseChannel(int channel = -1);
        void endChannel(int channel);
        void endChannelTimed(int channel, int time_ms);
        void endChannelFadeOut(int channel, int time_ms);


        void setPlanning(int channel, Uint8 left, Uint8 right);
        void setDistance(int channel, Uint8 distance);
        void setPosition(int channel, Sint16 angle, Uint8 distance);
        void removeEffects(int channel);
    };

    // Camera
    class G2D_Camera{
        friend class G2D_Texture;

    private:
        int _x, _y = 0;

        int getDrawXAdd();
        int getDrawYAdd();

    public:
        G2D_Camera();

        void setPosition(int x, int y);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();

    };

    // Audio effect
    class G2D_Audio{
        friend class G2D_Engine;
        friend class G2D_Sound;

    private:
        int _audible_radius = G2D_DEFAULT_AUDIBLE_RADIUS;

        G2D_Sound *_sound[G2D_MAX_CHANNEL] = {};

        void add(G2D_Sound *sound, int channel);
        void update();

    public:
        void setAudibleRadius(int radius);
        int getAudibleRadius();
    };

    // Engine
    SDL_Renderer* _renderer = nullptr;

    // Window
    SDL_Window* _window = nullptr;
    int _window_width;
    int _window_height;

    // FPS
    int _real_fps = 0;

    // Error
    bool _debug = false;
    std::string _error = "";
    bool _has_error = false;
    void setError(const char *text, ...);

    // SDL_Event to G2D_Event
    G2D_Event convertSDLEventtoG2DEvent(SDL_Event e);

public:
    G2D_Mixer *mixer = nullptr;
    G2D_Camera *camera = nullptr;
    G2D_Audio *audio = nullptr;

    G2D_Engine(int width, int height, const char *title, bool debug = false, Uint32 SDL_flags = SDL_RENDERER_ACCELERATED);
    ~G2D_Engine();

    bool hasError();
    const char* getError();

    int getWindowWidth();
    int getWindowHeight();

    int getFPS();

    void start(void (*event)(G2D_Event), void (*loop)(Uint32), void (*render)());
};


class G2D_Texture{
    friend class G2D_Text;
    friend class G2D_Engine;

private:
    SDL_Texture *_texture = nullptr;

    int _src_width;
    int _width;
    int _src_height;
    int _height;

    G2D_Texture(G2D_Font *font, const char *text, G2D_Color color);

public:
    G2D_Texture(const char *path);
    ~G2D_Texture();

    void free();

    void setColor(G2D_Color color);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(G2D_BlendMode blendMode);
    void setAlpha(Uint8 alpha);

    void render(int x, int y, G2D_Rect *clip = nullptr, double angle = 0, G2D_Point *center = nullptr, bool flip_horizontal = false, bool flip_vertical = false);

    void setSize(int width, int height);
    int getSrcWidth();
    int getWidth();
    int getSrcHeight();
    int getHeight();
};

class G2D_Font{
    friend class G2D_Texture;
    friend class G2D_Engine;

private:
    TTF_Font *_font = nullptr;
    std::string _path;
    int _size;

    bool loadFont(const char *path, int size);

public:
    G2D_Font(const char *path, int size);
    ~G2D_Font();

    void free();

    void setSize(int size);
};

class G2D_Text{
    friend class G2D_Engine;

private:
    G2D_Font *_font = nullptr;
    G2D_Texture *_texture = nullptr;

    std::string _text;
    G2D_Color _color;

    void reloadTexture();

public:
    G2D_Text(G2D_Font *font, const char *text, ...);
    ~G2D_Text();

    void setColor(G2D_Color color);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setAlpha(Uint8 alpha);
    void setText(const char *text, ...);
    void setFont(G2D_Font *font);


    void render(int x, int y);
};

class G2D_Music{
    friend class G2D_Engine;

private:
    static G2D_Music *_playing_now;
    Mix_Music *_music = nullptr;

    int _volume = 100;

    void updateVolume();

public:
    G2D_Music(const char *path);
    ~G2D_Music();

    int play(bool looping = true);
    int playFadeIn(bool looping = true, int effect_time_ms = 1000);

    void rewind();

    void resume();
    void pause();
    void stop();
    void stopFadeOut(int effect_time_ms = 1000);

    void setVolume(int volume);
    int getVolume();


    void free();
};

class G2D_Sound{
    friend class G2D_Engine;

private:
    Mix_Chunk *_sound = nullptr;
    int _channel = -1;

    int _x, _y = 0;
    bool _2d_effect;

public:
    G2D_Sound(const char *path);
    ~G2D_Sound();

    void setChannel(int channel);
    int getChannel();

    int play(int repeat_times = 0, int limit_ms = -1);

    void setPosition(int x, int y);
    void setPosition(G2D_Point point);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

    void disable2DEffect();

    void setVolume(int volume);
    int getVolume();

    void free();

};


#endif