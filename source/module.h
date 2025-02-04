#ifndef MODULE_H
#define MODULE_H

#include "amxxsdk/amxxmodule.h"
#include "sw/redis++/redis++.h"

using namespace sw::redis;

extern AMX_NATIVE_INFO g_natives[];
extern Redis *g_redis;

extern const char* convertToCString(const OptionalString& optStr);
extern cell	redis_connect(AMX *amx, cell *params);

extern cell redis_delete_key(AMX *amx, cell *params);
extern cell redis_hdelete_field(AMX *amx, cell *params);

extern cell redis_get_string(AMX *amx, cell *params);
extern cell redis_get_integer(AMX *amx, cell *params);

extern cell redis_set_string(AMX *amx, cell *params);
extern cell redis_set_integer(AMX *amx, cell *params);

extern cell redis_hget_string(AMX *amx, cell *params);
extern cell redis_hget_integer(AMX *amx, cell *params);

extern cell redis_hset_string(AMX *amx, cell *params);
extern cell redis_hset_integer(AMX *amx, cell *params);

#endif // MODULE_H
