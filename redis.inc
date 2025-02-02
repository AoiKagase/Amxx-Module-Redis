#if defined _redis_included
	#endinput
#endif
#define _redis_included

native redis_connect(const hostip[], const port = 6379, const username[] = "", const password[] = "");
native redis_disconnect();

native redis_set_string(const key[], const value[]);

native redis_get_string(const key[], value[], maxlength);

