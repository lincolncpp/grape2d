#ifndef GRAPE2D_H
#define GRAPE2D_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <vector>
#include <set>

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

#define G2D_DEFAULT_MAX_SOUND_DISTANCE 1000

#define G2D_PI 3.14159265

namespace G2D {

    class Engine;
    class Texture;
    class Font;
    class Text;
    class Music;
    class Sound;
    class Layer;
    class Sprite;
    class Timer;

    // G2D Keyboard Keys
    enum Keycode {
        KEY_0 = SDLK_0,
        KEY_1 = SDLK_1,
        KEY_2 = SDLK_2,
        KEY_3 = SDLK_3,
        KEY_4 = SDLK_4,
        KEY_5 = SDLK_5,
        KEY_6 = SDLK_6,
        KEY_7 = SDLK_7,
        KEY_8 = SDLK_8,
        KEY_9 = SDLK_9,
        KEY_A = SDLK_a,
        KEY_AC_BACK = SDLK_AC_BACK,
        KEY_AC_BOOKMARKS = SDLK_AC_BOOKMARKS,
        KEY_AC_FORWARD = SDLK_AC_FORWARD,
        KEY_AC_HOME = SDLK_AC_HOME,
        KEY_AC_REFRESH = SDLK_AC_REFRESH,
        KEY_AC_SEARCH = SDLK_AC_SEARCH,
        KEY_AC_STOP = SDLK_AC_STOP,
        KEY_AGAIN = SDLK_AGAIN,
        KEY_ALTERASE = SDLK_ALTERASE,
        KEY_QUOTE = SDLK_QUOTE,
        KEY_APPLICATION = SDLK_APPLICATION,
        KEY_AUDIOMUTE = SDLK_AUDIOMUTE,
        KEY_AUDIONEXT = SDLK_AUDIONEXT,
        KEY_AUDIOPLAY = SDLK_AUDIOPLAY,
        KEY_AUDIOPREV = SDLK_AUDIOPREV,
        KEY_AUDIOSTOP = SDLK_AUDIOSTOP,
        KEY_B = SDLK_b,
        KEY_BACKSLASH = SDLK_BACKSLASH,
        KEY_BACKSPACE = SDLK_BACKSPACE,
        KEY_BRIGHTNESSDOWN = SDLK_BRIGHTNESSDOWN,
        KEY_BRIGHTNESSUP = SDLK_BRIGHTNESSUP,
        KEY_C = SDLK_c,
        KEY_CALCULATOR = SDLK_CALCULATOR,
        KEY_CANCEL = SDLK_CANCEL,
        KEY_CAPSLOCK = SDLK_CAPSLOCK,
        KEY_CLEAR = SDLK_CLEAR,
        KEY_CLEARAGAIN = SDLK_CLEARAGAIN,
        KEY_COMMA = SDLK_COMMA,
        KEY_COMPUTER = SDLK_COMPUTER,
        KEY_COPY = SDLK_COPY,
        KEY_CRSEL = SDLK_CRSEL,
        KEY_CURRENCYSUBUNIT = SDLK_CURRENCYSUBUNIT,
        KEY_CURRENCYUNIT = SDLK_CURRENCYUNIT,
        KEY_CUT = SDLK_CUT,
        KEY_D = SDLK_d,
        KEY_DECIMALSEPARATOR = SDLK_DECIMALSEPARATOR,
        KEY_DELETE = SDLK_DELETE,
        KEY_DISPLAYSWITCH = SDLK_DISPLAYSWITCH,
        KEY_DOWN = SDLK_DOWN,
        KEY_E = SDLK_e,
        KEY_EJECT = SDLK_EJECT,
        KEY_END = SDLK_END,
        KEY_EQUALS = SDLK_EQUALS,
        KEY_ESCAPE = SDLK_ESCAPE,
        KEY_EXECUTE = SDLK_EXECUTE,
        KEY_EXSEL = SDLK_EXSEL,
        KEY_F = SDLK_f,
        KEY_F1 = SDLK_F1,
        KEY_F10 = SDLK_F10,
        KEY_F11 = SDLK_F11,
        KEY_F12 = SDLK_F12,
        KEY_F13 = SDLK_F13,
        KEY_F14 = SDLK_F14,
        KEY_F15 = SDLK_F15,
        KEY_F16 = SDLK_F16,
        KEY_F17 = SDLK_F17,
        KEY_F18 = SDLK_F18,
        KEY_F19 = SDLK_F19,
        KEY_F2 = SDLK_F2,
        KEY_F20 = SDLK_F20,
        KEY_F21 = SDLK_F21,
        KEY_F22 = SDLK_F22,
        KEY_F23 = SDLK_F23,
        KEY_F24 = SDLK_F24,
        KEY_F3 = SDLK_F3,
        KEY_F4 = SDLK_F4,
        KEY_F5 = SDLK_F5,
        KEY_F6 = SDLK_F6,
        KEY_F7 = SDLK_F7,
        KEY_F8 = SDLK_F8,
        KEY_F9 = SDLK_F9,
        KEY_FIND = SDLK_FIND,
        KEY_G = SDLK_g,
        KEY_BACKQUOTE = SDLK_BACKQUOTE,
        KEY_H = SDLK_h,
        KEY_HELP = SDLK_HELP,
        KEY_HOME = SDLK_HOME,
        KEY_I = SDLK_i,
        KEY_INSERT = SDLK_INSERT,
        KEY_J = SDLK_j,
        KEY_K = SDLK_k,
        KEY_KBDILLUMDOWN = SDLK_KBDILLUMDOWN,
        KEY_KBDILLUMTOGGLE = SDLK_KBDILLUMTOGGLE,
        KEY_KBDILLUMUP = SDLK_KBDILLUMUP,
        KEY_KP_0 = SDLK_KP_0,
        KEY_KP_00 = SDLK_KP_00,
        KEY_KP_000 = SDLK_KP_000,
        KEY_KP_1 = SDLK_KP_1,
        KEY_KP_2 = SDLK_KP_2,
        KEY_KP_3 = SDLK_KP_3,
        KEY_KP_4 = SDLK_KP_4,
        KEY_KP_5 = SDLK_KP_5,
        KEY_KP_6 = SDLK_KP_6,
        KEY_KP_7 = SDLK_KP_7,
        KEY_KP_8 = SDLK_KP_8,
        KEY_KP_9 = SDLK_KP_9,
        KEY_KP_A = SDLK_KP_A,
        KEY_KP_AMPERSAND = SDLK_KP_AMPERSAND,
        KEY_KP_AT = SDLK_KP_AT,
        KEY_KP_B = SDLK_KP_B,
        KEY_KP_BACKSPACE = SDLK_KP_BACKSPACE,
        KEY_KP_BINARY = SDLK_KP_BINARY,
        KEY_KP_C = SDLK_KP_C,
        KEY_KP_CLEAR = SDLK_KP_CLEAR,
        KEY_KP_CLEARENTRY = SDLK_KP_CLEARENTRY,
        KEY_KP_COLON = SDLK_KP_COLON,
        KEY_KP_COMMA = SDLK_KP_COMMA,
        KEY_KP_D = SDLK_KP_D,
        KEY_KP_DBLAMPERSAND = SDLK_KP_DBLAMPERSAND,
        KEY_KP_DBLVERTICALBAR = SDLK_KP_DBLVERTICALBAR,
        KEY_KP_DECIMAL = SDLK_KP_DECIMAL,
        KEY_KP_DIVIDE = SDLK_KP_DIVIDE,
        KEY_KP_E = SDLK_KP_E,
        KEY_KP_ENTER = SDLK_KP_ENTER,
        KEY_KP_EQUALS = SDLK_KP_EQUALS,
        KEY_KP_EQUALSAS400 = SDLK_KP_EQUALSAS400,
        KEY_KP_EXCLAM = SDLK_KP_EXCLAM,
        KEY_KP_F = SDLK_KP_F,
        KEY_KP_GREATER = SDLK_KP_GREATER,
        KEY_KP_HASH = SDLK_KP_HASH,
        KEY_KP_HEXADECIMAL = SDLK_KP_HEXADECIMAL,
        KEY_KP_LEFTBRACE = SDLK_KP_LEFTBRACE,
        KEY_KP_LEFTPAREN = SDLK_KP_LEFTPAREN,
        KEY_KP_LESS = SDLK_KP_LESS,
        KEY_KP_MEMADD = SDLK_KP_MEMADD,
        KEY_KP_MEMCLEAR = SDLK_KP_MEMCLEAR,
        KEY_KP_MEMDIVIDE = SDLK_KP_MEMDIVIDE,
        KEY_KP_MEMMULTIPLY = SDLK_KP_MEMMULTIPLY,
        KEY_KP_MEMRECALL = SDLK_KP_MEMRECALL,
        KEY_KP_MEMSTORE = SDLK_KP_MEMSTORE,
        KEY_KP_MEMSUBTRACT = SDLK_KP_MEMSUBTRACT,
        KEY_KP_MINUS = SDLK_KP_MINUS,
        KEY_KP_MULTIPLY = SDLK_KP_MULTIPLY,
        KEY_KP_OCTAL = SDLK_KP_OCTAL,
        KEY_KP_PERCENT = SDLK_KP_PERCENT,
        KEY_KP_PERIOD = SDLK_KP_PERIOD,
        KEY_KP_PLUS = SDLK_KP_PLUS,
        KEY_KP_PLUSMINUS = SDLK_KP_PLUSMINUS,
        KEY_KP_POWER = SDLK_KP_POWER,
        KEY_KP_RIGHTBRACE = SDLK_KP_RIGHTBRACE,
        KEY_KP_RIGHTPAREN = SDLK_KP_RIGHTPAREN,
        KEY_KP_SPACE = SDLK_KP_SPACE,
        KEY_KP_TAB = SDLK_KP_TAB,
        KEY_KP_VERTICALBAR = SDLK_KP_VERTICALBAR,
        KEY_KP_XOR = SDLK_KP_XOR,
        KEY_L = SDLK_l,
        KEY_LALT = SDLK_LALT,
        KEY_LCTRL = SDLK_LCTRL,
        KEY_LEFT = SDLK_LEFT,
        KEY_LEFTBRACKET = SDLK_LEFTBRACKET,
        KEY_LGUI = SDLK_LGUI,
        KEY_LSHIFT = SDLK_LSHIFT,
        KEY_M = SDLK_m,
        KEY_MAIL = SDLK_MAIL,
        KEY_MEDIASELECT = SDLK_MEDIASELECT,
        KEY_MENU = SDLK_MENU,
        KEY_MINUS = SDLK_MINUS,
        KEY_MODE = SDLK_MODE,
        KEY_MUTE = SDLK_MUTE,
        KEY_N = SDLK_n,
        KEY_NUMLOCKCLEAR = SDLK_NUMLOCKCLEAR,
        KEY_O = SDLK_o,
        KEY_OPER = SDLK_OPER,
        KEY_OUT = SDLK_OUT,
        KEY_P = SDLK_p,
        KEY_PAGEDOWN = SDLK_PAGEDOWN,
        KEY_PAGEUP = SDLK_PAGEUP,
        KEY_PASTE = SDLK_PASTE,
        KEY_PAUSE = SDLK_PAUSE,
        KEY_PERIOD = SDLK_PERIOD,
        KEY_POWER = SDLK_POWER,
        KEY_PRINTSCREEN = SDLK_PRINTSCREEN,
        KEY_PRIOR = SDLK_PRIOR,
        KEY_Q = SDLK_q,
        KEY_R = SDLK_r,
        KEY_RALT = SDLK_RALT,
        KEY_RCTRL = SDLK_RCTRL,
        KEY_RETURN = SDLK_RETURN,
        KEY_RETURN2 = SDLK_RETURN2,
        KEY_RGUI = SDLK_RGUI,
        KEY_RIGHT = SDLK_RIGHT,
        KEY_RIGHTBRACKET = SDLK_RIGHTBRACKET,
        KEY_RSHIFT = SDLK_RSHIFT,
        KEY_S = SDLK_s,
        KEY_SCROLLLOCK = SDLK_SCROLLLOCK,
        KEY_SELECT = SDLK_SELECT,
        KEY_SEMICOLON = SDLK_SEMICOLON,
        KEY_SEPARATOR = SDLK_SEPARATOR,
        KEY_SLASH = SDLK_SLASH,
        KEY_SLEEP = SDLK_SLEEP,
        KEY_SPACE = SDLK_SPACE,
        KEY_STOP = SDLK_STOP,
        KEY_SYSREQ = SDLK_SYSREQ,
        KEY_T = SDLK_t,
        KEY_TAB = SDLK_TAB,
        KEY_THOUSANDSSEPARATOR = SDLK_THOUSANDSSEPARATOR,
        KEY_U = SDLK_u,
        KEY_UNDO = SDLK_UNDO,
        KEY_UNKNOWN = SDLK_UNKNOWN,
        KEY_UP = SDLK_UP,
        KEY_V = SDLK_v,
        KEY_VOLUMEDOWN = SDLK_VOLUMEDOWN,
        KEY_VOLUMEUP = SDLK_VOLUMEUP,
        KEY_W = SDLK_w,
        KEY_WWW = SDLK_WWW,
        KEY_X = SDLK_x,
        KEY_Y = SDLK_y,
        KEY_Z = SDLK_z,
        KEY_AMPERSAND = SDLK_AMPERSAND,
        KEY_ASTERISK = SDLK_ASTERISK,
        KEY_AT = SDLK_AT,
        KEY_CARET = SDLK_CARET,
        KEY_COLON = SDLK_COLON,
        KEY_DOLLAR = SDLK_DOLLAR,
        KEY_EXCLAIM = SDLK_EXCLAIM,
        KEY_GREATER = SDLK_GREATER,
        KEY_HASH = SDLK_HASH,
        KEY_LEFTPAREN = SDLK_LEFTPAREN,
        KEY_LESS = SDLK_LESS,
        KEY_PERCENT = SDLK_PERCENT,
        KEY_PLUS = SDLK_PLUS,
        KEY_QUESTION = SDLK_QUESTION,
        KEY_QUOTEDBL = SDLK_QUOTEDBL,
        KEY_RIGHTPAREN = SDLK_RIGHTPAREN,
        KEY_UNDERSCORE = SDLK_UNDERSCORE
    };

