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
	int getAvailbleWindows();	//�ҵ����д��ڱ�ţ����û�з���0
	float getFreArrive(int currTime);		//��õ�ǰʱ��Ŀͻ�����Ƶ��
	int generateSerTime();			//����������ʱ��
	int generateDuration();			//��������ʱ����
	void arriveEvent();			//�����¼�
	void departureEvent();		//�뿪�¼�
	void run();		//ϵͳ����

private:
	int workTime;			//����ʱ�䣬�û�����
	int WindowsNum;	//���񴰿���Ŀ���û�����
	int totalServiceTime;			//�ۼƷ���ʱ��
	int totalWaitTime;				//�ۼƵȴ�ʱ��
	int totalSerCustomer;			//�ۼƷ���Ŀͻ���
	int totalCustomer;				//�ۼƿͻ���

	/*�˿Ͱ���һ����Ƶ�ʵ�������ϵͳ�����������ʱ�䣬ͬʱ������һ�������¼���ʱ��
	 * ���ʱ�����Ĳ���������[1,ʱ��Ƶ��*��󵽴�ʱ����] *
	*/
	float freq_arrive;		//�ͻ������ʱ��Ƶ�ʣ������Ƽ����ڵ���1���û�����
	int s_maxTime;			//������ʱ�䣬�û�����
	int s_minTime;			//��С����ʱ�䣬�û�����
	int a_maxTime;		//��󵽴�ʱ�������û�����

	ServiceWindow* sw;
	Event curEvent;		//��ǰ�¼�
	Priority_Queue pq;	//�¼�����
	std::queue<Customer>cusq;
	TimeConverter tc;
};

#endif // !BankSystem_h