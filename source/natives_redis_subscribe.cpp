#include "module.h"

using namespace sw::redis;

Subscriber sub;

std::vector<string> *channels = NULL;
std::thread *th_subscriber = NULL;
bool isSubsriverRunning = false;

// native redis_subscribe(const channel[]);
cell redis_register_subscriber(AMX *amx, cell *params)
{
	int len = 0;
	std::string channel = MF_GetAmxString(amx, params[1], 0, &len);

	if (g_redis != NULL)
	{
		if (channels == NULL) {
			channels = new std::vector<string>();
		}
		channels.push_back(channel);
	}
	else
		return -1;

	return 0;
}

// native redis_start_subscribe();
cell redis_start_subscribe(AMX* amx, cell* params)
{
	isSubsriverRunning = true;
	sub.subscribe(channels);

	th_subscriber = new std::thread(
		while (true)
		{
			if (!isSubsriverRunning)
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