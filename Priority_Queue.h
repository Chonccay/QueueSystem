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

	void orderInsert(Event &e);		//按时间戳把事件加入队列
	Event getHeadEvent();				//获取队列头部事件，并且把事件从队列中移除
	void Insert(const Event&en);	//插入优先队列
	Event DeleteMin();					//返回最小值
	bool isEmpty() const;				//是否为空队列
	bool isFull() const;					//队列是否为满


private:
	std::list<Event>q;	//采用STL中的list来构造排序链表
	int capicity;			//容量
	int size;				//当前大小
	Event *elements;	//元素存储区
	void init(int n);		//初始化
	void destory();		//销毁优先队列
};

#endif // !Priority_Queue_h
