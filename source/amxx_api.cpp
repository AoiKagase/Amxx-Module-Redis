#include "module.h"

void OnAmxxAttach()
{
    MF_AddNatives(g_natives);
}

void OnPluginsLoaded()
{
}

void OnPluginsUnloaded()
{
	g_redis->bgsave();
	delete g_redis;
}

