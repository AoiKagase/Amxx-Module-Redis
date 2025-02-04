#include "module.h"

using namespace sw::redis;

// native redis_hset_string(const key[], const field[], const value[]);
cell redis_hset_string(AMX *amx, cell *params)
{
	int len = 0;
	std::string key   = MF_GetAmxString(amx, params[1], 0, &len);
	std::string field = MF_GetAmxString(amx, params[2], 1, &len);
	std::string value = MF_GetAmxString(amx, params[3], 2, &len);

	if (g_redis != NULL)
		g_redis->hset(key, field, value);
	else
		return -1;

	return 0;
}

// native redis_hset_integer(const key[], const field[], const value);
cell redis_hset_integer(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);
	std::string field = MF_GetAmxString(amx, params[2], 1, &len);
	int value = params[3];

	if (g_redis != NULL)
		g_redis->hset(key, field, std::to_string(value));
	else
		return -1;

	return 0;
}

