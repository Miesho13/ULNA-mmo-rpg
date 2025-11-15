#include "../platform/platform.h"

// TODO(): for test perpous
#define RAYLIB_LINUX

#ifdef RAYLIB_LINUX
#   include "../platform/platform_raylib_linux.c"
#else
#   error "PLATFORM DONT SPECYFIE"
#endif
