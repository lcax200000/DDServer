#include "ServiceObj.h"


void MessageQueue::Push(Message& msg)
{
	lock_free_.push(msg);
}


Message MessageQueue::Pop()
{
	Message result;
	lock_free_.pop(result);
	return result;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void ServiceObj::Init(int handle)
{
	m_handle = handle;
	m_con = new DDCondition(m_mutex);
}
void ServiceObj::Free()
{}

void ServiceObj::Push(Message& msg)
{
	m_mq.Push(msg);
	m_con->signal();
}

Message ServiceObj::Pop()
{
	return m_mq.Pop();
}

void ServiceObj::Wait()
{
	m_con->wait();
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

ServiceMgr::ServiceMgr()
{}

ServiceMgr::~ServiceMgr()
{}

void ServiceMgr::Init(int pid, std::vector<Node>& nodes)
{
	for (std::vector<Node>::iterator iter = nodes.begin(); iter != nodes.end(); ++iter)
	{
		for (int i = 0;i<10;++i)
		{
			char sp[32] = { 0, };
			sprintf(sp, "%d", iter->unis[i].port);

			m_services[iter->unis[i].name] = iter->IP;
			m_services[iter->unis[i].name] += "&&";
			m_services[iter->unis[i].name] += sp;

		}
	}
}

void ServiceMgr::Register(int handle, ServiceObj* sobj)
{
	if (handle < 255)
	{
		m_objs[handle] = sobj;
		m_handles.push_back(handle);
	}
}


void* serviceThread(void *arg)
{
	ServiceObj* obj = (ServiceObj*)arg;
	while (true)
	{
		if (obj->Empty())
		{
			obj->Wait();
		}
		else
		{
			Message pmsg = obj->Pop();
			obj->Dispatch(pmsg);
			pmsg.releaseBuf();
		}
	}
	return NULL;
}

void ServiceMgr::DoService()
{
	for (std::vector<int>::iterator iter = m_handles.begin(); iter != m_handles.end(); ++iter)
	{
		if (m_objs[*iter] != NULL)
		{
			m_objs[*iter]->Init(*iter);

			pthread_t serpd;
			pthread_create(&serpd, NULL, serviceThread, (void*)(m_objs[*iter]));
			m_ptsp.push_back(serpd);
		}
	}
}

void ServiceMgr::WaitService()
{
	for (std::vector<pthread_t>::iterator iter = m_ptsp.begin(); iter != m_ptsp.end(); ++iter)
	{
		pthread_join(*iter, NULL);
	}
}

ServiceMgr*  ServiceMgr::instance(void)
{
	static ServiceMgr* g_service = NULL;
	static DDMutex _lock;
	if (g_service == NULL)
	{
		GUARD_RETURN(DDMutex, obj, _lock, NULL);
		if (g_service == NULL)
		{
			g_service = new ServiceMgr;
		}
	}
	return g_service;
}