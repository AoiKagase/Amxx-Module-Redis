#include "amxxsdk/amxxmodule.h"

bool UTIL_CheckForPublic(const char* publicname)
{
	AMX* amx;
	int iFunctionIndex;
	int i = 0;
	char blah[64];

	strncpy(blah, publicname, sizeof(blah));
	blah[63] = '\0';

	while ((amx = MF_GetScriptAmx(i++)))
	{
		if (MF_AmxFindPublic(amx, blah, &iFunctionIndex) == AMX_ERR_NONE)
		{
			MF_Log("[REDIS:DEBUG] Found public '%s' in script '%s'.", publicname, MF_GetScriptName(MF_FindScriptByAmx(amx)));
			return true;
		}
	}

	return false;
}