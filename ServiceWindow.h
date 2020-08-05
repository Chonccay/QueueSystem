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
	void serveCustomer(Customer &c);	//Ϊһ���˿ͷ���ʱ��������Ϣ����
	int getState();										//��ȡ����״̬������/æµ
	void setState(int i);								//���ô���״̬
	Customer* getCustomer();					//��ȡ�����е��û�

	int ID;		//���ں�
private:
	int state;	//0��ʾ����״̬����0��ʾ����û����ڱ�����
	int lastest_available_time;	//�������ʱ��
	Customer cus;
};

#endif // !ServiceWindow_h
