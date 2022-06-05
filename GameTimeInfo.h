#pragma once

#define _GAMETIMEINFO
#ifndef _GAMETIMEINFO
#define _GAMETIMEINFO

#include <time.h>

enum Month{
	DJanuary = 31, DFebryary = 28, DFebryaryLeap = 29,
	DMarch = 31, DApril = 30, DMay = 31,
	DJune = 30, DJuly = 31, DAugust = 31,
	DSeptember = 30, DOctober = 31, DNovember = 30,
	DDecember = 31
}; //Days in month

typedef enum Month{
January, Febryary, FebryaryLeap,
	March, April, May,
	June, July, August,
	September, October, November,
	December
};


class CGameTimeInfo
{
public:


private:
	byte m_Sec;
	byte m_Min;
	byte m_Hour;
	byte m_Day;
	byte m_Month;
	int m_Year;
	SYSTEMTIME tm;
public:
	void Tick();
	void Update();
};

#endif

/*
January - 31 days
February - 28 days in a common year and 29 days in Leap Years
March - 31 days
April - 30 days
May - 31 days
June - 30 days
July - 31 days
August - 31 days
September - 30 days
October - 31 days
November - 30 days
December - 31 days
*/