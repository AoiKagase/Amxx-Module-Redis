#if defined _redis_included
	#endinput
#endif
#define _redis_included

native redis_connect(const hostip[], const port = 6379, const username[] = "", const password[] = "");

native redis_set_string(const key[], const value[]);

native redis_set_integer(const key[], const value);

native redis_get_string(const key[], value[], maxlength);

native redis_get_integer(const key[]);

native redis_hset_string(const key[], const field[], const value[]);

native redis_hset_integer(const key[], const field[], const value);

native redis_hget_string(const key[], const field[], value[], maxlength);

native redis_hget_integer(const key[], const field[]);

native redis_del_key(const key[]);

native redis_hdel_field(const key[], const field[]);
