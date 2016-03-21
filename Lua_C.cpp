
#include "Lua_C.h"
#include "lua-seri.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <vector>
#include <sys/time.h>
#include "ServiceObj.h"
#include "Socket_Poll.h"
#include "Timer_Queue.h"
int traceback (lua_State *L) {
	if(L == NULL)
		return 0;
  lua_getfield(L, LUA_REGISTRYINDEX, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);  /* pass error message */
  lua_pushinteger(L, 2);  /* skip this function and traceback */
  lua_call(L, 2, 1);  /* call debug.traceback */
  return 1;
}


int _callback(lua_State *L)
{
	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_settop(L, 1);
	lua_rawsetp(L, LUA_REGISTRYINDEX, "callback");

	return 0;
}


int
llisten(lua_State *L)
{
	int port = luaL_checkinteger(L, 1);
	int backlog = luaL_optinteger(L, 2, 48);
	
	lua_getfield(L, LUA_REGISTRYINDEX, "service_handle");
	int handle = lua_tointeger(L,-1);

	int id = do_listen(handle, port, backlog);

	if (id < 0) {
		return luaL_error(L, "Listen error");
	}

	lua_pushinteger(L, id);
	return 1;
}

int
lconnect(lua_State *L) {
	size_t sz = 0;
	const char * addr = luaL_checklstring(L, 1, &sz);
	int port = luaL_checkinteger(L, 2);

	int sock_cli = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);  
	servaddr.sin_addr.s_addr = inet_addr(addr);  
	
	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
	    perror("connect");
	    exit(1);
	}

	connection_st* ptc = (connection_st*)(Allocator_Manager::instance()->malloc(sizeof(connection_st)));
	ptc->sock = sock_cli;
	ptc->rbuf = new Stream_Base(10240);
	ptc->type = T_CONNECT;
	ptc->epfd = sock_cli%EPOLL_NUM;
	lua_getfield(L, LUA_REGISTRYINDEX, "service_handle");
	ptc->service_handle = lua_tointeger(L, -1);

	printf("zone sock_cli %d\n", sock_cli);
	SOCKET_SERVER.slot[sock_cli] = ptc;
	struct epoll_event evReg;
	evReg.events = EPOLLIN | EPOLLONESHOT;
	evReg.data.ptr = ptc;
	epoll_ctl(SOCKET_SERVER.epfd[sock_cli%EPOLL_NUM], EPOLL_CTL_ADD, sock_cli, &evReg);

	lua_pushinteger(L, sock_cli);
	return 1;
}

int
lclose(lua_State *L) {
	int sock_cli = luaL_checkinteger(L, 1);
	closeConnection(sock_cli);
	return 0;
}


int
lsend(lua_State *L) {
	static char* sbuf = NULL;
	int id = luaL_checkinteger(L, 1);

	struct block temp;
	temp.next = NULL;
	struct write_block wb;
	wb_init(&wb, &temp);
	pack_from(L, &wb, 1);
	block* b = &temp;
	int len = wb.len;
	// TODO  分配内存 可优化
	char * buffer = (char*)malloc(len);

	char * ptr = buffer;
	int sz = len;
	while (len > 0)
	{
		if (len >= BLOCK_SIZE)
		{
			memcpy(ptr, b->buffer, BLOCK_SIZE);
			ptr += BLOCK_SIZE;
			len -= BLOCK_SIZE;
			b = b->next;
		}
		else
		{
			memcpy(ptr, b->buffer, len);
			break;
		}
	}

	wb_free(&wb);
	lua_pushinteger(L, sendData(SOCKET_SERVER.slot[id], buffer, len));
	free(buffer);

	return 1;
}

int
lregtimer(lua_State *L)
{
	int secs = luaL_checkinteger(L, 1);
	lua_getfield(L, LUA_REGISTRYINDEX, "service_handle");
	int _handle = lua_tointeger(L, -1);

	Time_Value tv;
	tv.msec(secs);

	lua_pushinteger(L, Timer_Queue::instance()->schedule_timer(_handle, tv));
	return 1;
}

ServiceLua::ServiceLua(const char* path, int port) :m_path(path), m_port(port)
{}
ServiceLua::~ServiceLua()
{}

int lua_openmylib(lua_State *L)
{
	luaL_Reg l[] = {
		{ "unpack", _luaseri_unpack },
		{ "callback", _callback },
		{ "listen", llisten },
		{ "connect", lconnect },
		{ "close", lclose },
		{ "send", lsend },
		{ "schedule_timer", lregtimer },
		
		{ NULL, NULL },
	};
	luaL_newlib(L, l);

	return 1;
};

void ServiceLua::Init(int handle)
{
	ServiceObj::Init(handle);
	L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushinteger(L, handle);
	lua_setfield(L, LUA_REGISTRYINDEX, "service_handle");

	SetGlb();
	luaL_requiref(L, "c_fun", lua_openmylib, 0);
	int status = luaL_dofile(L, m_path);
	
	if (status != 0)
	{
		printf("Lua Error ======================================================\n");
		printf("%s\n", lua_tostring(L, -1));
		printf("========= ======================================================\n");
		return;
	}
}

void ServiceLua::Free()
{}

void ServiceLua::Dispatch(Message& msg)
{
	int trace = 1;
	int r;
	int top = lua_gettop(L);
	
	lua_pushcfunction(L, traceback);
	lua_rawgetp(L, LUA_REGISTRYINDEX, "callback");

	lua_pushinteger(L, msg.getFd());
	lua_pushinteger(L, msg.getType());

	if (msg.getMsg())
	{
		lua_pushlightuserdata(L, (void *)msg.getMsg()->get_base_ptr());
		lua_pushinteger(L, msg.getMsg()->get_readable());
		r = lua_pcall(L, 4, 0, trace);
	}
	else
	{
		r = lua_pcall(L, 2, 0, trace);
	}
	
	if (r != LUA_OK) {
		switch (r) {
		case LUA_ERRRUN:
			break;
		case LUA_ERRMEM:
			break;
		case LUA_ERRERR:
			break;
		case LUA_ERRGCMM:
			break;
		};
	}

	lua_pop(L, 1);
	return;
}


void ServiceLua::SetGlb()
{
	lua_newtable(L);
	lua_pushnumber(L, m_port);
	lua_setfield(L, -2, "port");

	std::map<std::string, std::string> ms = ServiceMgr::instance()->GetServicesMap();
	for (std::map<std::string, std::string>::iterator iter = ms.begin(); iter != ms.end(); ++iter)
	{
		lua_pushstring(L, iter->second.c_str());
		lua_setfield(L, -2, iter->first.c_str());
	}
	

	lua_setglobal(L, "c_global");
}