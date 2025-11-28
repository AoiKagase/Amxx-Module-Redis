#include "module.h"

using namespace sw::redis;

// native redis_subscribe(const channel[], const message[]);
//cell redis_subscribe(AMX *amx, cell *params)
//{
//	int len = 0;
//	std::string channel   = MF_GetAmxString(amx, params[1], 0, &len);
//	std::string message	  = MF_GetAmxString(amx, params[2], 1, &len);
//
//	if (g_redis != NULL)
//		g_redis->subscribe(channel, message);
//	else
//		return -1;
//
//	return 0;
//}
