#ifndef ENGINE_UTILS_H_HEADER_GUARD
#define ENGINE_UTILS_H_HEADER_GUARD

#include <stdio.h>
#include "bgfx/bgfx.h"
#include <string.h>
#include <bx/string.h>
#include <bx/timer.h>
#include <bx/math.h>

bgfx::ShaderHandle loadShader(const char* FILENAME);

#endif