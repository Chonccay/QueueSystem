#include"stdafx.h"
#include"BankSystem.h"
#include<iostream>
using namespace std;

BankSys::BankSys(int WinNum, float freq_arrive, int workTime, int s_maxTime, int s_minTime, int a_maxTime) :
	WindowsNum(WinNum), freq_arrive(freq_arrive), workTime(workTime), s_maxTime(s_maxTime), s_minTime(s_minTime), a_maxTime(a_maxTime) {
	sw = new ServiceWindow[WindowsNum + 1];
	for (int i = 1; i <= WindowsNum; ++i) {
		ServiceWindow* tempsw = &sw[i];
		tempsw->ID = i;
		tempsw->setState(0);
	}
	totalSerCustomer = 0;
	totalCustomer = 0;
	totalServiceTime = 0;
	totalWaitTime = 0;
	curEvent.occur_time = 0;
	curEvent.event_type = 0;		//默认为到达事件
	pq.Insert(curEvent);
}

BankSys::BankSys()
{
}

BankSys::~BankSys()
{
}

int BankSys::generateSerTime() {		//产生一个 [s_minTime,s_maxTime) 的服务时间
	return rand() % (s_maxTime - s_minTime) + s_minTime;
}

int BankSys::generateDuration() {		//产生一个 [1,a_maxTime*freq_arrive]的时间间隔
	int tmp = (int)a_maxTime*freq_arrive;
	return rand() % tmp + 1;
}

void BankSys::arriveEvent() {			//到达事件
	totalCustomer++;		//累计客户数目加1
	int arriveTime = generateDuration();	//产生下一个到达的时间间隔
	int serviceTime = generateSerTime();	//产生当前用户的服务时间
	int t = curEvent.occur_time + arriveTime;	//下一个事件的发生时间
	Event newEvent(t, 0);	//新建该事件
	if (t < workTime) {
		pq.Insert(newEvent);	//将该到达事件添加到队列中
	}
	Customer newCustomer(totalCustomer,curEvent.occur_time,serviceTime);//新客户的编号，到达时间，服务时间
	cusq.push(newCustomer);		//将客户添加到顾客队列中
	/* 结果输出 */
	std::cout << "当前事件类型：" << "到达事件 " << " 新顾客的编号：" << newCustomer.numID
		<< " 新顾客的到达时间：" << tc.getTime(newCustomer.arrive_time) << " 新顾客需要的服务时间：" <<
		newCustomer.ser_time << endl;
	if (cusq.size() == 1) {				//如果队列中只有一个顾客的话，即该顾客在队列首部
		int freeWindows = getAvailbleWindows();		//查询空闲窗口编号
		if (freeWindows > 0) {			//如果存在空闲窗口
			Customer tempCustomer = cusq.front();	//队列首的顾客出列
			tempCustomer.wait_time = curEvent.occur_time - tempCustomer.arrive_time;
			cusq.pop();
			sw[freeWindows].serveCustomer(tempCustomer);		//客户进入该窗口
			sw[freeWindows].setState(newCustomer.numID);		//该窗口处于服务状态
			/*创建离开事件*/
			//cout << totalCustomer << endl;
			int tLeave = curEvent.occur_time + serviceTime;
			Event newEvent(tLeave, freeWindows);
			if (tLeave < workTime) {
				pq.Insert(newEvent);
			}
		}
	}
}

void BankSys::departureEvent() {			//离开事件
	totalSerCustomer++;		//被服务的客户数加1;
	int i = curEvent.event_type;
	/*获得离开的窗口*/
	if (sw[i].getState() == 0) {
		//cout << "该事件不是离开事件！" << endl;
		return;
	}
	Customer* tempCustomer = sw[i].getCustomer();		//获得窗口中的用户

	totalServiceTime += tempCustomer->ser_time;		//服务时间累加
	totalWaitTime += tempCustomer->wait_time;			//等待时间累加
	/* 结果输出 */
	std::cout << "窗口号 " << i << " 客户号 " << tempCustomer->numID <<" 客户到达时间 " <<
		tc.getTime(tempCustomer->arrive_time) <<" 等待时间 " << tempCustomer->wait_time <<
		"s " << " 服务时间 " <<tempCustomer->ser_time << "s " << " 离开时间 " <<
		tc.getTime(curEvent.occur_time) << endl;

	sw[i].setState(0);		//将此窗口设置为空闲状态
	/* 如果顾客队列不为空 */
	if (cusq.size() > 0) {
		int freeWindows = getAvailbleWindows();
		//cout << "新的空闲窗口" << freeWindows << endl;
		if (freeWindows > 0) {	//如果存在空闲窗口
			Customer c = cusq.front();
			c.wait_time = curEvent.occur_time - c.arrive_time;		//客户的等待时间
			cusq.pop();
			sw[freeWindows].serveCustomer(c);		//客户进入该窗口
			sw[freeWindows].setState(c.numID);		//将该窗口设置成服务状态
			/* 创建离开事件 */
			Event newEvent(curEvent.occur_time + c.ser_time, freeWindows);
			pq.Insert(newEvent);
		}
		else {
			//std::cout << "第" << i << "位顾客在等待空闲窗口" << endl;
		}
	}
}

void BankSys::run() {		//系统运行
	while (!pq.isEmpty()) {
		curEvent = pq.DeleteMin();		//获得第一个事件并删除
		//freq_arrive = getFreArrive(curEvent.occur_time);
		if (curEvent.occur_time <= workTime) {
			std::cout << tc.getTime(curEvent.occur_time) << '\t';
			if (curEvent.event_type == 0) {	//处理到达事件
				arriveEvent();
			}
			else {		//离开事件
				departureEvent();
			}
		}
	}
	std::cout << "客户人数为" << totalCustomer << endl;
	std::cout << "实际被服务客户人数为" << totalSerCustomer << endl;
	int serviceTime = totalServiceTime / totalSerCustomer;
	int serMinutes = serviceTime / 60;
	int serSeconds = serviceTime % 60;
	if (serMinutes == 0) {
		std::cout << "平均服务时间为" << serSeconds <<'s'<< endl;
	}
	else {
		std::cout << "平均服务时间为" << serMinutes << 'm' << serSeconds << 's' << endl;
	}
	int waitTime = totalWaitTime / totalSerCustomer;
	int waitMinutes = waitTime / 60;
	int waitSeconds = waitTime % 60;
	if (waitMinutes == 0) {
		std::cout << "平均等待时间为" << waitSeconds << 's' << endl;
	}
	else {
		std::cout << "平均等待时间为" << waitMinutes << 'm' << waitSeconds << 's' << endl;
	}
}

int BankSys::getAvailbleWindows() {		//找到空闲窗口
	int winIndex = 0;
	for (int i = 1; i <= WindowsNum; ++i) {
		if (sw[i].getState() == 0) {
			winIndex = i;
			break;
		}
	}
	return winIndex;
}