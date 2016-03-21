

#ifndef LUA_C
#define LUA_C

#include "ServiceObj.h"
#include "lua.hpp"

extern int traceback(lua_State *L);

static int _callback(lua_State *L);

static int
llisten(lua_State *L);
static int
lconnect(lua_State *L);

static int
lclose(lua_State *L);

static int
lsend(lua_State *L);

static int
lregtimer(lua_State *L);


class ServiceLua : public ServiceObj
{
public:
	ServiceLua(const char* path, int port);
	~ServiceLua();

	void Init(int handle);

	void Free();

	void Dispatch(Message& msg);
	
	void SetGlb();


private:
	lua_State *L;
	const char* m_path;
	int m_port;

};

#endif