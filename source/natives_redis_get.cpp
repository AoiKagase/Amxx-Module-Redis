#include "module.h"

using namespace sw::redis;

// native redis_get_string(const key[], value[], maxlength);
cell redis_get_string(AMX *amx, cell *params)
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
cell redis_get_integer(AMX *amx, cell *params)
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
