#include "module.h"

using namespace sw::redis;

Redis* g_redis = NULL;
ConnectionOptions g_connection_options;

const char* convertToCString(const OptionalString& optStr) {
    if (optStr) {
        return optStr->c_str();
    } else {
        return nullptr;
    }
}
// native redis_connect(const hostip[], const port, const username[] = "", const password[] = "");
static cell	Native_RedisConnect(AMX *amx, cell *params)
{
	MF_Log("Redis Connect.");

	int len = 0;
	// HOST IP.
	g_connection_options.host = MF_GetAmxString(amx, params[1], 0, &len);
	// PORT
	g_connection_options.port = params[2];

	std::string username = MF_GetAmxString(amx, params[3], 1, &len);

	if (len > 0) 
	{
		// USERNAME
		g_connection_options.user = username;
		// PASSWORD
		g_connection_options.password = MF_GetAmxString(amx, params[4], 2, &len);
	}

	try 
    {
        g_redis = new Redis(g_connection_options);
    } catch (const Error &e) {
		MF_LogError(amx, AMX_ERR_NATIVE, "Redis Connecting Error.");
        return -1;
    }
    return 0;
}

// native redis_set_string(const key[], const value[]);
static cell Native_RedisSetString(AMX *amx, cell *params)
{
	MF_Log("Redis Set String.");

	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);
	std::string value = MF_GetAmxString(amx, params[2], 1, &len);

	if (g_redis != NULL)
		g_redis->set(key, value);
	else
		return -1;

	return 0;
}

// native redis_get_string(const key[], value[], maxlength);
static cell Native_RedisGetString(AMX *amx, cell *params)
{
	MF_Log("Redis Get String");
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);

	if (g_redis != NULL)
	{
		OptionalString value = g_redis->get(key);
		const char* result = convertToCString(value);
		MF_SetAmxString(amx, params[2], result, params[3]);
	}
	else
		return -1;

	return 0;
}

AMX_NATIVE_INFO g_natives[] =
	{
		{"redis_connect", Native_RedisConnect},
		{"redis_set_string", Native_RedisSetString},
		{"redis_get_string", Native_RedisGetString},

		{nullptr, nullptr}
};
