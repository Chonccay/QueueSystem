#pragma once
#ifndef BankSystem_h
#define BankSystem_h

#include"stdafx.h"
#include"Customer.h"
#include"Event.h"
#include"TimeConvertor.h"
#include"Priority_Queue.h"
#include"ServiceWindow.h"
#include<cmath>
class BankSys
{
public:
	BankSys(int WindowsNum, float freq_arrive, int workTime, int s_maxTime, int s_minTime, int a_maxTime);
	BankSys();
	~BankSys();
	int getAvailbleWindows();	//找到空闲窗口编号，如果没有返回0
	float getFreArrive(int currTime);		//获得当前时间的客户到达频率
	int generateSerTime();			//产生最大服务时间
	int generateDuration();			//产生到达时间间隔
	void arriveEvent();			//到达事件
	void departureEvent();		//离开事件
	void run();		//系统运行

private:
	int workTime;			//工作时间，用户输入
	int WindowsNum;	//服务窗口数目，用户输入
	int totalServiceTime;			//累计服务时间
	int totalWaitTime;				//累计等待时间
	int totalSerCustomer;			//累计服务的客户数
	int totalCustomer;				//累计客户数

	/*顾客按照一定的频率到达，到达后系统随机产生服务时间，同时产生下一个到达事件的时间
	 * 随机时间间隔的产生方法是[1,时间频率*最大到达时间间隔] *
	*/
	float freq_arrive;		//客户到达的时间频率，这里推荐大于等于1，用户输入
	int s_maxTime;			//最大服务时间，用户输入
	int s_minTime;			//最小服务时间，用户输入
	int a_maxTime;		//最大到达时间间隔，用户输入

	ServiceWindow* sw;
	Event curEvent;		//当前事件
	Priority_Queue pq;	//事件队列
	std::queue<Customer>cusq;
	TimeConverter tc;
};

#endif // !BankSystem_h