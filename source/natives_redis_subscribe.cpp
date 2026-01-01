#include "module.h"

using namespace sw::redis;

std::vector<std::string> channels;
std::thread *th_subscriber = NULL;

// native redis_subscribe(const channel[]);
cell redis_register_subscriber(AMX *amx, cell *params)
{
	if (!HasRedisOnMessage)
		return -1;

	int len = 0;
	std::string channel = MF_GetAmxString(amx, params[1], 0, &len);

	channels.clear();
	if (g_redis != NULL)
	{
		channels.push_back(channel);
	}
	else
		return -1;

	return 0;
}

void consumeThread()
{
	isSubsriberRunning = true;
	try
	{
		while (isSubsriberRunning)
		{
			sub->consume();
		}
	}
	catch (const Error& err)
	{
		LOG_CONSOLE(PLID, "[DEBUG] SUBSCRIBE ERROR: %s", err.what());
	}
}

// native redis_start_subscribe();
cell redis_start_subscribe(AMX* amx, cell* params)
{
	MF_Log("[DEBUG] START SUBSCRIBE FUNCTION.");

	if (!HasRedisOnMessage) {
		MF_Log("[DEBUG] NOT EXISTS FORWARD. EXIT.");
		return -1;
	}

	for (auto& ch : channels) {
		sub->subscribe(ch);
	}

	MF_Log("[DEBUG] SUBSCRIBE CHANNELS.");

	th_subscriber = new std::thread(consumeThread);
	MF_Log("[DEBUG] CREATED THREAD.");

	MF_Log("[DEBUG] END SUBSCRIBE FUNCTION.");
	return 0;
}

