#include "Thread.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

DDMutex::DDMutex()
{
#ifdef WIN32
	InitializeCriticalSection(&this->thr_mutex_);
#else
	pthread_mutex_init(&handle,NULL);
#endif
	
}

DDMutex::~DDMutex(void)
{
	this->remove();
}

bool DDMutex::remove(void)
{
#ifdef WIN32
	DeleteCriticalSection(&this->thr_mutex_);
#else
	pthread_mutex_destroy(&handle);
#endif
	return  true;
}

bool  DDMutex::acquire(void)
{
#ifdef WIN32
	EnterCriticalSection(&this->thr_mutex_);
#else
	return pthread_mutex_lock(&handle) == 0 ? true : false;
#endif
	return true;
}

bool DDMutex::release(void)
{
#ifdef WIN32
	LeaveCriticalSection(&this->thr_mutex_);
#else
	return pthread_mutex_unlock(&handle) == 0 ? true : false;
#endif
	return  true;
}

DDEvent::DDEvent(bool b_manual, bool binit_stat, const char* name) : name_(name), remove_(0)
{
#ifdef WIN32
	event_handle_= ::CreateEventA(NULL,b_manual,binit_stat,name);
#else
	hevent.state = binit_stat;
	hevent.manual_reset = b_manual;
	pthread_mutex_init(&hevent.mutex, NULL);
	pthread_cond_init(&hevent.cond, NULL);
#endif
}
DDEvent::~DDEvent()
{
	remove();
}

bool DDEvent::signal (void)
{
#ifdef WIN32
	return ::SetEvent(event_handle_);
#else
	if (pthread_mutex_lock(&hevent.mutex) != 0)
	{
		return false;
	}

	hevent.state = true;
	// 手动，广播所有
	if (hevent.manual_reset)
	{
		if(pthread_cond_broadcast(&hevent.cond))
		{
			return false;
		}
	}
	else
	{
		// 自动，每次只触发一个
		if(pthread_cond_signal(&hevent.cond))
		{
			return false;
		}
	}

	if (pthread_mutex_unlock(&hevent.mutex) != 0)
	{
		return false;
	}

	return true;
#endif
}

/** Method
* - Summary:\n
*	关闭事件
* - Parameters:\n
*  
* - return\n
*   0 is sucess,-1 is fails
*/
int DDEvent::remove (void)
{
	int result = -1;
#ifdef WIN32
	if (remove_ == 0)
	{
		remove_ = 1;
		result = ::CloseHandle(event_handle_)?0:-1;
	}
#else
	if (remove_ == 0)
	{
		remove_ = 1;
		pthread_cond_destroy(&hevent.cond);
		pthread_mutex_destroy(&hevent.mutex);
		result = 0;
	}
#endif
	return result;
}

/** Method
* - Summary:\n
*	等待事件
* - Parameters:\n
*  
* - return\n
*   0 is sucess,-1 is fails
*/
int DDEvent::wait ()
{
#ifdef WIN32
	switch(::WaitForSingleObject(event_handle_, INFINITE))
	{
	case WAIT_OBJECT_0:
		return 0;
	case WAIT_ABANDONED:
		return WAIT_ABANDONED;
	case WAIT_TIMEOUT:
		return WAIT_TIMEOUT;
	default:
		return -1;
	}
#else
	if (pthread_mutex_lock(&hevent.mutex))   
	{      
		return -1;   
	}   
	while (!hevent.state)    
	{      
		// linux 条件变量的用法，这里会解锁，把hevent.state让给其他线程然后等待
		// 当其他线程修改hevent.state以后会触发条件变量hevent.cond
		// 这里就会得到响应退出
		if (pthread_cond_wait(&hevent.cond, &hevent.mutex))   
		{   
			pthread_mutex_unlock(&hevent.mutex); 
			return -1;
		}   
	}   
	// 如果是自动事件这里要重置
	if (!hevent.manual_reset) 
	{
		hevent.state = false;
	}
	if (pthread_mutex_unlock(&hevent.mutex))   
	{     
		return -1;   
	}  
	return 0;
#endif
}

