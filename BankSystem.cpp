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
	curEvent.event_type = 0;		//Ĭ��Ϊ�����¼�
	pq.Insert(curEvent);
}

BankSys::BankSys()
{
}

BankSys::~BankSys()
{
}

int BankSys::generateSerTime() {		//����һ�� [s_minTime,s_maxTime) �ķ���ʱ��
	return rand() % (s_maxTime - s_minTime) + s_minTime;
}

int BankSys::generateDuration() {		//����һ�� [1,a_maxTime*freq_arrive]��ʱ����
	int tmp = (int)a_maxTime*freq_arrive;
	return rand() % tmp + 1;
}

void BankSys::arriveEvent() {			//�����¼�
	totalCustomer++;		//�ۼƿͻ���Ŀ��1
	int arriveTime = generateDuration();	//������һ�������ʱ����
	int serviceTime = generateSerTime();	//������ǰ�û��ķ���ʱ��
	int t = curEvent.occur_time + arriveTime;	//��һ���¼��ķ���ʱ��
	Event newEvent(t, 0);	//�½����¼�
	if (t < workTime) {
		pq.Insert(newEvent);	//���õ����¼���ӵ�������
	}
	Customer newCustomer(totalCustomer,curEvent.occur_time,serviceTime);//�¿ͻ��ı�ţ�����ʱ�䣬����ʱ��
	cusq.push(newCustomer);		//���ͻ���ӵ��˿Ͷ�����
	/* ������ */
	std::cout << "��ǰ�¼����ͣ�" << "�����¼� " << " �¹˿͵ı�ţ�" << newCustomer.numID
		<< " �¹˿͵ĵ���ʱ�䣺" << tc.getTime(newCustomer.arrive_time) << " �¹˿���Ҫ�ķ���ʱ�䣺" <<
		newCustomer.ser_time << endl;
	if (cusq.size() == 1) {				//���������ֻ��һ���˿͵Ļ������ù˿��ڶ����ײ�
		int freeWindows = getAvailbleWindows();		//��ѯ���д��ڱ��
		if (freeWindows > 0) {			//������ڿ��д���
			Customer tempCustomer = cusq.front();	//�����׵Ĺ˿ͳ���
			tempCustomer.wait_time = curEvent.occur_time - tempCustomer.arrive_time;
			cusq.pop();
			sw[freeWindows].serveCustomer(tempCustomer);		//�ͻ�����ô���
			sw[freeWindows].setState(newCustomer.numID);		//�ô��ڴ��ڷ���״̬
			/*�����뿪�¼�*/
			//cout << totalCustomer << endl;
			int tLeave = curEvent.occur_time + serviceTime;
			Event newEvent(tLeave, freeWindows);
			if (tLeave < workTime) {
				pq.Insert(newEvent);
			}
		}
	}
}

void BankSys::departureEvent() {			//�뿪�¼�
	totalSerCustomer++;		//������Ŀͻ�����1;
	int i = curEvent.event_type;
	/*����뿪�Ĵ���*/
	if (sw[i].getState() == 0) {
		//cout << "���¼������뿪�¼���" << endl;
		return;
	}
	Customer* tempCustomer = sw[i].getCustomer();		//��ô����е��û�

	totalServiceTime += tempCustomer->ser_time;		//����ʱ���ۼ�
	totalWaitTime += tempCustomer->wait_time;			//�ȴ�ʱ���ۼ�
	/* ������ */
	std::cout << "���ں� " << i << " �ͻ��� " << tempCustomer->numID <<" �ͻ�����ʱ�� " <<
		tc.getTime(tempCustomer->arrive_time) <<" �ȴ�ʱ�� " << tempCustomer->wait_time <<
		"s " << " ����ʱ�� " <<tempCustomer->ser_time << "s " << " �뿪ʱ�� " <<
		tc.getTime(curEvent.occur_time) << endl;

	sw[i].setState(0);		//���˴�������Ϊ����״̬
	/* ����˿Ͷ��в�Ϊ�� */
	if (cusq.size() > 0) {
		int freeWindows = getAvailbleWindows();
		//cout << "�µĿ��д���" << freeWindows << endl;
		if (freeWindows > 0) {	//������ڿ��д���
			Customer c = cusq.front();
			c.wait_time = curEvent.occur_time - c.arrive_time;		//�ͻ��ĵȴ�ʱ��
			cusq.pop();
			sw[freeWindows].serveCustomer(c);		//�ͻ�����ô���
			sw[freeWindows].setState(c.numID);		//���ô������óɷ���״̬
			/* �����뿪�¼� */
			Event newEvent(curEvent.occur_time + c.ser_time, freeWindows);
			pq.Insert(newEvent);
		}
		else {
			//std::cout << "��" << i << "λ�˿��ڵȴ����д���" << endl;
		}
	}
}

void BankSys::run() {		//ϵͳ����
	while (!pq.isEmpty()) {
		curEvent = pq.DeleteMin();		//��õ�һ���¼���ɾ��
		//freq_arrive = getFreArrive(curEvent.occur_time);
		if (curEvent.occur_time <= workTime) {
			std::cout << tc.getTime(curEvent.occur_time) << '\t';
			if (curEvent.event_type == 0) {	//�������¼�
				arriveEvent();
			}
			else {		//�뿪�¼�
				departureEvent();
			}
		}
	}
	std::cout << "�ͻ�����Ϊ" << totalCustomer << endl;
	std::cout << "ʵ�ʱ�����ͻ�����Ϊ" << totalSerCustomer << endl;
	int serviceTime = totalServiceTime / totalSerCustomer;
	int serMinutes = serviceTime / 60;
	int serSeconds = serviceTime % 60;
	if (serMinutes == 0) {
		std::cout << "ƽ������ʱ��Ϊ" << serSeconds <<'s'<< endl;
	}
	else {
		std::cout << "ƽ������ʱ��Ϊ" << serMinutes << 'm' << serSeconds << 's' << endl;
	}
	int waitTime = totalWaitTime / totalSerCustomer;
	int waitMinutes = waitTime / 60;
	int waitSeconds = waitTime % 60;
	if (waitMinutes == 0) {
		std::cout << "ƽ���ȴ�ʱ��Ϊ" << waitSeconds << 's' << endl;
	}
	else {
		std::cout << "ƽ���ȴ�ʱ��Ϊ" << waitMinutes << 'm' << waitSeconds << 's' << endl;
	}
}

int BankSys::getAvailbleWindows() {		//�ҵ����д���
	int winIndex = 0;
	for (int i = 1; i <= WindowsNum; ++i) {
		if (sw[i].getState() == 0) {
			winIndex = i;
			break;
		}
	}
	return winIndex;
}