#include"stdafx.h"
#include"Priority_Queue.h"

Priority_Queue::Priority_Queue(Event *data,int n)
{
	init(n);
	for (int i = 0; i < n; ++i)
		Insert(data[i]);
}
Priority_Queue::Priority_Queue(int maxElements) {
	init(maxElements);
}

Priority_Queue::~Priority_Queue()
{
	destory();
}

void Priority_Queue::orderInsert(Event &e) {
	Event newEvent(e.occur_time, e.event_type);
	std::list<Event>::iterator it = q.begin();
	while (it != q.end()) {
		Event temp = *it;
		if (newEvent.occur_time <= temp.occur_time) {
			q.insert(it, newEvent);				//将newEvent插入到迭代器it的前面
			break;
		}
		it++;
	}
	if (it == q.end()) {
		q.push_back(newEvent);
	}
}

Event Priority_Queue::getHeadEvent() {
	std::list<Event>::iterator it = q.begin();
	Event temp = q.front();
	q.pop_front();
	return temp;
}

void Priority_Queue::Insert(const Event& en) {
	if (!isFull()) {
		int i;
		for (i = ++size; en.occur_time < elements[i / 2].occur_time; i /= 2) {
			elements[i] = elements[i / 2];
		}
		this->elements[i] = en;
	}
}

Event Priority_Queue::DeleteMin() {
	Event minElement, lastElement;
	int i, child;
	if (!isEmpty()) {
		minElement = this->elements[1];
		lastElement = this->elements[this->size--];
		for (i = 1; i * 2 <= this->size; i = child) {
			child = i * 2;
			if (child != this->size&&this->elements[child + 1].occur_time < this->elements[child].occur_time) {
				child++;
			}
			if (lastElement.occur_time > this->elements[child].occur_time) {
				this->elements[i] = this->elements[child];
			}
			else{
				break;
			}
		}
		this->elements[i] = lastElement;
		return minElement;		//返回最小值
	}
	return this->elements[0];//失败
}

bool Priority_Queue::isEmpty() const {
	return this->size == 0;
}

bool Priority_Queue::isFull() const {
	return this->size == capicity;
}

void Priority_Queue::init(int n) {
	this->elements = new Event[n + 1];
	this->capicity = n;
	this->size = 0;
}

void Priority_Queue::destory() {
	if (this->elements != nullptr) {
		delete[] elements;
		this->elements = nullptr;
		this->size = 0;
	}
}