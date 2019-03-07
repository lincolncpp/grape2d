#include "../include/grape2d.h"

// Windows support to args
#ifdef _WIN32
    #ifndef _vscprintf
        int _vscprintf_so(const char * format, va_list pargs) {
            int retval;
            va_list argcopy;
            va_copy(argcopy, pargs);
            retval = vsnprintf(NULL, 0, format, argcopy);
            va_end(argcopy);
            return retval;
        }
    #endif
    #ifndef vasprintf
        int vasprintf(char **strp, const char *fmt, va_list ap) {
            int len = _vscprintf_so(fmt, ap);
            if (len == -1) return -1;
            char *str = (char*)malloc((size_t) len + 1);
            if (!str) return -1;
            int r = vsnprintf(str, len + 1, fmt, ap);
            if (r == -1) return free(str), -1;
            *strp = str;
            return r;
        }
    #endif
#endif