/** Method
* - Summary:\n
*	等待事件
* - Parameters:\n
*   Time_Value 对像，等待的时间
* - return\n
*   0 is sucess,-1 is fails 超时返回1
*/
int DDEvent::wait (Time_Value& time_value)
{
#ifdef WIN32
	switch(::WaitForSingleObject(event_handle_, time_value.msec()))
	{
	case WAIT_OBJECT_0:
		return 0;
	case WAIT_ABANDONED:
		return WAIT_ABANDONED;
	case WAIT_TIMEOUT:
		return 1;    //WAIT_TIMEOUT;   超时返回1
 	default:
		return -1;
	}
#else
	int rc = 0;   
	struct timespec abstime;   
	struct timeval tv;   
	gettimeofday(&tv, NULL);   
	abstime.tv_sec  = tv.tv_sec + time_value.msec() / 1000;   
	abstime.tv_nsec = tv.tv_usec*1000 + (time_value.msec() % 1000)*1000000; 
	//abstime.tv_sec = time_value.msec() / 1000;
	//abstime.tv_nsec = (time_value.msec() % 1000) * 1000000;
	if (abstime.tv_nsec >= 1000000000)   
	{   
		abstime.tv_nsec -= 1000000000;   
		abstime.tv_sec++;   
	}   

	if (pthread_mutex_lock(&hevent.mutex) != 0)   
	{     
		return -1;   
	}   
	while (!hevent.state)    
	{      
		if (rc = pthread_cond_timedwait(&hevent.cond, &hevent.mutex, &abstime))   
		{   
			if (rc == ETIMEDOUT) break;   
			pthread_mutex_unlock(&hevent.mutex);    
			return -1;   
		}   
	}   
	if (rc == 0 && !hevent.manual_reset)   
	{
		hevent.state = false;
	}
	if (pthread_mutex_unlock(&hevent.mutex) != 0)   
	{      
		return -1;   
	}
	if (rc == ETIMEDOUT)
	{
		//timeout return 1
		return 1;
	}
	else
		printf("rc != timeout %d\n", rc);
	//wait event success return 0
	return 0;
#endif
	
}
				
/** Method
* - Summary:\n
*	设轩为激发状态
* - Parameters:\n
*  
* - return\n
*   true is sucess  false is fails
*/
bool DDEvent::reset (void)
{
#ifdef WIN32
	return ResetEvent(event_handle_) == TRUE;
#else
	if (pthread_mutex_lock(&hevent.mutex) != 0)
	{
		return false;
	}

	hevent.state = false;

	if (pthread_mutex_unlock(&hevent.mutex) != 0)
	{      
		return false;
	}
	return true;
#endif
}


/** Method
* - Summary:\n
*  构造 创建互斥体，信号量和事件
* - Parameters:\n
*	1 锁,
*
*/
DDCondition::DDCondition(DDMutex& m, const char* name):mutex_(m),name_(name)
{
#ifdef WIN32
	cond_.was_broadcast_ = 0;
	cond_.waiters_  = 0;
	cond_.sema_ = ::CreateSemaphoreA(NULL, 0, 65536, name);

	InitializeCriticalSection(&cond_.waiters_lock_);
	cond_.waiters_done_ = CreateEvent(NULL, false, false, 0);
#else
	pthread_cond_init(&cond, NULL);
#endif
}

DDCondition::~DDCondition()
{
	remove();
}

/** Method
* - Summary:\n
*进入一个等待
* - Parameters:\n
*
*- return
*0 is sucess.1 si falid
*/
int DDCondition::wait()
{
#ifdef WIN32
	EnterCriticalSection(&cond_.waiters_lock_);
	cond_.waiters_++;
	LeaveCriticalSection(&cond_.waiters_lock_);
	int result = 0;
	int error  = 0;

	mutex_.release();
	result = ::WaitForSingleObject(cond_.sema_, INFINITE);

	EnterCriticalSection(&cond_.waiters_lock_);
	cond_.waiters_--;
	int last_waiter = cond_.was_broadcast_ && cond_.waiters_ == 0;
	LeaveCriticalSection(&cond_.waiters_lock_);

	if(result != WAIT_OBJECT_0)
	{
		switch(result)
		{
		case WAIT_TIMEOUT:
			break;
		default:
			break;
			return -1;
		}
	}
	else if (last_waiter)
	{
		SetEvent(cond_.waiters_done_);
	}

	mutex_.acquire();
	return result;
#else
	return pthread_cond_wait(&cond, &mutex_.get_handle());
#endif
}

