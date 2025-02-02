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
}

