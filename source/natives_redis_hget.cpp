#include "module.h"

using namespace sw::redis;

// native redis_hget_string(const key[], const field[], value[], maxlength);
cell redis_hget_string(AMX *amx, cell *params)
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
cell redis_hget_integer(AMX *amx, cell *params)
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
