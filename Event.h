#pragma once
#ifndef Event_h
#define Event_h

#include"Customer.h"
#include<iostream>
class Event
{
public:
	Event();
	~Event();

	//时间、事件类型
	//顾客号、服务窗口、等待时间、服务时间
	int occur_time;		//事件发生时间
	int event_type;		//事件类型，0表示到达事件
	Event(int occur_time, int event_type) :occur_time(occur_time), event_type(event_type) {}

private:

};

#endif // !Event_h
