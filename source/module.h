#ifndef MODULE_H
#define MODULE_H

#include "amxxsdk/amxxmodule.h"
#include "sw/redis++/redis++.h"

using namespace sw::redis;

extern AMX_NATIVE_INFO g_natives[];
extern Redis *g_redis;

#endif // MODULE_H
