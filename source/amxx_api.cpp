#include "module.h"

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
	isSubsriverRunning = false;
	channels->clear();
	g_redis->bgsave();
	delete g_redis;
}

