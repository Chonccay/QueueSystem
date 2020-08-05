#include"stdafx.h"
#include"ServiceWindow.h"
using namespace std;

ServiceWindow::ServiceWindow()
{
}

ServiceWindow::~ServiceWindow()
{
}

void ServiceWindow::serveCustomer(Customer &c) {//½¨ÒéÐÞ¸Ä
	cus.arrive_time = c.arrive_time;
	cus.numID = c.numID;
	cus.ser_time = c.ser_time;
	cus.wait_time = c.wait_time;
}

int ServiceWindow::getState() {
	return state;
}

void ServiceWindow::setState(int i) {
	state = i;
}

Customer* ServiceWindow::getCustomer() {
	return &cus;
}
