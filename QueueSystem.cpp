// QueueSystem.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "���������е��ϰ�ʱ��(XX:XX:XX)��";
	cin >> onWork;
	cout << "���������е��°�ʱ��(XX:XX:XX)��";
	cin >> offWork;
	workTime = tc.getTime(onWork, offWork);
	cout << "���������еķ��񴰿�����";
	cin>>windowsNum;
	cout << "������ͻ������������ʱ��(s)��";
	cin >> s_maxTime;
	cout << "������ͻ��������̷���ʱ��(s)��";
	cin >> s_minTime;
	cout << "������ͻ�����Ƶ�ʣ�";
	cin >> freq_arrive;
	cout << "������ͻ���������ʱ����(s)��";
	cin >> a_maxTime;
	cout << "������ʱ����������";
	cin >> seed;
	srand(seed);
	BankSys bank(windowsNum, freq_arrive, workTime, s_maxTime, s_minTime, a_maxTime);
	bank.run();
	system("pause");
    return 0;
}