    enum MouseButton {
        MB_LEFT,
        MB_RIGHT,
        MB_MIDDLE
    };

    enum BlendMode {
        BM_NONE,
        BM_BLEND,
        BM_ADD,
        BM_MOD
    };

    enum EventType {
        ET_NULL,
        ET_MOUSEDOWN,
        ET_MOUSEUP,
        ET_MOUSEMOVE,
        ET_MOUSEWHEEL,
        ET_KEYDOWN,
        ET_KEYUP
    };

    enum Referential {
        R_ABSOLUTE,
        R_RELATIVE,
    };

    // G2D Color struct
    struct Color {
        int r = 0;
        int g = 0;
        int b = 0;
        int a = 255;
    };

    // G2D Rect struct
    struct Rect {
        int x;
        int y;
        int w;
        int h;
    };

    // G2D Point struct
    struct Point {
        int x;
        int y;
    };

    // G2D Event struct
    struct Event {
        EventType type = ET_NULL;

        struct MouseEvent {
            int x;
            int y;
            int x_rel;
            int y_rel;
            MouseButton button;

            int wheel;
        } mouse = {};

        struct KeyboardEvent {
            Keycode key;
        } keyboard = {};
    };

    class Engine {
        friend class Texture;
        friend class Sound;
        friend class Music;
        friend class Text;
        friend class Font;
        friend class Layer;
        friend class Timer;

