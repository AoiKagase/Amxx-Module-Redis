#include "module.h"

using namespace sw::redis;

Subscriber sub;

std::vector<StringView> *channels = NULL;
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

	if (g_redis != NULL)
	{
		if (channels == NULL) {
			channels = new std::vector<StringView>();
		}
		channels.push_back(channel);
	}
	else
		return -1;

	return 0;
}

// native redis_start_subscribe();
void redis_start_subscribe(AMX* amx, cell* params)
{
	if (!HasRedisOnMessage)
		return;

	isSubsriverRunning = true;
	for (int i = 0; i < channels->size(); i++) {
		sub.subscribe(channels[i]);
	}

	th_subscriber = new std::thread(
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
	);
	th_subscriber->join();
}