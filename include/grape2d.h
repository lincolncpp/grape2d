#ifndef GRAPE2D_H
#define GRAPE2D_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>

// Windows support to args
#ifdef _WIN32
    #ifndef _vscprintf
        int _vscprintf_so(const char * format, va_list pargs);
    #endif
    #ifndef vasprintf
        int vasprintf(char **strp, const char *fmt, va_list ap);
    #endif
#endif

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

// G2D Keyboard Keys
enum G2D_Keycode{
    G2D_KEYCODE_0                  = SDLK_0,
    G2D_KEYCODE_1                  = SDLK_1,
    G2D_KEYCODE_2                  = SDLK_2,
    G2D_KEYCODE_3                  = SDLK_3,
    G2D_KEYCODE_4                  = SDLK_4,
    G2D_KEYCODE_5                  = SDLK_5,
    G2D_KEYCODE_6                  = SDLK_6,
    G2D_KEYCODE_7                  = SDLK_7,
    G2D_KEYCODE_8                  = SDLK_8,
    G2D_KEYCODE_9                  = SDLK_9,
    G2D_KEYCODE_A                  = SDLK_a,
    G2D_KEYCODE_AC_BACK            = SDLK_AC_BACK,
    G2D_KEYCODE_AC_BOOKMARKS       = SDLK_AC_BOOKMARKS,
    G2D_KEYCODE_AC_FORWARD         = SDLK_AC_FORWARD,
    G2D_KEYCODE_AC_HOME            = SDLK_AC_HOME,
    G2D_KEYCODE_AC_REFRESH         = SDLK_AC_REFRESH,
    G2D_KEYCODE_AC_SEARCH          = SDLK_AC_SEARCH,
    G2D_KEYCODE_AC_STOP            = SDLK_AC_STOP,
    G2D_KEYCODE_AGAIN              = SDLK_AGAIN,
    G2D_KEYCODE_ALTERASE           = SDLK_ALTERASE,
    G2D_KEYCODE_QUOTE              = SDLK_QUOTE,
    G2D_KEYCODE_APPLICATION        = SDLK_APPLICATION,
    G2D_KEYCODE_AUDIOMUTE          = SDLK_AUDIOMUTE,
    G2D_KEYCODE_AUDIONEXT          = SDLK_AUDIONEXT,
    G2D_KEYCODE_AUDIOPLAY          = SDLK_AUDIOPLAY,
    G2D_KEYCODE_AUDIOPREV          = SDLK_AUDIOPREV,
    G2D_KEYCODE_AUDIOSTOP          = SDLK_AUDIOSTOP,
    G2D_KEYCODE_B                  = SDLK_b,
    G2D_KEYCODE_BACKSLASH          = SDLK_BACKSLASH,
    G2D_KEYCODE_BACKSPACE          = SDLK_BACKSPACE,
    G2D_KEYCODE_BRIGHTNESSDOWN     = SDLK_BRIGHTNESSDOWN,
    G2D_KEYCODE_BRIGHTNESSUP       = SDLK_BRIGHTNESSUP,
    G2D_KEYCODE_C                  = SDLK_c,
    G2D_KEYCODE_CALCULATOR         = SDLK_CALCULATOR,
    G2D_KEYCODE_CANCEL             = SDLK_CANCEL,
    G2D_KEYCODE_CAPSLOCK           = SDLK_CAPSLOCK,
    G2D_KEYCODE_CLEAR              = SDLK_CLEAR,
    G2D_KEYCODE_CLEARAGAIN         = SDLK_CLEARAGAIN,
    G2D_KEYCODE_COMMA              = SDLK_COMMA,
    G2D_KEYCODE_COMPUTER           = SDLK_COMPUTER,
    G2D_KEYCODE_COPY               = SDLK_COPY,
    G2D_KEYCODE_CRSEL              = SDLK_CRSEL,
    G2D_KEYCODE_CURRENCYSUBUNIT    = SDLK_CURRENCYSUBUNIT,
    G2D_KEYCODE_CURRENCYUNIT       = SDLK_CURRENCYUNIT,
    G2D_KEYCODE_CUT                = SDLK_CUT,
    G2D_KEYCODE_D                  = SDLK_d,
    G2D_KEYCODE_DECIMALSEPARATOR   = SDLK_DECIMALSEPARATOR,
    G2D_KEYCODE_DELETE             = SDLK_DELETE,
    G2D_KEYCODE_DISPLAYSWITCH      = SDLK_DISPLAYSWITCH,
    G2D_KEYCODE_DOWN               = SDLK_DOWN,
    G2D_KEYCODE_E                  = SDLK_e,
    G2D_KEYCODE_EJECT              = SDLK_EJECT,
    G2D_KEYCODE_END                = SDLK_END,
    G2D_KEYCODE_EQUALS             = SDLK_EQUALS,
    G2D_KEYCODE_ESCAPE             = SDLK_ESCAPE,
    G2D_KEYCODE_EXECUTE            = SDLK_EXECUTE,
    G2D_KEYCODE_EXSEL              = SDLK_EXSEL,
    G2D_KEYCODE_F                  = SDLK_f,
    G2D_KEYCODE_F1                 = SDLK_F1,
    G2D_KEYCODE_F10                = SDLK_F10,
    G2D_KEYCODE_F11                = SDLK_F11,
    G2D_KEYCODE_F12                = SDLK_F12,
    G2D_KEYCODE_F13                = SDLK_F13,
    G2D_KEYCODE_F14                = SDLK_F14,
    G2D_KEYCODE_F15                = SDLK_F15,
    G2D_KEYCODE_F16                = SDLK_F16,
    G2D_KEYCODE_F17                = SDLK_F17,
    G2D_KEYCODE_F18                = SDLK_F18,
    G2D_KEYCODE_F19                = SDLK_F19,
    G2D_KEYCODE_F2                 = SDLK_F2,
    G2D_KEYCODE_F20                = SDLK_F20,
    G2D_KEYCODE_F21                = SDLK_F21,
    G2D_KEYCODE_F22                = SDLK_F22,
    G2D_KEYCODE_F23                = SDLK_F23,
    G2D_KEYCODE_F24                = SDLK_F24,
    G2D_KEYCODE_F3                 = SDLK_F3,
    G2D_KEYCODE_F4                 = SDLK_F4,
    G2D_KEYCODE_F5                 = SDLK_F5,
    G2D_KEYCODE_F6                 = SDLK_F6,
    G2D_KEYCODE_F7                 = SDLK_F7,
    G2D_KEYCODE_F8                 = SDLK_F8,
    G2D_KEYCODE_F9                 = SDLK_F9,
    G2D_KEYCODE_FIND               = SDLK_FIND,
    G2D_KEYCODE_G                  = SDLK_g,
    G2D_KEYCODE_BACKQUOTE          = SDLK_BACKQUOTE,
    G2D_KEYCODE_H                  = SDLK_h,
    G2D_KEYCODE_HELP               = SDLK_HELP,
    G2D_KEYCODE_HOME               = SDLK_HOME,
    G2D_KEYCODE_I                  = SDLK_i,
    G2D_KEYCODE_INSERT             = SDLK_INSERT,
    G2D_KEYCODE_J                  = SDLK_j,
    G2D_KEYCODE_K                  = SDLK_k,
    G2D_KEYCODE_KBDILLUMDOWN       = SDLK_KBDILLUMDOWN,
    G2D_KEYCODE_KBDILLUMTOGGLE     = SDLK_KBDILLUMTOGGLE,
    G2D_KEYCODE_KBDILLUMUP         = SDLK_KBDILLUMUP,
    G2D_KEYCODE_KP_0               = SDLK_KP_0,
    G2D_KEYCODE_KP_00              = SDLK_KP_00,
    G2D_KEYCODE_KP_000             = SDLK_KP_000,
    G2D_KEYCODE_KP_1               = SDLK_KP_1,
    G2D_KEYCODE_KP_2               = SDLK_KP_2,
    G2D_KEYCODE_KP_3               = SDLK_KP_3,
    G2D_KEYCODE_KP_4               = SDLK_KP_4,
    G2D_KEYCODE_KP_5               = SDLK_KP_5,
    G2D_KEYCODE_KP_6               = SDLK_KP_6,
    G2D_KEYCODE_KP_7               = SDLK_KP_7,
    G2D_KEYCODE_KP_8               = SDLK_KP_8,
    G2D_KEYCODE_KP_9               = SDLK_KP_9,
    G2D_KEYCODE_KP_A               = SDLK_KP_A,
    G2D_KEYCODE_KP_AMPERSAND       = SDLK_KP_AMPERSAND,
    G2D_KEYCODE_KP_AT              = SDLK_KP_AT,
    G2D_KEYCODE_KP_B               = SDLK_KP_B,
    G2D_KEYCODE_KP_BACKSPACE       = SDLK_KP_BACKSPACE,
    G2D_KEYCODE_KP_BINARY          = SDLK_KP_BINARY,
    G2D_KEYCODE_KP_C               = SDLK_KP_C,
    G2D_KEYCODE_KP_CLEAR           = SDLK_KP_CLEAR,
    G2D_KEYCODE_KP_CLEARENTRY      = SDLK_KP_CLEARENTRY,
    G2D_KEYCODE_KP_COLON           = SDLK_KP_COLON,
    G2D_KEYCODE_KP_COMMA           = SDLK_KP_COMMA,
    G2D_KEYCODE_KP_D               = SDLK_KP_D,
    G2D_KEYCODE_KP_DBLAMPERSAND    = SDLK_KP_DBLAMPERSAND,
    G2D_KEYCODE_KP_DBLVERTICALBAR  = SDLK_KP_DBLVERTICALBAR,
    G2D_KEYCODE_KP_DECIMAL         = SDLK_KP_DECIMAL,
    G2D_KEYCODE_KP_DIVIDE          = SDLK_KP_DIVIDE,
    G2D_KEYCODE_KP_E               = SDLK_KP_E,
    G2D_KEYCODE_KP_ENTER           = SDLK_KP_ENTER,
    G2D_KEYCODE_KP_EQUALS          = SDLK_KP_EQUALS,
    G2D_KEYCODE_KP_EQUALSAS400     = SDLK_KP_EQUALSAS400,
    G2D_KEYCODE_KP_EXCLAM          = SDLK_KP_EXCLAM,
    G2D_KEYCODE_KP_F               = SDLK_KP_F,
    G2D_KEYCODE_KP_GREATER         = SDLK_KP_GREATER,
    G2D_KEYCODE_KP_HASH            = SDLK_KP_HASH,
    G2D_KEYCODE_KP_HEXADECIMAL     = SDLK_KP_HEXADECIMAL,
    G2D_KEYCODE_KP_LEFTBRACE       = SDLK_KP_LEFTBRACE,
    G2D_KEYCODE_KP_LEFTPAREN       = SDLK_KP_LEFTPAREN,
    G2D_KEYCODE_KP_LESS            = SDLK_KP_LESS,
    G2D_KEYCODE_KP_MEMADD          = SDLK_KP_MEMADD,
    G2D_KEYCODE_KP_MEMCLEAR        = SDLK_KP_MEMCLEAR,
    G2D_KEYCODE_KP_MEMDIVIDE       = SDLK_KP_MEMDIVIDE,
    G2D_KEYCODE_KP_MEMMULTIPLY     = SDLK_KP_MEMMULTIPLY,
    G2D_KEYCODE_KP_MEMRECALL       = SDLK_KP_MEMRECALL,
    G2D_KEYCODE_KP_MEMSTORE        = SDLK_KP_MEMSTORE,
    G2D_KEYCODE_KP_MEMSUBTRACT     = SDLK_KP_MEMSUBTRACT,
    G2D_KEYCODE_KP_MINUS           = SDLK_KP_MINUS,
    G2D_KEYCODE_KP_MULTIPLY        = SDLK_KP_MULTIPLY,
    G2D_KEYCODE_KP_OCTAL           = SDLK_KP_OCTAL,
    G2D_KEYCODE_KP_PERCENT         = SDLK_KP_PERCENT,
    G2D_KEYCODE_KP_PERIOD          = SDLK_KP_PERIOD,
    G2D_KEYCODE_KP_PLUS            = SDLK_KP_PLUS,
    G2D_KEYCODE_KP_PLUSMINUS       = SDLK_KP_PLUSMINUS,
    G2D_KEYCODE_KP_POWER           = SDLK_KP_POWER,
    G2D_KEYCODE_KP_RIGHTBRACE      = SDLK_KP_RIGHTBRACE,
    G2D_KEYCODE_KP_RIGHTPAREN      = SDLK_KP_RIGHTPAREN,
    G2D_KEYCODE_KP_SPACE           = SDLK_KP_SPACE,
    G2D_KEYCODE_KP_TAB             = SDLK_KP_TAB,
    G2D_KEYCODE_KP_VERTICALBAR     = SDLK_KP_VERTICALBAR,
    G2D_KEYCODE_KP_XOR             = SDLK_KP_XOR,
    G2D_KEYCODE_L                  = SDLK_l,
    G2D_KEYCODE_LALT               = SDLK_LALT,
    G2D_KEYCODE_LCTRL              = SDLK_LCTRL,
    G2D_KEYCODE_LEFT               = SDLK_LEFT,
    G2D_KEYCODE_LEFTBRACKET        = SDLK_LEFTBRACKET,
    G2D_KEYCODE_LGUI               = SDLK_LGUI,
    G2D_KEYCODE_LSHIFT             = SDLK_LSHIFT,
    G2D_KEYCODE_M                  = SDLK_m,
    G2D_KEYCODE_MAIL               = SDLK_MAIL,
    G2D_KEYCODE_MEDIASELECT        = SDLK_MEDIASELECT,
    G2D_KEYCODE_MENU               = SDLK_MENU,
    G2D_KEYCODE_MINUS              = SDLK_MINUS,
    G2D_KEYCODE_MODE               = SDLK_MODE,
    G2D_KEYCODE_MUTE               = SDLK_MUTE,
    G2D_KEYCODE_N                  = SDLK_n,
    G2D_KEYCODE_NUMLOCKCLEAR       = SDLK_NUMLOCKCLEAR,
    G2D_KEYCODE_O                  = SDLK_o,
    G2D_KEYCODE_OPER               = SDLK_OPER,
    G2D_KEYCODE_OUT                = SDLK_OUT,
    G2D_KEYCODE_P                  = SDLK_p,
    G2D_KEYCODE_PAGEDOWN           = SDLK_PAGEDOWN,
    G2D_KEYCODE_PAGEUP             = SDLK_PAGEUP,
    G2D_KEYCODE_PASTE              = SDLK_PASTE,
    G2D_KEYCODE_PAUSE              = SDLK_PAUSE,
    G2D_KEYCODE_PERIOD             = SDLK_PERIOD,
    G2D_KEYCODE_POWER              = SDLK_POWER,
    G2D_KEYCODE_PRINTSCREEN        = SDLK_PRINTSCREEN,
    G2D_KEYCODE_PRIOR              = SDLK_PRIOR,
    G2D_KEYCODE_Q                  = SDLK_q,
    G2D_KEYCODE_R                  = SDLK_r,
    G2D_KEYCODE_RALT               = SDLK_RALT,
    G2D_KEYCODE_RCTRL              = SDLK_RCTRL,
    G2D_KEYCODE_RETURN             = SDLK_RETURN,
    G2D_KEYCODE_RETURN2            = SDLK_RETURN2,
    G2D_KEYCODE_RGUI               = SDLK_RGUI,
    G2D_KEYCODE_RIGHT              = SDLK_RIGHT,
    G2D_KEYCODE_RIGHTBRACKET       = SDLK_RIGHTBRACKET,
    G2D_KEYCODE_RSHIFT             = SDLK_RSHIFT,
    G2D_KEYCODE_S                  = SDLK_s,
    G2D_KEYCODE_SCROLLLOCK         = SDLK_SCROLLLOCK,
    G2D_KEYCODE_SELECT             = SDLK_SELECT,
    G2D_KEYCODE_SEMICOLON          = SDLK_SEMICOLON,
    G2D_KEYCODE_SEPARATOR          = SDLK_SEPARATOR,
    G2D_KEYCODE_SLASH              = SDLK_SLASH,
    G2D_KEYCODE_SLEEP              = SDLK_SLEEP,
    G2D_KEYCODE_SPACE              = SDLK_SPACE,
    G2D_KEYCODE_STOP               = SDLK_STOP,
    G2D_KEYCODE_SYSREQ             = SDLK_SYSREQ,
    G2D_KEYCODE_T                  = SDLK_t,
    G2D_KEYCODE_TAB                = SDLK_TAB,
    G2D_KEYCODE_THOUSANDSSEPARATOR = SDLK_THOUSANDSSEPARATOR,
    G2D_KEYCODE_U                  = SDLK_u,
    G2D_KEYCODE_UNDO               = SDLK_UNDO,
    G2D_KEYCODE_UNKNOWN            = SDLK_UNKNOWN,
    G2D_KEYCODE_UP                 = SDLK_UP,
    G2D_KEYCODE_V                  = SDLK_v,
    G2D_KEYCODE_VOLUMEDOWN         = SDLK_VOLUMEDOWN,
    G2D_KEYCODE_VOLUMEUP           = SDLK_VOLUMEUP,
    G2D_KEYCODE_W                  = SDLK_w,
    G2D_KEYCODE_WWW                = SDLK_WWW,
    G2D_KEYCODE_X                  = SDLK_x,
    G2D_KEYCODE_Y                  = SDLK_y,
    G2D_KEYCODE_Z                  = SDLK_z,
    G2D_KEYCODE_AMPERSAND          = SDLK_AMPERSAND,
    G2D_KEYCODE_ASTERISK           = SDLK_ASTERISK,
    G2D_KEYCODE_AT                 = SDLK_AT,
    G2D_KEYCODE_CARET              = SDLK_CARET,
    G2D_KEYCODE_COLON              = SDLK_COLON,
    G2D_KEYCODE_DOLLAR             = SDLK_DOLLAR,
    G2D_KEYCODE_EXCLAIM            = SDLK_EXCLAIM,
    G2D_KEYCODE_GREATER            = SDLK_GREATER,
    G2D_KEYCODE_HASH               = SDLK_HASH,
    G2D_KEYCODE_LEFTPAREN          = SDLK_LEFTPAREN,
    G2D_KEYCODE_LESS               = SDLK_LESS,
    G2D_KEYCODE_PERCENT            = SDLK_PERCENT,
    G2D_KEYCODE_PLUS               = SDLK_PLUS,
    G2D_KEYCODE_QUESTION           = SDLK_QUESTION,
    G2D_KEYCODE_QUOTEDBL           = SDLK_QUOTEDBL,
    G2D_KEYCODE_RIGHTPAREN         = SDLK_RIGHTPAREN,
    G2D_KEYCODE_UNDERSCORE         = SDLK_UNDERSCORE
};

