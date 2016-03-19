#pragma once
#include "Ref_Object.h"
#include "Smart_Ptr.h"

class Time_Value;
class Timer_Handler : public Ref_Object
{
public:
	virtual ~Timer_Handler(void){}

	virtual void handle_time_out(const Time_Value& now,const Time_Value& tv,Smart_Ptr<Ref_Object>& act,long timer_id) = 0;
};
