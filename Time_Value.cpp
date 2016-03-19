
#include "Time_Value.h"

const Time_Value Time_Value::max_time (0xFFFFFFFF,ACE_ONE_SECOND_IN_USECS - 1);
const   Time_Value   Time_Value::zero;
#ifdef WIN32
const DWORDLONG Time_Value::FILETIME_to_timval_skew =
	(0x19db1ded53e8000);
#endif

///////////////////构造函数//////////////////////////////////////////
Time_Value::Time_Value(void)
{
	this->set(0,0);
}

Time_Value::Time_Value(long sec,long usec)
{
	this->set(sec,usec);
}

Time_Value::Time_Value(const struct timeval& tv)
{
	this->set(tv);
}

#ifdef WIN32
Time_Value::Time_Value(const FILETIME &ft)
{
	this->set(ft);
}
#endif



////////////////////////////////可以考虑转为内联函数//////////////////////////////////
Time_Value::operator timeval() const
{
	return this->tv_;
}


Time_Value::operator const timeval *() const
{
	return (const timeval*)&this->tv_;
}

void Time_Value::set(long sec,long usec)
{
	this->tv_.tv_sec = sec;
	this->tv_.tv_usec = usec;
	this->normalize();
}

#ifdef WIN32
void Time_Value::set(const FILETIME &ft)
{
	ULARGE_INTEGER  _100ns;
	_100ns.LowPart =  ft.dwLowDateTime;
	_100ns.HighPart = ft.dwHighDateTime;
	//这里是减去一个1970年的绝对值。这里保存的时间是从1970后的时间的秒和微秒
	_100ns.QuadPart -= Time_Value::FILETIME_to_timval_skew;

	this->tv_.tv_sec = (long) (_100ns.QuadPart / (10000 * 1000));
	this->tv_.tv_usec = (long) ((_100ns.QuadPart % (10000 * 1000)) / 10);
	this->normalize();
}
#endif


void Time_Value::set(double d)
{
	long l = (long)d;
	this->tv_.tv_sec = l;
	this->tv_.tv_usec = (long)((d - (double) l) * ACE_ONE_SECOND_IN_USECS + .5);
	this->normalize();
}

void Time_Value::set(const timeval &tv)
{
	this->tv_.tv_sec = tv.tv_sec;
	this->tv_.tv_usec = tv.tv_usec;
	this->normalize();
}
long Time_Value::sec(void) const
{
	return this->tv_.tv_sec;
}

void  Time_Value::sec (long sec)
{
	// ACE_OS_TRACE ("ACE_Time_Value::sec");
	this->tv_.tv_sec = sec;
}


long Time_Value::usec(void) const
{
	return this->tv_.tv_usec;
}

void Time_Value::usec(long usec)
{
	this->tv_.tv_usec = usec;
}

unsigned long Time_Value::msec(void)
{
	return (unsigned long)this->tv_.tv_sec * 1000 + this->tv_.tv_usec / 1000;
}
void Time_Value::msec(unsigned long milliseconds)
{
	this->tv_.tv_sec = milliseconds/1000;
	this->tv_.tv_usec = (milliseconds - (this->tv_.tv_sec * 1000)) * 1000;
}


Time_Value Time_Value::operator *=(double d)
{
	double  time = ((double)this->sec()) * ACE_ONE_SECOND_IN_USECS + this->usec();
	time *= d;
	return Time_Value((long)time);
}
/////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//全局重载函数
///////////////////////////////////////////////////////////////////////////////
Time_Value operator*(double d,const Time_Value& tv)
{
	return Time_Value(tv)*=d;
}

Time_Value operator*(const Time_Value &tv,double d)
{
	return Time_Value(tv)*=d;
}

int operator >(const Time_Value& tv1,const Time_Value &tv2)
{
	if (tv1.sec() > tv2.sec())
	{
		return 1;
	}
	else if (tv1.sec() == tv2.sec() && tv1.usec() > tv2.usec())
	{
		return 1;
	}
	return 0;
}