    private:
        static Engine *instance;

        // Mixer
        class Mixer {
            friend class Engine;
            friend class Sound;
            friend class Music;

        private:
            Music *_playing_music = nullptr;
            int _max_sound_distance = G2D_DEFAULT_MAX_SOUND_DISTANCE;
            Sound *_sound[G2D_MAX_CHANNEL] = {};

            void add(Sound *sound, int channel);
            void update();

        public:
            void setChannelVolume(int volume, int channel = -1);
            int getChannelVolume(int channel = -1);
            void setMaxChannels(int num_channels);
            void resumeChannel(int channel = -1);
            void pauseChannel(int channel = -1);
            void endChannel(int channel);
            void endChannelTimed(int channel, int time_ms);
            void endChannelFadeOut(int channel, int time_ms);
            void setPlanning(int channel, int left, int right);
            void setDistance(int channel, int distance);
            void setPosition(int channel, int angle, int distance);
            void removeEffects(int channel);
            Music *getPlayingMusic();
            void setMaxSoundDistance(int radius);
            int getMaxSoundDistance();
        };

        // Camera
        class Camera {
            friend class Texture;

        private:
            Point _position;

        public:
            Camera();
            void setCenterPosition(int x, int y);
            void setCenterPosition(Point point);
            void setCenterX(int x);
            void setCenterY(int y);
            int getCenterX();
            int getCenterY();
            int getCornerX();
            int getCornerY();
        };

