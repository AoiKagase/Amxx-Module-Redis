#include "module.h"

using namespace sw::redis;

// native redis_set_string(const key[], const value[]);
cell redis_set_string(AMX *amx, cell *params)
{
	int len = 0;
	std::string key   = MF_GetAmxString(amx, params[1], 0, &len);
	std::string value = MF_GetAmxString(amx, params[2], 1, &len);

	if (g_redis != NULL)
		g_redis->set(key, value);
	else
		return -1;

	return 0;
}

// native redis_set_integer(const key[], const value[]);
cell redis_set_integer(AMX *amx, cell *params)
{
	int len = 0;
	std::string key   = MF_GetAmxString(amx, params[1], 0, &len);
	int value = params[2];

	if (g_redis != NULL)
		g_redis->set(key, std::to_string(value));
	else
		return -1;

	return 0;
}
