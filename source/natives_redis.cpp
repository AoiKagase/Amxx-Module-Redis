#include "module.h"

using namespace sw::redis;

Redis* g_redis = NULL;
ConnectionOptions g_connection_options;
Subscriber sub;
int ForwardRedisOnMessage = -1;
int HasRedisOnMessage = -1;

const char* convertToCString(const OptionalString& optStr) {
    if (optStr) {
        return optStr->c_str();
    } else {
        return nullptr;
    }
}

// native redis_connect(const hostip[], const port, const username[] = "", const password[] = "");
cell redis_connect(AMX *amx, cell *params)
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

		if (HasRedisOnMessage) 
		{
			sub = g_redis->subscriber();

			// Set callback functions.
			sub.on_message([](std::string channel, std::string msg) {
				// Process message of MESSAGE type.
				MF_ExecuteForward(ForwardRedisOnMessage, channel, msg);
			});
		}

    } catch (const Error &e) {
		MF_LogError(amx, AMX_ERR_NATIVE, "Redis Connecting Error.");
        return -1;
    }
    return 0;
}
