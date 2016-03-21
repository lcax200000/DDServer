#ifndef TIMER_QUEUE
#define TIMER_QUEUE
#include "Time_Value.h"
#include "Thread.h"
#include <queue>
#include "Allocator_Manager.h"


#include <ext/hash_map>
using namespace __gnu_cxx;


class Timer_Queue
{
public:
	struct STimerItem
	{
		int service_hanlde;
		Time_Value tv_;
		Time_Value interval_;
		bool repeat_;
		bool enable_;
		long timer_id_;

		void* operator new(size_t sz)
		{
			Allocator_Manager::instance()->malloc(sz);
		}

		void operator delete(void* p)
		{
			if(p == NULL)
				return;
			Allocator_Manager::instance()->free(p);
		}

		STimerItem(int _h,long timer_id,const Time_Value& tv,const Time_Value& interval,bool repeat) 
			: service_hanlde(_h),timer_id_(timer_id), tv_(tv), interval_(interval), repeat_(repeat)
		{
			enable_ = true;
		}
	};

	typedef hash_map<long, STimerItem* > TimerMap;
	typedef std::pair<long, STimerItem* > TimerMapPair;
public:
	Timer_Queue(void);
public:
	~Timer_Queue(void);
	
	long schedule_timer(int _h, const Time_Value &time);

	long schedule_repeating_timer(int _h, const Time_Value &interval);

	void cancel(long id);

	void stop(void);

	void start(void);
public:
	virtual int svc(void);
public:
	long next_id()
	{
		timer_id_count_ ++;
		if(timer_id_count_ == -1)
		{
			return 1;
		}
		else
		{
			return timer_id_count_;
		}
	}
	static Timer_Queue* instance(void);

	static void finstance(void);


private:
	static Timer_Queue* g_timer_queue_;

	DDMutex l_;

	struct timeval_less : public std::binary_function<STimerItem*,STimerItem*,bool>
	{
		bool operator()(const STimerItem* _Left, const STimerItem* _Right) const
		{
			if(_Left->tv_.sec() < _Right->tv_.sec())
			{
				return false;
			}
			else if(_Left->tv_.sec() > _Right->tv_.sec())
			{
				return true;
			}
			else
			{
				//µÈÓÚ
				if(_Left->tv_.usec() <= _Right->tv_.usec())
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			return true;
		}
	};

	typedef std::priority_queue<STimerItem*, std::vector<STimerItem*> ,timeval_less> TimeQueue;

	TimeQueue tq_;

	DDEvent wait_event_;

	bool is_run_;

	TimerMap timer_map_;

	long timer_id_count_;

};
#endif