/** Method
* - Summary:\n
*进入一个等待
* - Parameters:\n
*  1 等待的事间，超时返回0。如果传NULL则为无超时
*- return
*0 is sucess.1 si falid
*/
int DDCondition::wait(Time_Value& time_value)
{
#ifdef WIN32
	EnterCriticalSection(&cond_.waiters_lock_);
	cond_.waiters_++;
	LeaveCriticalSection(&cond_.waiters_lock_);
	int result = 0;
	int error  = 0;

	mutex_.release();
	if (time_value.msec() == 0)
	{
		result = ::WaitForSingleObject(cond_.sema_, INFINITE);
	}
	else
	{
		result = ::WaitForSingleObject(cond_.sema_, time_value.msec());
	}

	EnterCriticalSection(&cond_.waiters_lock_);
	cond_.waiters_--;
	int last_waiter  = cond_.was_broadcast_ && cond_.waiters_ == 0;
	LeaveCriticalSection(&cond_.waiters_lock_);

	if(result != WAIT_OBJECT_0)
	{
		switch(result)
		{
		case WAIT_TIMEOUT:
			break;
		default:
			break;
			return -1;
		}
	}
	else if (last_waiter)
	{
		SetEvent(cond_.waiters_done_);
	}

	mutex_.acquire();
	return result;
#else
	if (time_value.msec() == 0)
	{
		return wait();
	}
	else
	{ 
		struct timespec abstime;   
		struct timeval tv;   
		gettimeofday(&tv, NULL);   
		abstime.tv_sec  = tv.tv_sec + time_value.msec() / 1000;   
		abstime.tv_nsec = tv.tv_usec*1000 + (time_value.msec() % 1000)*1000000;   
		if (abstime.tv_nsec >= 1000000000)   
		{   
			abstime.tv_nsec -= 1000000000;   
			abstime.tv_sec++;   
		}   
		return pthread_cond_timedwait(&cond, &mutex_.get_handle(), &abstime);
	}
#endif
}
/** Method
* - Summary:\n
*唤醒一个等待
* - Parameters:\n
*
*- return
*0 is sucess.1 si falid
*/
int DDCondition::signal(void)
{
#ifdef WIN32
	EnterCriticalSection(&cond_.waiters_lock_);
	int have_waits = cond_.waiters_;
	LeaveCriticalSection(&cond_.waiters_lock_);

	int result = 0;
	if (have_waits > 0)
	{
		bool b = ReleaseSemaphore(cond_.sema_, 1, 0) == TRUE;
		result = b ? 0:-1;
		return result;
	}

	return  result;
#else
	return pthread_cond_signal(&cond);
#endif
}

/** Method
* - Summary:\n
*唤醒所有的等待
* - Parameters:\n
*
*- return
*0 is sucess.1 si falid
*/
int DDCondition::broadcast(void)
{
#ifdef WIN32
	int have_waits = 0;
	EnterCriticalSection(&cond_.waiters_lock_);
	if (cond_.waiters_ > 0)
	{
		cond_.was_broadcast_ = 1;
		have_waits = 1;
	}
	LeaveCriticalSection(&cond_.waiters_lock_);

	int result = 0;

	if (have_waits)
	{
		if (!::ReleaseSemaphore(cond_.sema_, cond_.waiters_, 0))
		{
			return -1;
		}

		switch (::WaitForSingleObject(cond_.waiters_done_, INFINITE))
		{
		case WAIT_OBJECT_0:
			{
				result = 0;
			}
		default:
			result = -1;
		}

		cond_.was_broadcast_ = 0;
	}

	return result;
#else
	return pthread_cond_broadcast(&cond);
#endif
}

/** Method
* - Summary:\n
*关闭事件，信号量，锁
* - Parameters:\n
*
*- return
*0 is sucess.1 si falid
*/
int DDCondition::remove(void)
{

#ifdef WIN32
	::CloseHandle(cond_.waiters_done_);

	DeleteCriticalSection(&cond_.waiters_lock_);

	::CloseHandle(cond_.sema_);
#else
	return pthread_cond_destroy(&cond);
#endif
	return 0;
}