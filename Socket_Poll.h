#ifndef SOCKET_POLL
#define SOCKET_POLL

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
#include "Allocator_Manager.h"
#include "ServiceObj.h"
#include <sys/time.h>

#define T_ACCEPT 1
#define T_CONNECT 2

#define SOCKET_TYPE_DATA 0
#define SOCKET_TYPE_CONNECT 1
#define SOCKET_TYPE_CLOSE 2
#define SOCKET_TYPE_CTRL 3
#define SOCKET_TYPE_TIMEOUT 4


struct connection_st 
{
    int sock;
	int epfd;
	int type;
	int service_handle;
	bool isclose;
	Stream_Base* rbuf;
	Stream_Base* wbuf;
   
	connection_st()
	{
		memset(this, 0, sizeof(connection_st));
	}

};


#define EPOLL_NUM 6
#define WORKER_PER_GROUP 8

#define NUM_WORKER (EPOLL_NUM * WORKER_PER_GROUP)

static long RecvNums = 0;
static long AllRecv = 0;
static long PerRecv = 0;
static long MaxRecv = 0;
static int CurTimes = 0;

struct socket_server {
	socket_server()
	{
		memset(this, 0, sizeof(socket_server));
	}
	struct connection_st* slot[65536];
	int lisfd_serverid[65536];
	int epfd[EPOLL_NUM];
	bool shut_server;
	pthread_t worker[NUM_WORKER];
};

extern socket_server SOCKET_SERVER;

static void records(int per_recv, int max_recv);

void sigroutine(int signo);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
Stream_Base* make_stream_packet(char *data, int len);

extern int sendData(connection_st* conn, char *data, int len);

static bool parse_stream_head(int fd, Stream_Base& stream, std::vector<Message>& vstream);



static int handleReadEvent(connection_st* conn);

static int handleWriteEvent(connection_st* conn);

extern void closeConnection(int fd);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////





extern int do_listen(int handle, int port, int block);
extern int do_accept(connection_st* conn);


extern void do_poll(int epfd);





#endif