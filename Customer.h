#pragma once
#ifndef Customer_h

#define Customer_h

class Customer
{
public:
	Customer();
	~Customer();

	int numID;		//顾客号
	int arrive_time;//到达时间
	int wait_time;	//等待服务时间
	int ser_time;		//服务时间
	Customer(int numid, int arriveTime, int serTime) :
		numID(numid), arrive_time(arriveTime), ser_time(serTime) {}
private:

};

#endif // !Customer_h


