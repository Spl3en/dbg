#pragma once

// ---------- Includes ------------
#include <stdio.h>
#include "Utils/Utils.h"

// ---------- Defines -------------
#if __DBG_ACTIVATED__ == TRUE
    #ifdef __DEBUG_OBJECT__
        #define dbg(format, ...)                                                                        \
            do {                                                                                        \
                char __time_buffer__[20] = {0};                                                         \
                get_now_buffer(__time_buffer__);                                                        \
                _dbg("[%s][%20s:%30s] " format "\n",                                                    \
                    __time_buffer__,                                                                    \
                    __DEBUG_OBJECT__,                                                                   \
                    __FUNCTION__,                                                                       \
                    ##__VA_ARGS__);                                                                     \
            } while (0);
    #else
        #define dbg(format, ...)                                                                        \
            do {                                                                                        \
                char __time_buffer__[20] = {0};                                                         \
                get_now_buffer(__time_buffer__);                                                        \
                _dbg("[%s][%20s:%30s] " format "\n",                                                    \
                        __time_buffer__,                                                                \
                        ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__, \
                        __FUNCTION__,                                                                   \
                        ##__VA_ARGS__);                                                                 \
            } while (0);
    #endif

    #ifdef __DEBUG_OBJECT__
        #define fail(format, ...)                                                                       \
            do {                                                                                        \
                char __time_buffer__[20] = {0};                                                         \
                get_now_buffer(__time_buffer__);                                                        \
                _fail("[%s][%20s:%30s] [FAIL] " format "\n",                                            \
                        __time_buffer__,                                                                \
                        __DEBUG_OBJECT__,                                                               \
                        __FUNCTION__,                                                                   \
                        ##__VA_ARGS__);                                                                 \
            } while (0);
    #else
        #define fail(format, ...)                                                                       \
            do {                                                                                        \
                char __time_buffer__[20] = {0};                                                         \
                get_now_buffer(__time_buffer__);                                                        \
            _fail("[%s][%20s:%30s] [FAIL] " format "\n",                                                \
                    __time_buffer__,                                                                    \
                    ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__,     \
                    __FUNCTION__,                                                                       \
                    ##__VA_ARGS__);                                                                     \
            } while (0);
    #endif

    #ifdef __DEBUG_OBJECT__
        #define warn(format, ...)                                                                       \
            do {                                                                                        \
                char __time_buffer__[20] = {0};                                                         \
                get_now_buffer(__time_buffer__);                                                        \
            _warn("[%s][%20s:%30s] [WARN] " format "\n",                                                \
                    __time_buffer__,                                                                    \
                    __DEBUG_OBJECT__,                                                                   \
                    __FUNCTION__,                                                                       \
                    ##__VA_ARGS__);                                                                     \
            } while (0);
    #else
        #define warn(format, ...)                                                                       \
            do {                                                                                        \
                char __time_buffer__[20] = {0};                                                         \
                get_now_buffer(__time_buffer__);                                                        \
            _warn("[%s][%20s:%30s] [WARN] " format "\n",                                                \
                    __time_buffer__,                                                                    \
                    ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__,     \
                    __FUNCTION__,                                                                       \
                    ##__VA_ARGS__);                                                                     \
            } while (0);
    #endif
#else
	#define dbg(format, ...)
	#define fail(format, ...)
	#define warn(format, ...)
#endif

void _dbg  (char *format, ...);
void _fail (char *format, ...);
void _warn (char *format, ...);

void dbg_set_output (FILE *output);

// ----------- Methods ------------
