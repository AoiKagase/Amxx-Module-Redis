#include "module.h"

static cell	Native_RedisConnect(AMX *amx, cell *params)     {return redis_connect(amx, params);}

static cell Native_RedisDeleteKey(AMX *amx, cell *params)   {return redis_delete_key(amx, params);}
static cell Native_RedisHDeleteField(AMX *amx, cell *params){return redis_hdelete_field(amx, params);}

static cell Native_RedisGetString(AMX *amx, cell *params)   {return redis_get_string(amx, params);}
static cell Native_RedisGetInteger(AMX *amx, cell *params)  {return redis_get_integer(amx, params);}

static cell Native_RedisSetString(AMX *amx, cell *params)   {return redis_set_string(amx, params);}
static cell Native_RedisSetInteger(AMX *amx, cell *params)  {return redis_set_integer(amx, params);}


static cell Native_RedisHGetString(AMX *amx, cell *params)  {return redis_hget_string(amx, params);}
static cell Native_RedisHGetInteger(AMX *amx, cell *params) {return redis_hget_integer(amx, params);}

static cell Native_RedisHSetString(AMX *amx, cell *params)  {return redis_hset_string(amx, params);}
static cell Native_RedisHSetInteger(AMX *amx, cell *params) {return redis_hset_integer(amx, params);}

AMX_NATIVE_INFO g_natives[] =
{
	{"redis_connect", Native_RedisConnect},
	{"redis_set_string", Native_RedisSetString},
	{"redis_set_integer", Native_RedisSetInteger},
	{"redis_get_string", Native_RedisGetString},
	{"redis_get_integer", Native_RedisGetInteger},
	{"redis_hset_string", Native_RedisHSetString},
	{"redis_hset_integer", Native_RedisHSetInteger},
	{"redis_hget_string", Native_RedisHGetString},
	{"redis_hget_integer", Native_RedisHGetInteger},
	{"redis_del_key", Native_RedisDeleteKey},
	{"redis_hdel_field", Native_RedisHDeleteField},
	{nullptr, nullptr}
};
