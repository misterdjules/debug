#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <stdio.h>

#include "debug.h"

struct debug_context_s
{
    const char* name;
    int         enabled;
};

DEBUG_API debug_context_t* debug_create_context(const char* name)
{
    debug_context_t* new_debug_context = NULL;
    const char* debug_env              = NULL;

    new_debug_context = malloc(sizeof(debug_context_t));
    if (!new_debug_context)
        return NULL;

    if (name)
        new_debug_context->name = strdup(name);
    else
        new_debug_context->name = NULL;

    new_debug_context->enabled = 0;
    debug_env = getenv("DEBUG");
    if (debug_env && !strcmp(name, debug_env))
    {
        new_debug_context->enabled = 1;
    }

    return new_debug_context;
}

DEBUG_API void debug(const debug_context_t* context,
                     const char* format,
                     ...)
{
    va_list argp;

    va_start(argp, format);
    vdebug(context, format, argp);
    va_end(argp);
}

DEBUG_API void vdebug(const debug_context_t* context, const char* format, va_list ap)
{
    assert(context);
    assert(format);

    if (!context || !format)
        return;

    if (context && !context->enabled)
        return;

    fprintf(stderr, "[%s] ", context->name);
    vfprintf(stderr, format, ap);
}