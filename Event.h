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

	//ʱ�䡢�¼�����
	//�˿ͺš����񴰿ڡ��ȴ�ʱ�䡢����ʱ��
	int occur_time;		//�¼�����ʱ��
	int event_type;		//�¼����ͣ�0��ʾ�����¼�
	Event(int occur_time, int event_type) :occur_time(occur_time), event_type(event_type) {}

private:

};

#endif // !Event_h
