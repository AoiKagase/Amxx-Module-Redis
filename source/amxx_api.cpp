#include "module.h"
int ForwardRedisOnMessage = -1;
int HasRedisOnMessage = -1;

void OnAmxxAttach()
{
    MF_AddNatives(g_natives);
}

void OnPluginsLoaded()
{
	ForwardRedisOnMessage = MF_RegisterForward("Redis_Subscriber_OnMessage", ET_STOP, FP_STRING, FP_STRING, FP_DONE);
	HasRedisOnMessage = UTIL_CheckForPublic("Redis_Subscriber_OnMessage");
}

void stop_subscribe()
{
	if (sub) {
		delete sub;
		sub = nullptr;
	}

	if (g_subscriber_redis) {
		delete g_subscriber_redis;
		g_subscriber_redis = nullptr;
	}

	if (th_subscriber && th_subscriber->joinable()) {
		th_subscriber->join();
	}
}

void OnPluginsUnloaded()
{
	stop_subscribe();

	channels.clear();
	g_redis->bgsave();

	delete g_redis;
	g_redis = nullptr;

	delete th_subscriber;
	th_subscriber = nullptr;
}

