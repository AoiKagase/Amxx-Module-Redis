#include "module.h"
int ForwardRedisOnMessage = -1;
int HasRedisOnMessage = -1;
bool isSubsriberRunning = false;

void OnAmxxAttach()
{
    MF_AddNatives(g_natives);
}

void OnPluginsLoaded()
{
	ForwardRedisOnMessage = MF_RegisterForward("Redis_Subscriber_OnMessage", ET_STOP, FP_STRING, FP_STRING, FP_DONE);
	HasRedisOnMessage = UTIL_CheckForPublic("Redis_Subscriber_OnMessage");
}

void OnPluginsUnloaded()
{
	isSubsriberRunning = false;
	th_subscriber->join();

	channels.clear();
	g_redis->bgsave();
	delete sub;
	delete g_subscriber_redis;
	delete g_redis;
	delete th_subscriber;
}

