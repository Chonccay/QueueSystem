// QueueSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"TimeConvertor.h"
#include"BankSystem.h"
#include<iostream>
#include<ctype.h>
using namespace std;

int main()
{
	TimeConverter tc;
	int seed;
	int workTime;
	int windowsNum;
	float freq_arrive;
	int s_maxTime;
	int s_minTime;
	int a_maxTime;
	string onWork, offWork;
	cout << "请输入银行的上班时间(XX:XX:XX)：";
	cin >> onWork;
	cout << "请输入银行的下班时间(XX:XX:XX)：";
	cin >> offWork;
	workTime = tc.getTime(onWork, offWork);
	cout << "请输入银行的服务窗口数：";
	cin>>windowsNum;
	cout << "请输入客户所需的最大服务时间(s)：";
	cin >> s_maxTime;
	cout << "请输入客户所需的最短服务时间(s)：";
	cin >> s_minTime;
	cout << "请输入客户到达频率：";
	cin >> freq_arrive;
	cout << "请输入客户到达的最大时间间隔(s)：";
	cin >> a_maxTime;
	cout << "请输入时间种子数：";
	cin >> seed;
	srand(seed);
	BankSys bank(windowsNum, freq_arrive, workTime, s_maxTime, s_minTime, a_maxTime);
	bank.run();
	system("pause");
    return 0;
}

