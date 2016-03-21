#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>
#include "Socket_Poll.h"
#include "Lua_C.h"
#include "ServiceObj.h"
#include "Timer_Queue.h"
#include "tinyxml.h"  
#include "tinystr.h" 

extern socket_server SOCKET_SERVER;


void* workerThread(void* arg)
{
	int epfd = *(int*)arg;

	do_poll(epfd);
}

void* timerThread(void* arg)
{

	Timer_Queue::instance()->svc();
}

int main(int argc, char *const argv[]) 
{
	int pid = 1;
	int port = -1;

	std::vector<Node> nodes;
	//创建一个XML的文档对象。  
	TiXmlDocument *myDocument = new TiXmlDocument("config.xml");
	myDocument->LoadFile();

	//获得根元素，即Persons。  
	TiXmlElement *RootElement = myDocument->RootElement();
	
  	TiXmlElement* pEle = NULL;
  	for (pEle = RootElement->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())
  	{
		Node mynode;
		mynode.PID = atoi(pEle->Attribute("PID"));
		strcpy(mynode.IP, pEle->Attribute("IP"));
		
		int i = 0;
		for (TiXmlElement* pEle2 = pEle->FirstChildElement(); pEle2; pEle2 = pEle2->NextSiblingElement())
		{
			Unit _u;
			_u.id = mynode.PID * 10 + i;
			strcpy(_u.name, pEle2->Attribute("name"));
			strcpy(_u.path, pEle2->Attribute("path"));
			_u.port = atoi(pEle2->Attribute("port"));
			mynode.unis[i] = _u;
			++i;
		}
		nodes.push_back(mynode);
  	}

	ServiceMgr::instance()->Init(pid, nodes);
	int i = 0;
	for (std::vector<Node>::iterator iter = nodes.begin(); iter != nodes.end(); ++iter, ++i)
	{
		if (iter->PID == pid)
		{
			for (int j = 0; iter->unis[j].id > 0; ++j)
			{
				ServiceMgr::instance()->Register(iter->unis[j].id, new ServiceLua(iter->unis[j].path,iter->unis[j].port));
			}
			break;
		}
	}

// 	struct itimerval value, ovalue;
// 	printf("main thread tid = %u\n", pthread_self());
// 	signal(SIGALRM, sigroutine);
// 	signal(SIGVTALRM, sigroutine);
// 	value.it_value.tv_sec = 1;
// 	value.it_value.tv_usec = 0;
// 	value.it_interval.tv_sec = 1;
// 	value.it_interval.tv_usec = 0;
// 	setitimer(ITIMER_REAL, &value, &ovalue);

	for (int epi = 0; epi < EPOLL_NUM; ++epi) 
	{
		SOCKET_SERVER.epfd[epi] = epoll_create(20);
	}

	for (int i = 0; i < EPOLL_NUM; ++i)
    {
		int j;
		for (j = 0; j < WORKER_PER_GROUP; ++j) 
			pthread_create(SOCKET_SERVER.worker + (i * WORKER_PER_GROUP + j), NULL, workerThread, SOCKET_SERVER.epfd + i);
	}
	pthread_t serpd;
	pthread_create(&serpd, NULL, timerThread, NULL);
	


	ServiceMgr::instance()->DoService();
	ServiceMgr::instance()->WaitService();


	for (int i = 0; i < NUM_WORKER; ++i)
    {
		pthread_join(SOCKET_SERVER.worker[i], NULL);
	}

    return 0;
}
