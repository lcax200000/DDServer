#ifndef THREAD_H
#define THREAD_H

#ifdef WIN32
#else
#include <pthread.h>
#include <errno.h>
#endif
#include "Time_Value.h"
/***********************************************************************
使用简单封装 
线程锁,对临界区进行了简单的封装
***********************************************************************/
class DDMutex
{
public:
	/** Property
	* - Summary:\n
	*构造函数
	*/
	DDMutex();

public:
	/** Method
	* - Summary:\n
	*析构函数,退出时删除昨界区
	* - Parameters:\n
	*
	*/
	~DDMutex(void);

	/** Method
	* - Summary:\n
	*得到锁
	* - Parameters:\n
	*
	*/
	bool  acquire(void);

	/** Method
	* - Summary:\n
	*删除锁
	* - Parameters:\n
	*
	*/
	bool  remove(void);

	/** Method
	* - Summary:\n
	*释放锁
	* - Parameters:\n
	*
	*/
	bool  release(void);

#ifdef WIN32
#else
	pthread_mutex_t& get_handle()
	{
		return handle;
	}
#endif
	
private:
#ifdef WIN32
	CRITICAL_SECTION thr_mutex_;
#else
	pthread_mutex_t handle;
#endif
};

////////////////////////////////////////////////////////////////////
/** ClassTtemplate
* - Summary:\n
*
*守卫类
* - TParameters:\n
*锁，传thread_mutex
*
*/
template<class TMUTEX>
class Thread_Guard
{
public:
	Thread_Guard(TMUTEX& mutex):mutex_(mutex),owner_(0)
	{
		this->acquire();
	}

	~Thread_Guard()
	{
		this->release();
	}
public:
	inline int  acquire(void)
	{
		this->owner_ = this->mutex_.acquire()?0:-1;
		return this->owner_;
	}

	inline int locked(void)
	{
		return this->owner_ != -1;
	}

	inline int release(void)
	{
		if (this->owner_ == -1)
		{
			return -1;
		}
		else
		{
			this->owner_ = -1;
			return	this->mutex_.release();
		}
	}

	TMUTEX& getMutex()
	{
		return mutex_;
	}

protected:
	TMUTEX&  mutex_;

	int owner_;
};

#define GUARD(MUTEX,OBJ,LOCK)\
	GUARD_REACTION(MUTEX,OBJ,LOCK,return)

#define GUARD_EXCEPTION(MUTEX,OBJ,LOCK)\
	GUARD_REACTION(MUTEX,OBJ,LOCK,throw exception("Lock Error!"))

#define GUARD_REACTION(MUTEX,OBJ,LOCK,REACTION)\
	GUARD_ACTION(MUTEX, OBJ, LOCK,;,REACTION)

#define GUARD_RETURN(MUTEX,OBJ,LOCK,RETURN)\
	GUARD_REACTION(MUTEX,OBJ,LOCK,return RETURN)

#define GUARD_ACTION(MUTEX,OBJ,LOCK,ACTION,REACTION) \
	Thread_Guard<MUTEX> OBJ(LOCK); \
	if (OBJ.locked () != 0) { ACTION; } \
   else { REACTION; }



// 事件
class DDEvent
{
#ifdef WIN32
#else
	struct event_t
	{
		bool state;				// 有无信号状态
		bool manual_reset;		// 是否手动
		pthread_mutex_t mutex;
		pthread_cond_t cond;
	};
#endif
public:
	DDEvent(bool b_manual, bool binit_stat, const char* name);
	~DDEvent();

	bool signal (void);

	/** Method
	* - Summary:\n
	*	关闭事件
	* - Parameters:\n
	*  
	* - return\n
	*   0 is sucess,-1 is fails
	*/
	int remove (void);

	/** Method
	* - Summary:\n
	*	等待事件
	* - Parameters:\n
	*  
	* - return\n
	*   0 is sucess,-1 is fails
	*/
	int wait ();

	/** Method
	* - Summary:\n
	*	等待事件
	* - Parameters:\n
	*   Time_Value 对像，等待的时间
	* - return\n
	*   0 is sucess,-1 is fails 超时返回1
	*/
	int wait (Time_Value& time_value);
				
	/** Method
	* - Summary:\n
	*	设轩为激发状态
	* - Parameters:\n
	*  
	* - return\n
	*   true is sucess  false is fails
	*/
	bool reset (void);

private:

#ifdef WIN32
	HANDLE event_handle_;
#else
	event_t hevent;
#endif

	/** Property
	* - Summary:\n
	*事件名字
	*/
	const char*  name_;

	int remove_;
};


#ifdef WIN32
class TF_cond_t
{
public:
	TF_cond_t(void){}

	~TF_cond_t(void){}
	/** Property
	* - Summary:\n
	*等待个数
	*/
	long waiters_;

	//long waiters(void) const;

	/** Property
	* - Summary:\n
	*等待个数
	*/
	CRITICAL_SECTION  waiters_lock_;
		
	/** Property
	* - Summary:\n
	*信号量
	*/
	HANDLE sema_;

	/** Property
	* - Summary:\n
	*在bostcast时的事件
	*/
	HANDLE waiters_done_;

	/** Property
	* - Summary:\n
	*在bostcast时的标志
	*/
	size_t was_broadcast_;
};
#endif


/** ClassTtemplate
* - Summary:\n
*
*条件变量
* - TParameters:\n
*锁，传tf_mutex
*/
class  DDCondition
{
public:
	/** Method
	* - Summary:\n
	*  构造 创建互斥体，信号量和事件
	* - Parameters:\n
	*	1 锁,
	*
	*/
	DDCondition(DDMutex& m, const char* name=0);

	~DDCondition();

public:
	/** Method
	* - Summary:\n
	*进入一个等待
	* - Parameters:\n
	*
	*- return
	*0 is sucess.1 si falid
	*/
	int wait();

	/** Method
	* - Summary:\n
	*进入一个等待
	* - Parameters:\n
	*  1 等待的事间，超时返回0。如果传NULL则为无超时
	*- return
	*0 is sucess.1 si falid
	*/
	int wait(Time_Value& time_value);
	/** Method
	* - Summary:\n
	*唤醒一个等待
	* - Parameters:\n
	*
	*- return
	*0 is sucess.1 si falid
	*/
	int signal();

	/** Method
	* - Summary:\n
	*唤醒所有的等待
	* - Parameters:\n
	*
	*- return
	*0 is sucess.1 si falid
	*/
	int broadcast();

	/** Method
	* - Summary:\n
	*关闭事件，信号量，锁
	* - Parameters:\n
	*
	*- return
	*0 is sucess.1 si falid
	*/
	int remove();
protected: 
#ifdef WIN32
	/** Property
	* - Summary:\n
	*内部cond对象
	*/
	TF_cond_t cond_; 
#else
	pthread_cond_t cond;
#endif

	/** Property
	* - Summary:\n
	*锁
	*/
	DDMutex& mutex_; 

private:
	/** Property
	* - Summary:\n
	*名字，指向一个常量
	*/
	const char* name_;
};

#endif