        // Engine
        SDL_Renderer *_renderer = nullptr;

        // Window
        SDL_Window *_window = nullptr;
        int _window_width;
        int _window_height;

        // FPS
        int _real_fps = 0;

        // Layers
        std::vector<Layer*> _layers = {};

        // Timers
        std::vector<Timer*> _timers = {};

        // Debug
        bool _debug = false;
        std::string _error = "";
        bool _has_error = false;
        void setError(const char *text, ...);

        // Intern functions
        Event convertEvent(SDL_Event e);
        void updateLayerZIndex();

    public:
        Mixer *mixer = nullptr;
        Camera *camera = nullptr;

        Engine(int width, int height, const char *title, bool debug = false,
                   int SDL_flags = SDL_RENDERER_ACCELERATED);
        ~Engine();

        bool hasError();
        const char *getError();

        int getWindowWidth();
        int getWindowHeight();
        int getFPS();

        void attachLayer(Layer *layer);

        void run();
    };


    class Texture {
        friend class Text;
        friend class Engine;
        friend class Sprite;

    private:
        SDL_Texture *_texture = nullptr;

        int _src_width;
        int _width;
        int _src_height;
        int _height;

        Referential _referential = R_ABSOLUTE;

        // Special constructor for Text class
        Texture(Font *font, const char *text, Color color);

