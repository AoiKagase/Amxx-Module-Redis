#include "module.h"

using namespace sw::redis;

// native redis_del_key(const key[]);
cell redis_delete_key(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);

	if (g_redis != NULL)
		g_redis->del(key);
	else
		return -1;

	return 0;
}

// native redis_hdel_field(const key[], const field[]);
cell redis_hdelete_field(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);
	std::string field = MF_GetAmxString(amx, params[2], 1, &len);

	if (g_redis != NULL)
		g_redis->hdel(key, field);
	else
		return -1;

	return 0;
}