int operator >=(const Time_Value& tv1,const Time_Value& tv2)
{
	if (tv1.sec() > tv2.sec())
	{
		return 1;
	}
	else if (tv1.sec() == tv2.sec() && tv1.usec() >= tv2.usec())
	{
		return 1;
	}
	return 0;
}

int operator < (const Time_Value& tv1,const Time_Value& tv2)
{
	return tv2 > tv1;
}

int operator <= (const Time_Value& tv1,const Time_Value& tv2)
{
	return tv2 >= tv1;
}

int operator == (const Time_Value& tv1,const Time_Value& tv2)
{
	return (tv1.sec() == tv2.sec() && tv1.usec() == tv2.usec());
}

int operator != (const Time_Value& tv1,const Time_Value& tv2)
{
	return !(tv1 == tv2);
}

Time_Value& Time_Value::operator +=(const Time_Value &tv)
{
	this->tv_.tv_sec += tv.sec();
	this->tv_.tv_usec += tv.usec();

	this->normalize();
	return *this;
}


Time_Value& Time_Value::operator -=(const Time_Value &tv)
{
	this->tv_.tv_sec -= tv.sec();
	this->tv_.tv_usec -= tv.usec();

	this->normalize();
	return *this;

}

Time_Value operator + (const Time_Value &tv1,
							  const Time_Value &tv2)
{
	Time_Value sum(tv1.sec() + tv2.sec(),tv1.usec() + tv2.usec());
	sum.normalize();
	return sum;
}

Time_Value operator - (const Time_Value &tv1,
							  const Time_Value &tv2)
{
	Time_Value delta (tv1.sec() - tv2.sec(),tv1.usec() - tv2.usec());
	delta .normalize();
	return delta;
}


Time_Value Time_Value::operator ++(int)
{
	Time_Value tv(*this);
	++*this;
	return tv;
}

Time_Value& Time_Value::operator ++(void)
{
	this->usec(this->usec() + 1);
	this->normalize();
	return *this;
}

Time_Value Time_Value::operator --(int)
{
	Time_Value tv(*this);
	--*this;
	return tv;
}

Time_Value& Time_Value::operator --(void)
{
	this->usec(this->usec() - 1);
	this->normalize();
	return *this;
}


Time_Value::~Time_Value(void)
{

}

void Time_Value::normalize (void)
{
	if (this->tv_.tv_usec >= ACE_ONE_SECOND_IN_USECS)
	{
		do 
		{
			this->tv_.tv_sec++;
			this->tv_.tv_usec -= ACE_ONE_SECOND_IN_USECS;
		} while(this->tv_.tv_usec >= ACE_ONE_SECOND_IN_USECS);
	}
	else if (this->tv_.tv_usec <= -ACE_ONE_SECOND_IN_USECS)
	{
		do 
		{
			this->tv_.tv_sec--;
			this->tv_.tv_usec += ACE_ONE_SECOND_IN_USECS;
		} while(this->tv_.tv_usec <= -ACE_ONE_SECOND_IN_USECS);
	}

	if (this->tv_.tv_sec >=1 && this->tv_.tv_usec <0)
	{
		this->tv_.tv_sec--;
		this->tv_.tv_usec += ACE_ONE_SECOND_IN_USECS;
	}
	else if (this->tv_.tv_sec < 0 && this->tv_.tv_usec >0)
	{
		this->tv_.tv_sec++;
		this->tv_.tv_usec -= ACE_ONE_SECOND_IN_USECS;
	}
}

Time_Value Time_Value::gettimeofday(void)
{
#ifdef WIN32
	FILETIME tfile;
	::GetSystemTimeAsFileTime (&tfile);
	return Time_Value (tfile);
#else
	struct timeval t;
	struct timezone tz;
	::gettimeofday(&t, &tz);
	return Time_Value(t);
#endif

	
}