    public:
        Texture(const char *path);
        ~Texture();
        void free();

        void setColor(Color color);
        void setColor(int red, int green, int blue);
        void setBlendMode(BlendMode blendMode);
        void setAlpha(int alpha);
        void setReferential(Referential referential);
        void render(int x, int y, Rect *clip = nullptr, double angle = 0, Point *center = nullptr,
                    bool flip_horizontal = false, bool flip_vertical = false);
        void setSize(int width, int height);

        int getSrcWidth();
        int getWidth();
        int getSrcHeight();
        int getHeight();
    };

    class Font {
        friend class Texture;
        friend class Engine;

    private:
        TTF_Font *_font = nullptr;
        std::string _path;
        int _size;

        bool loadFont(const char *path, int size);

    public:
        Font(const char *path, int size);
        ~Font();
        void free();

        void setSize(int size);
    };

    class Text {
        friend class Engine;

    private:
        Font *_font = nullptr;
        Texture *_texture = nullptr;

        std::string _text;
        Color _color;

        Referential _referential;

        void reloadTexture();

    public:
        Text(Font *font, const char *text, ...);
        ~Text();

        void setColor(Color color);
        void setColor(int red, int green, int blue);
        void setAlpha(int alpha);
        void setText(const char *text, ...);
        void setFont(Font *font);
        void setReferential(Referential referential);
        void render(int x, int y);
    };

