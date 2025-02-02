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

	server_print("REDIS TEST RESULT = [%s]", result);
	return PLUGIN_HANDLED_MAIN;
}