# AMX MOD X - Redis Client Module
### Description:
> This is a module for amxmodx that allows operations from HLDS to the Redis data store.

---
### Required:
> Data store server application supporting Redis protocol.
```
Redis 
Valkey 
KeyDB 
Microsoft Garnet
```

---
### Building:
> Currently, only Linux is supported. <br>

I use ambuild for builds.

  1. Build the hiredis library that exists in public/hiredis.
  2. Build the redis++ library that exists in public/redis-plus-plus.
  3. execute `python configure.py`.
  4. execute `ambuild obj-linux/`.

> Help me set up a compiling environment for Windows.<br/>
> It also does not support automatic compilation of the external libraries hiredis and redis-plus-plus.<br/>
> I don't think I can implement these.

---
### Usage for plugins:
> This is in its infancy and there are few functions available at this time.

See ![redis.inc](redis.inc) and ![redis_test.sma](redis_test.sma)

---
### A little test:
> I took a simple benchmark using Redis.<br/>
> In one cycle, I did a SET/GET/DEL against a hash table and processed 100,000 cases.<br/>
> The result was 14 seconds, or 0.00014 per cycle.<br/>
> Needless to say, since we ran 100,000 cycles in FOR logic, the CPU usage was 100% during that time.
```C++
server_print("[REDIS] BENCHMARK START");
new start = get_systime();
new iResult = 0;
for (new i = 0; i < 100000; i++)
{
    redis_hset_integer("REDIS_TEST_HASH", "INTEGER", i);
    iResult = redis_hget_integer("REDIS_TEST_HASH", "INTEGER");
    redis_hdel_field("REDIS_TEST_HASH", "INTEGER");
//  server_print("[REDIS] %d", iResult);
}
new bench = get_systime() - start;
server_print("[REDIS] %d", iResult);
server_print("[REDIS] BENCHMARK %d SEC", bench);
```
```
[REDIS] BENCHMARK START
[REDIS] 99999
[REDIS] BENCHMARK 14 SEC
```

---
## I need your help.
- Build environment on Windows.
- Automatic build of external libraries.
- If there is a feature you would like to see, please send a request to Issue.