    class Music {
        friend class Engine;

    private:
        Mix_Music *_music = nullptr;

        int _volume = 100;

        void updateVolume();

    public:
        Music(const char *path);
        ~Music();
        void free();

        int play(bool looping = true);
        int playFadeIn(bool looping = true, int time = 1000);
        void rewind();
        void resume();
        void pause();
        void stop();
        void stopFadeOut(int time = 1000);
        void setVolume(int volume);
        int getVolume();
    };

    class Sound {
        friend class Engine;

    private:
        Mix_Chunk *_sound = nullptr;
        int _channel = -1;

        Point _position = {};
        bool _2d_effect;

    public:
        Sound(const char *path);
        ~Sound();
        void free();

        void setChannel(int channel);
        int getChannel();
        int play(int repeat = 0, int time = 0);
        void setPosition(int x, int y);
        void setPosition(Point point);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        void disable2DEffect();
        void setVolume(int volume);
        int getVolume();
    };

    class Layer {
        friend class Engine;
        friend class Sprite;

    private:
        bool _visible = true;
        int _z = 0;

        std::set<std::pair<int, Sprite*>> _elements = {};

        void render();
        void update(int frame);

        struct Callback {
            friend class Engine;

        private:
            void (*onRenderFunction)() = nullptr;
            void (*onUpdateFunction)() = nullptr;
            void (*onEventFunction)(Event) = nullptr;

        public:
            void onRender(void (*function)());
            void onUpdate(void (*function)());
            void onEvent(void (*function)(Event));
        };

    public:
        Layer();
        ~Layer();

        Callback callback = {};

        void setZ(int value);
        int getZ();
        void attach(Sprite *sprite);
        void hide();
        void show();
    };

    class Sprite {
        friend class Layer;

    private:
        Texture *_texture = nullptr;

        Point _position = {};
        int _z = 0;

        Rect _clip = {};
        int _current_frame = 0;

        // Animate
        int _tick_animate = 0;
        int _time = 0;
        bool _is_animating = false;
        std::vector<int> *_frames = nullptr;

        void construct(int frames_x, int frames_y);
        void update(int tick);

    public:
        Sprite(const char *path, int frames_x = 0, int frames_y = 0);
        Sprite(Texture *texture, int frames_x = 0, int frames_y = 0);
        ~Sprite();

        void setPosition(int x, int y);
        void setPosition(Point point);
        void setX(int x);
        int getX();
        void setY(int y);
        int getY();
        void setReferential(Referential referential);
        void setFrame(int frame);
        int getFrame();
        void animate(std::vector<int> frames, int time, bool force = false);
        void setZ(int value);
        int getZ();
        void render();
        Texture *getTexture();
    };

    class Timer {
    private:
        bool _started = false;
        bool _paused = false;

        int _tick_start = 0;
        int _tick_pause = 0;
        int _limit = 0;

        void (*_callback)() = nullptr;

    public:
        Timer(int limit = 0, void (*callback)() = nullptr);
        ~Timer();

        void update(int engine_tick);
        void start();
        void pause();
        void resume();
        void stop();
        void restart();
        void toggle();
        int getTime();
        bool isPaused();
        bool isStarted();
    };

}

#endif
