#include"stdafx.h"
#include"TimeConvertor.h"

int TimeConverter::getTime(std::string start,std::string end) {
	int h = 0, m = 0, s = 0;		//时分秒初始化
	int time;
	if (start[2] == ':'&&start[5] == ':'&&end[2] == ':'&&end[5] == ':') {		//判断日期输入格式是否合法
		int hs = std::stoi(start.substr(0, 2)), ms = std::stoi(start.substr(3, 2)), ss = std::stoi(start.substr(6, 2));
		int he = std::stoi(end.substr(0, 2)), me = std::stoi(end.substr(3, 2)), se = std::stoi(end.substr(6, 2));
		if (hs * 10000 + ms * 100 + ss >= he * 10000 + me * 100 + se) {
			return 0;
		}
		if (se < ss) {
			s =se + 60 - ss;
			me--;
		}
		else {
			s = se - ss;
		}
		if (me < ms) {
			m = me + 60 - ms;
			he--;
		}
		else {
			m= me - ms;
		}
		h =he - hs;
	}
	else {
		return 0;
	}
	time = h * 60 * 60 + m * 60 + s;
	return time;
}

inline std::string TimeConverter::num2Str(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string TimeConverter::getTime(int seconds) {
	int openTime = 8;//默认开始营业时间为早上8点
	int h = 0, m = 0, s = 0;
	std::string hStr = "", mStr = "", sStr = "", timeStr = "";
	s = seconds % 60;
	int res = seconds / 60;
	m = res % 60;
	h = res / 60;
	h += openTime;

	if (h < 10) {
		hStr = '0' + num2Str(h);
	}
	else {
		hStr = num2Str(h);
	}
	if (m < 10) {
		mStr = '0' + num2Str(m);
	}
	else {
		mStr = num2Str(m);
	}
	if (s < 10) {
		sStr = '0' + num2Str(s);
	}
	else {
		sStr = num2Str(s);
	}
	return timeStr = hStr + ':' + mStr + ':' + sStr;
}