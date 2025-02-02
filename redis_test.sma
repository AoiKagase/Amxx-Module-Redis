#include <amxmodx>
#include <redis>

#define PLUGIN					"Redis Test"
#define VERSION					"0.01"
#define AUTHOR					"Aoi.Kagase"

new const HOST_IP[]	=			"127.0.0.1";
new const HOST_PORT	=			6379;

public plugin_init() 
{
	register_plugin(PLUGIN, VERSION, AUTHOR);

	redis_connect(HOST_IP, HOST_PORT);

	new result[32];
	redis_set_string("TEST", "REDIS_123456");
	redis_get_string("TEST", result, charsmax(result));
	redis_del_key("TEST");
	server_print("[REDIS] TEST RESULT = [%s]", result);

	server_print("[REDIS] BENCHMARK START");
	new start = get_systime();
	new iResult = 0;
	for (new i = 0; i < 100000; i++)
	{
		redis_hset_integer("REDIS_TEST_HASH", "INTEGER", i);
		iResult = redis_hget_integer("REDIS_TEST_HASH", "INTEGER");
		redis_hdel_field("REDIS_TEST_HASH", "INTEGER");
//		server_print("[REDIS] %d", iResult);
	}
	new bench = get_systime() - start;
	server_print("[REDIS] %d", iResult);
	server_print("[REDIS] BENCHMARK %d SEC", bench);

	return PLUGIN_HANDLED_MAIN;
}