enum G2D_MOUSEBUTTON{
    G2D_MOUSEBUTTON_LEFT,
    G2D_MOUSEBUTTON_RIGHT,
    G2D_MOUSEBUTTON_MIDDLE
};

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
enum G2D_EventType{
    G2D_EVENTTYPE_NULL,
    G2D_EVENTTYPE_MOUSEDOWN,
    G2D_EVENTTYPE_MOUSEUP,
    G2D_EVENTTYPE_MOUSEMOVE,
    G2D_EVENTTYPE_MOUSEWHEEL,
    G2D_EVENTTYPE_KEYDOWN,
    G2D_EVENTTYPE_KEYUP
};

struct G2D_Event{
    G2D_EventType type = G2D_EVENTTYPE_NULL;
    struct G2D_MouseEvent{
        int x;
        int y;
        int x_rel;
        int y_rel;
        G2D_MOUSEBUTTON button;

        Sint8 wheel;
    } mouse = {};
    struct G2D_KeyboardEvent{
        G2D_Keycode keycode;
    } key = {};
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

    public:
        G2D_Camera();

        void setCenterPosition(int x, int y);
        void setCenterPosition(G2D_Point point);
        void setCenterX(int x);
        void setCenterY(int y);
        int getCenterX();
        int getCenterY();

        int getCornerX();
        int getCornerY();

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
    G2D_Event createG2D_Event(SDL_Event e);

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
    void _render(bool absolute, int x, int y, G2D_Rect *clip = nullptr, double angle = 0, G2D_Point *center = nullptr, bool flip_horizontal = false, bool flip_vertical = false);

public:
    G2D_Texture(const char *path);
    ~G2D_Texture();

    void free();

    void setColor(G2D_Color color);
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(G2D_BlendMode blendMode);
    void setAlpha(Uint8 alpha);

    void render(int x, int y, G2D_Rect *clip = nullptr, double angle = 0, G2D_Point *center = nullptr, bool flip_horizontal = false, bool flip_vertical = false);
    void renderHUD(int x, int y, G2D_Rect *clip = nullptr, double angle = 0, G2D_Point *center = nullptr, bool flip_horizontal = false, bool flip_vertical = false);

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
    void renderHUD(int x, int y);
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
