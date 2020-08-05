#pragma once
#ifndef ServiceWindow_h
#define Service_Window_h

#include"Customer.h"
#include<queue>

class ServiceWindow
{
public:
	ServiceWindow();
	~ServiceWindow();
	void serveCustomer(Customer &c);	//为一名顾客服务时，将其信息拷贝
	int getState();										//获取窗口状态：空闲/忙碌
	void setState(int i);								//设置窗口状态
	Customer* getCustomer();					//获取窗口中的用户

	int ID;		//窗口号
private:
	int state;	//0表示空闲状态，非0表示编号用户正在被服务
	int lastest_available_time;	//最早服务时间
	Customer cus;
};

#endif // !ServiceWindow_h
