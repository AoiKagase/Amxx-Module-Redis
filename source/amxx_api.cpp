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
	ForwardRedisOnMessage = MF_RegisterForward("Redis_OnMessage", ET_STOP, FP_STRING, FP_STRING, FP_DONE);
	HasRedisOnMessage = UTIL_CheckForPublic("Redis_OnMessage");
}

void OnPluginsUnloaded()
{
	isSubsriberRunning = false;
	channels.clear();
	g_redis->bgsave();
	delete g_redis;
	delete th_subscriber;
}

