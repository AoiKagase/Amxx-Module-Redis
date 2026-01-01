#ifndef MODULE_H
#define MODULE_H

#include "amxxsdk/amxxmodule.h"
#include "sw/redis++/redis++.h"

#define DEBUG_LOGGING 0

using namespace sw::redis;

extern AMX_NATIVE_INFO g_natives[];
extern Redis* g_redis;
extern Redis* g_subscriber_redis;
extern bool isSubscriberRunning;

extern int ForwardRedisOnMessage;
extern int HasRedisOnMessage;

extern std::vector<std::string> channels;
extern std::thread* th_subscriber;
extern sw::redis::Subscriber* sub;

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

extern cell redis_publish(AMX* amx, cell* params);

extern cell redis_register_subscriber(AMX* amx, cell* params);
extern cell redis_start_subscribe(AMX* amx, cell* params);

extern bool UTIL_CheckForPublic(const char* publicname);

#endif // MODULE_H
