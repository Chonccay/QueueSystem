#pragma once
#ifndef Customer_h

#define Customer_h

class Customer
{
public:
	Customer();
	~Customer();

	int numID;		//�˿ͺ�
	int arrive_time;//����ʱ��
	int wait_time;	//�ȴ�����ʱ��
	int ser_time;		//����ʱ��
	Customer(int numid, int arriveTime, int serTime) :
		numID(numid), arrive_time(arriveTime), ser_time(serTime) {}
private:

};

#endif // !Customer_h


