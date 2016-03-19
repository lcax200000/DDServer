

#ifndef SERVICEOBJ_H
#define SERVICEOBJ_H
#include "boost/lockfree/queue.hpp"
#include "Stream.h"
#include "Thread.h"
#include <vector>
#include <map>
struct Message
{
	Message()
	{
		memset(this, 0, sizeof(Message));
	}
	Message(int fd, int _t, Stream_Base* _s) :m_fd(fd), m_type(_t), m_stream(_s)
	{}
	int getFd(){ return m_fd; }
	int getType(){ return m_type; }
	Stream_Base* getMsg(){ return m_stream;	}
	void releaseBuf()
	{
		if (m_stream)
		{
			delete m_stream;
			m_stream = NULL;
		}
	}

	int m_fd;
	int m_type;
	Stream_Base* m_stream;
};

class MessageQueue
{
public:
    MessageQueue(){}
    ~MessageQueue(){}
    
	void Push(Message&);
	Message Pop();
	bool Empty(){ return lock_free_.empty(); }
private:
	boost::lockfree::queue<Message> lock_free_;
};


class ServiceObj
{
public:
    ServiceObj()
    {
		m_handle = 0;
		m_con = NULL;
    }
    
    virtual ~ServiceObj(){}
    
	virtual void Init(int handle);
	virtual void Free();
    
	virtual void Dispatch(Message& msg){}
	virtual void OnConnect(int fd){}

	void Push(Message& msg);
	Message Pop();
	
	void Wait();
	bool Empty(){ return m_mq.Empty(); }
private:
	int m_handle;
    MessageQueue m_mq;    
	DDCondition* m_con;
	DDMutex m_mutex;
};


struct Unit
{
	Unit()
	{
		memset(this, 0, sizeof(Unit));
	}
	int id;
	int port;
	char name[32];
	char path[256];
};

struct Node
{
	Node()
	{
		memset(this, 0, sizeof(Node));
	}
	int PID;
	char IP[32];
	Unit unis[10];
};

class ServiceMgr
{
public:
	ServiceMgr();
    
	~ServiceMgr();
 
	void Init(int pid, std::vector<Node>&);
	void Register(int handle, ServiceObj* sobj);
 
	inline ServiceObj* GetService(int handle)
	{
		if (handle < 255)
		{
			return m_objs[handle];
		}
		return NULL;
	}

	std::map<std::string, std::string>& GetServicesMap()
	{
		return m_services;
	}

	void DoService();

	void WaitService();

	static  ServiceMgr*  instance(void);

 private:
    ServiceObj* m_objs[255];
	std::vector<int> m_handles;
	std::vector<pthread_t> m_ptsp;
	std::map<std::string, std::string> m_services;
}; 
#endif