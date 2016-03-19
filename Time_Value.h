#ifndef TIMEVALUE_H
#define TIMEVALUE_H
#ifdef WIN32
#include <Winsock2.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

#define ACE_ONE_SECOND_IN_MSECS 1000L
#define ACE_ONE_SECOND_IN_USECS 1000000L
#define ACE_ONE_SECOND_IN_NSECS 1000000000L


/** ClassTtemplate
* - Summary:\n
*Time value 类。得到相对时间
* - TParameters:\n
*
*/
class Time_Value
{
public:
	/** Method
	* - Summary:\n
	* 构造
	* - Parameters:\n
	*
	*/
	Time_Value(void);
	
	/** Method
	* - Summary:\n
	* 构造
	* - Parameters:\n
	*1 秒  2 微秒
	*/
	Time_Value(long sec,long usec = 0);

	/** Method
	* - Summary:\n
	* 构造
	* - Parameters:\n
	*1 timeval 结构体
	*/
	Time_Value(const timeval &t);

#ifdef WIN32
	Time_Value (const FILETIME &ft);
#endif
	

	~Time_Value(void);
	/** Method
	* - Summary:\n
	* 设置时间
	* - Parameters:\n
	*1 秒 2 微秒
	*/
	void set(long sec,long usec);

#ifdef WIN32
	void set (const FILETIME &ft);
#endif
	
	//Init the class from a double,which is assumed to be 
	//in second format,with any remainder treated as microseconds
	/** Method
	* - Summary:\n
	* 设置时间
	* - Parameters:\n
	*1 double 部分，整数为秒，小数为微秒
	*/
	void set(double d);

	/** Method
	* - Summary:\n
	* 设置时间
	* - Parameters:\n
	*1
	*/
	void set(const timeval& t);

	unsigned long msec(void);

	void msec(unsigned long milliseconds);


	/** Property
	* - Summary:\n
	*静态属性，表示时间0
	*/
	static  const   Time_Value   zero;
	/** Property
	* - Summary:\n
	*静态属性，表示最大时间。0XFFFFFFFF FFFFFFFF
	*/
	static  const   Time_Value   max_time;

	operator timeval () const;

	operator const timeval* () const;

	long  sec (void) const;

	void  sec(long sec);

	long  usec (void) const;

	void  usec(long usec);


	Time_Value &operator +=(const Time_Value &tv);

	Time_Value &operator -=(const Time_Value &tv);

	Time_Value operator *=(double d);

	Time_Value &operator ++(void);

	Time_Value operator ++(int);

	Time_Value operator --(int);

	Time_Value &operator --(void);

	friend  Time_Value operator + (const Time_Value &tv1,
		const Time_Value &tv2);

	friend Time_Value operator - (const Time_Value &tv1,
		const Time_Value &tv2);

	friend int operator > (const Time_Value &tv1,
		const Time_Value &tv2);

	friend int operator < (const Time_Value &tv1,
		const Time_Value &tv2);

	friend int operator >= (const Time_Value &tv1,
		const Time_Value &tv2);

	friend int operator <= (const Time_Value &tv1,
		const Time_Value &tv2);

	friend int operator == (const Time_Value &tv1,
		const Time_Value &tv2);

	friend int operator != (const Time_Value &tv1,
		const Time_Value &tv2);

	friend Time_Value operator *(double d,
		const Time_Value &tv);

	friend Time_Value operator *(const Time_Value &tv,
		double d);
#ifdef WIN32
	operator FILETIME() const
	{
		FILETIME file_time;
		ULARGE_INTEGER _100ns;
		_100ns.QuadPart = (((DWORDLONG) this->tv_.tv_sec * (10000 * 1000) +
			this->tv_.tv_usec * 10) +
			Time_Value::FILETIME_to_timval_skew);

		file_time.dwLowDateTime = _100ns.LowPart;
		file_time.dwHighDateTime = _100ns.HighPart;
		return file_time;
	}
#endif
	
public:

#ifdef WIN32
	static const DWORDLONG FILETIME_to_timval_skew;
#endif
	
	/** Method
	* - Summary:\n
	* 表态方法，得到当前的相对时间
	* - Parameters:\n
	*1
	*/
	static  Time_Value gettimeofday(void);
private:
	/** Method
	* - Summary:\n
	* 标准化，转换成秒和毫秒形势
	* - Parameters:\n
	*1
	*/
	void normalize (void);
	/** Property
	* - Summary:\n
	*时间对象
	*/
	timeval  tv_; 
};

#endif