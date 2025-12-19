#include "module.h"

using namespace sw::redis;

std::vector<StringView> channels;
std::thread *th_subscriber = NULL;
bool isSubsriverRunning = false;
int HasRedisOnMessage = -1;

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
		channels.push_back(channel.c_str());
	}
	else
		return -1;

	return 0;
}

void consumeThread()
{
	auto sub = g_redis->subscriber();
	isSubsriberRunning = true;
	while (true)
	{
		if (!isSubsriberRunning)
			break;

		try
		{
			sub.consume();
		}
		catch (const Error& err)
		{
		}
	}
}

// native redis_start_subscribe();
cell redis_start_subscribe(AMX* amx, cell* params)
{
	if (!HasRedisOnMessage)
		return -1;

	auto sub = g_redis->subscriber();

	for (size_t i = 0; i < channels.size(); i++) {
		sub.subscribe(channels[i]);
	}

	th_subscriber = new std::thread(consumeThread);
	th_subscriber->join();

	return 0;
}

