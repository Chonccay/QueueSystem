#pragma once
#ifndef TimeConverter_h
#define TimeConverter_h

#include<string>
#include<sstream>

class TimeConverter
{
public:

	 int getTime(std::string start,std::string end);		//�������������ʽ�ο�08:00:00-17:00:00
	 std::string getTime(int seconds);
	 std::string num2Str(int i);

private:

};

#endif // !TimeConverter_h
