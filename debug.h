#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef _WIN32
    #ifdef DEBUG_EXPORTING
        #define DEBUG_API __declspec(dllexport)
    #elif !defined(DEBUG_STATIC)
        #define DEBUG_API __declscpec(dllimport)
    #else
        #define DEBUG_API
    #endif /* DEBUG_EXPORTING */
#else
    #define DEBUG_API
#endif /* _WIN32 */

#ifdef __sun
#  include <sys/varargs.h>
#endif /* __sun */

typedef struct debug_context_s debug_context_t;

DEBUG_API debug_context_t* debug_create_context(const char* name);
DEBUG_API void debug(const debug_context_t* context, const char* format, ...);
DEBUG_API void vdebug(const debug_context_t* context, const char* format, va_list ap);

#define CREATE_DEBUG_CTX(ctx_name)                                  \
static debug_context_t* ctx_name ##_debug_ctx = NULL;               \
                                                                    \
static void ctx_name ## _create_dbg_ctx(void)                       \
{                                                                   \
    if (!ctx_name ## _debug_ctx)                                    \
    {                                                               \
        ctx_name ## _debug_ctx = debug_create_context(#ctx_name);   \
    }                                                               \
}                                                                   \
                                                                    \
static void ctx_name ## _debug(const char* format, ...)             \
{                                                                   \
    va_list argp;                                                   \
                                                                    \
    ctx_name ## _create_dbg_ctx();                                  \
                                                                    \
    va_start(argp, format);                                         \
    vdebug(ctx_name ## _debug_ctx, format, argp);                   \
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DEBUG_H_ */
