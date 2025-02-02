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
static cell Native_RedisSetInteger(AMX *amx, cell *params)
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

// native redis_get_string(const key[], value[], maxlength);
static cell Native_RedisGetString(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);

	if (g_redis != NULL)
	{
		OptionalString value = g_redis->get(key);
		const char *result = convertToCString(value);
		MF_SetAmxString(amx, params[2], result, params[3]);
	}
	else
		return -1;

	return 0;
}

// native redis_get_integer(const key[], value);
static cell Native_RedisGetInteger(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);
	int iResult = 0;
	if (g_redis != NULL)
	{
		OptionalString value = g_redis->get(key);
		std::string result = value.value();
		try
		{
			iResult = std::stoi(result);
		}
		catch (const Error &e)
		{
			iResult = 0;
			return 0;
		}
	}
	else
		return 0;

	return iResult;
}

// native redis_del_key(const key[]);
static cell Native_RedisDeleteKey(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);

	if (g_redis != NULL)
		g_redis->del(key);
	else
		return -1;

	return 0;
}

// native redis_hset_string(const key[], const field[], const value[]);
static cell Native_RedisHSetString(AMX *amx, cell *params)
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
static cell Native_RedisHSetInteger(AMX *amx, cell *params)
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

// native redis_hget_string(const key[], const field[], value[], maxlength);
static cell Native_RedisHGetString(AMX *amx, cell *params)
{
	int len = 0;
	std::string key   = MF_GetAmxString(amx, params[1], 0, &len);
	std::string field = MF_GetAmxString(amx, params[2], 1, &len);

	if (g_redis != NULL)
	{
		OptionalString value = g_redis->hget(key, field);
		const char *result = convertToCString(value);
		MF_SetAmxString(amx, params[3], result, params[4]);
	}
	else
		return -1;

	return 0;
}

// native redis_hget_string(const key[], const field[], value);
static cell Native_RedisHGetInteger(AMX *amx, cell *params)
{
	int len = 0;
	std::string key = MF_GetAmxString(amx, params[1], 0, &len);
	std::string field = MF_GetAmxString(amx, params[2], 1, &len);
	int iResult = 0;
	if (g_redis != NULL)
	{
		OptionalString value = g_redis->hget(key, field);
		std::string result = value.value();
		try
		{
			iResult = std::stoi(result);
		}
		catch (const Error &e)
		{
			iResult = 0;
			return 0;
		}
	}
	else
		return 0;

	return iResult;
}

// native redis_hdel_field(const key[], const field[]);
static cell Native_RedisHDeleteField(AMX *amx, cell *params)
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
