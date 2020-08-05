#pragma once
#ifndef Priority_Queue_h
#define Priority_Queue_h

#include"Event.h"
#include<list>
#include<iostream>

class Priority_Queue
{
public:
	Priority_Queue(Event *data,int n);
	Priority_Queue(int maxElements = 10000);
	~Priority_Queue();

	void orderInsert(Event &e);		//��ʱ������¼��������
	Event getHeadEvent();				//��ȡ����ͷ���¼������Ұ��¼��Ӷ������Ƴ�
	void Insert(const Event&en);	//�������ȶ���
	Event DeleteMin();					//������Сֵ
	bool isEmpty() const;				//�Ƿ�Ϊ�ն���
	bool isFull() const;					//�����Ƿ�Ϊ��


private:
	std::list<Event>q;	//����STL�е�list��������������
	int capicity;			//����
	int size;				//��ǰ��С
	Event *elements;	//Ԫ�ش洢��
	void init(int n);		//��ʼ��
	void destory();		//�������ȶ���
};

#endif // !Priority_Queue_h
