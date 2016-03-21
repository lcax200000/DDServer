
#include "Timer_Queue.h"
#include "ServiceObj.h"
#include "Socket_Poll.h"

Timer_Queue::Timer_Queue(void) : wait_event_(false, false,NULL)
{
	//LOGINFO("Timer queue create...");
	is_run_ = true;
	timer_id_count_ = 0;
}

Timer_Queue::~Timer_Queue(void)
{
}
Timer_Queue* Timer_Queue::g_timer_queue_ = NULL;

Timer_Queue* Timer_Queue::instance()
{
	static DDMutex _lock;
	if(g_timer_queue_ == NULL)
	{
		GUARD_RETURN(DDMutex, obj, _lock, NULL);
		if(g_timer_queue_ == NULL)
		{
			g_timer_queue_ = new Timer_Queue;
			//Singleton_Manager::instance()->add_singleton(g_timer_queue_);
		}
	}
	return g_timer_queue_;
}

void Timer_Queue::finstance(void)
{
	if (g_timer_queue_ != NULL)
	{
		delete g_timer_queue_;
	}
}



long Timer_Queue::schedule_timer(int _h, const Time_Value &time)
{
	//得到绝对时间
	Time_Value absolute_time = Time_Value::gettimeofday() + time;
	//加入时间队列
	bool fire_now = false;
	long id = 0;
	{
		GUARD_RETURN(DDMutex, obj, l_, NULL);
		if(is_run_ == false)
			return -1;
		id = next_id();
		STimerItem* item = new STimerItem(_h,id, absolute_time, Time_Value::zero, false);
		tq_.push(item);
		timer_map_.insert(TimerMapPair(id,item));
		if(tq_.top()->tv_ == absolute_time)
		{
			fire_now = true;
		}
	}
	//如果最早时间就是本次时间，那么需要激活定时器等待，并更新为本次时间
	if(fire_now)
	{
		wait_event_.signal();
	}
	return id;
}

long Timer_Queue::schedule_repeating_timer(int _h, const Time_Value &interval)
{
	//得到绝对时间
	Time_Value absolute_time = Time_Value::gettimeofday() + interval;
	//加入时间队列
	bool fire_now = false;
	long id = 0;
	{
		GUARD_RETURN(DDMutex, obj, l_, NULL);
		if (is_run_ == false)
			return -1;
		id = next_id();
		STimerItem* item = new STimerItem(_h,id, absolute_time, interval, true);
		tq_.push(item);
		timer_map_.insert(TimerMapPair(id,item));
		if(tq_.top()->tv_ == absolute_time)
		{
			fire_now = true;
		}
	}
	//如果最早时间就是本次时间，那么需要激活定时器等待，并更新为本次时间
	if(fire_now)
	{
		wait_event_.signal();
	}
	return id;
}

int Timer_Queue::svc()
{
	Time_Value absolute_time;
	Time_Value relative_time;
	int result = 0;
	Time_Value cur_time;
	//LOGINFO("Timer Queue begin service...");
	//至少等待一次single
	wait_event_.wait();
	while(is_run_)
	{
		bool wait_able_ = false;
		{
			GUARD_RETURN(DDMutex, obj, l_, NULL);
			if(tq_.size() == 0)
			{
				wait_able_ = true;
			}
			else
			{
				absolute_time = tq_.top()->tv_;
			}
		}

		if(wait_able_ == true)
		{
			wait_event_.wait();
			continue;
		}
		else
		{
			//可以处理一个定时器
			cur_time = Time_Value::gettimeofday();

			if(absolute_time > cur_time)
			{
				relative_time = absolute_time - cur_time;
			}
			else//时间等于或者小于的的话，都立马执行
			{
				relative_time = Time_Value::zero;
			}
			result = wait_event_.wait(relative_time);
		}
		if(is_run_ == false)
		{
			break;
		}
		// Check for timer expiries.
		printf("wait res %d\n", result);
		if (result==0)
		{
			int i = 0;
		}
		switch(result)
		{
		case 1:
			{
				STimerItem* item = NULL;
				// timeout: expire timers
				Time_Value now = absolute_time;
				Time_Value want_tv = Time_Value::zero;
				{
					//得到所有可以激活的handler
					GUARD_RETURN(DDMutex, obj, l_, NULL);
					if(tq_.size() == 0)
						continue;
					if(tq_.top()->tv_ <= now)
					{
						item = tq_.top();
						tq_.pop();
						want_tv = item->tv_;
						if(item->repeat_ == true && item->enable_ == true)
						{
							item->tv_ = now + item->interval_;
							tq_.push(item);
						}
						else
						{
							timer_map_.erase(item->timer_id_);
						}

						if(item->enable_ == true)
						{
							Message msg(item->timer_id_, SOCKET_TYPE_TIMEOUT, NULL);
							ServiceMgr::instance()->GetService(item->service_hanlde)->Push(msg);
						}
						if (item->repeat_ == false || item->enable_==false)
						{
							delete item;
						}
					}
				}
			}
			break;
		case 0:
			break;
		default:
			//LOGERROR("Timer Queue wait error %d",GetLastError());
			return 0;
		}
	}
	//LOGINFO("Timer Queue end service...");
	return 1;
}

void Timer_Queue::cancel(long id)
{
	GUARD(DDMutex, obj, l_);
	TimerMap::iterator fit = timer_map_.find(id);
	if(fit != timer_map_.end())
	{
		fit->second->enable_ = false;
		timer_map_.erase(fit);
	}
}



void Timer_Queue::stop()
{
	{
		GUARD(DDMutex, obj, l_);
		timer_map_.clear();
		while(tq_.size() > 0)
		{
			tq_.pop();
		}
		is_run_ = false;
	}
	
	wait_event_.signal();
}
