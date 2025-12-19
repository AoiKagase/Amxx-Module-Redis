#include "amxxmodule.h"
#include <amtl/am-algorithm.h>
#include <amtl/am-string.h>

bool UTIL_CheckForPublic(const char* publicname)
{
	AMX* amx;
	int iFunctionIndex;
	int i = 0;
	char blah[64];

	ke::SafeStrcpy(blah, sizeof(blah), publicname);

	while ((amx = MF_GetScriptAmx(i++)))
	{
		if (MF_AmxFindPublic(amx, blah, &iFunctionIndex) == AMX_ERR_NONE)
		{
			return true;
		}
	}

	return false;
}